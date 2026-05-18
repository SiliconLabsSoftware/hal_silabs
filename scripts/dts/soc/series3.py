# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

import glob
import logging
import os
import re
import sys
from pathlib import Path

import cmsis_svd.parser

import util.sdk
import util.soc
import dts.soc.common
from dts.node import Node, ClockNode, DeleteNode, ChosenNode
from dts.prop import DeferredValue, DeleteProperty, property_from_string

logger = logging.getLogger(__name__)


def create_family_device_tree(family, shared_config):
    """
    Create family-specific devicetree including the base devicetree and setting any
    family-specific properties.
    """
    family_dt = Node("/")
    family_dt.add_include(f"silabs/{shared_config.name}/{shared_config.name}.dtsi")

    soc = Node("soc")
    family_dt.add_node(soc)
    nodes = [family_dt]

    if family.any("device_has_radio"):
        radio = Node(
            "radio",
            labels=["radio"],
            compatible="silabs,series2-radio",
            reg=[0xB0000000, 0x1000000],
        )
        soc.add_node(radio)

        radio_interrupts = [
            "agc",
            "bufc",
            "frc_pri",
            "frc",
            "hfrcolpw",
            "hfrcodplllpw",
            "modem",
            "protimer",
            "rac_rsm",
            "rac_seq",
            "rftimer",
            "seqacc",
            "synth",
            "sysmblpw0cpu",
            "rfeca0",
            "rfeca1",
        ]
        dts.soc.common.add_interrupts_to_node(
            radio, None, radio_interrupts, shared_config.cmsis.interrupts, prio=1
        )

        radio.add_int("pa-initial-power-dbm", 10)
        radio.add_int(
            "pa-max-power-dbm", dts.soc.common.get_max_output_power(shared_config.cmsis)
        )
        radio.add_int("pa-ramp-time-us", 2)
        radio.add_int("pa-voltage-mv", 3300)
        # TODO: Make OPN dependent?
        radio.add_bool("radio-tx-high-power-supported", True)

        if shared_config.any("device_has_radio_2g4hz"):
            radio.add_string("pa-2p4ghz", "auto")

        if family.any("device_supports_bluetooth"):
            bt = Node(
                "bt_hci_silabs",
                labels=["bt_hci_silabs"],
                compatible="silabs,bt-hci-efr32",
            )
            bt.status("disabled")
            radio.add_node(bt)

            for prop, feature in dts.soc.common.BT_FEATURES.items():
                if family.all(feature):
                    radio.add_bool(prop, True)

        if family.all("device_supports_thread"):
            ieee802154 = Node(
                "ieee802154", labels=["ieee802154"], compatible="silabs,efr32-ieee802154"
            )
            ieee802154.status("disabled")
            radio.add_node(ieee802154)


        protimer = Node("protimer", labels=["protimer"], compatible="silabs,protimer")
        protimer.status("disabled")
        radio.add_node(protimer)

        pti = Node("pti", labels=["pti"], compatible="silabs,pti")
        pti.add_int("clock-frequency", "DT_FREQ_K(1600)")
        pti.add_string("mode", "uart")
        pti.status("disabled")
        radio.add_node(pti)

    return nodes


def create_clock_device_trees(dt: Node) -> dict[str, list[Node]]:
    """
    Create clock configuration devicetree fragments, configuring the clock tree to
    use a given oscillator.
    """
    output = {}

    freq = {}
    freq["hfxo"] = dt.find("/soc/hfxo", address=False).prop("clock-frequency").value
    start = freq["hfxo"].find("(") + 1
    end = freq["hfxo"].find(")")
    hfxo_freq = int(freq["hfxo"][start:end])
    freq["hfrcodpll"] = freq["hfxo"][:start] + str(hfxo_freq * 2) + freq["hfxo"][end:]
    freq["hfrco"] = (
        dt.find("/soc/hfrcodpll", address=False).prop("clock-frequency").value
    )
    freq["socpll"] = (
        dt.find("/soc/socpll0", address=False).prop("clock-frequency").value
    )

    for clock_name in ["socpll"]:
        nodes = []
        for mux_node in dt.find("clocks").nodes:
            if p := mux_node.prop("clocks"):
                if (
                    mux_node.name not in ["hfrcodpllrt", "hfxort"]
                    and p.value == "socpll"
                ):
                    new_node = Node(labels=[mux_node.labels[0]])
                    new_node.add_phandle("clocks", clock_name)
                    nodes.append(new_node)

        cpu = Node(labels=["cpu0"])
        cpu.add_int("clock-frequency", freq[clock_name])
        nodes.append(cpu)

        cpu = Node(labels=["itm"])
        cpu.add_int("swo-ref-frequency", freq[clock_name])
        nodes.append(cpu)

        hfxo = Node(labels=["hfxo"])
        hfxo.status("okay")
        nodes.append(hfxo)

        socpll = Node(labels=["socpll"])
        socpll.add_int("clock-frequency", freq[clock_name])
        socpll.add_phandle("clocks", "hfxo")
        socpll.status("okay")
        nodes.append(socpll)

        nodes.sort(key=lambda n: (n.labels, n.name))
        output[clock_name] = nodes

    for clock_name in ["hfrcodpll", "hfxo", "hfrco"]:
        clock_phandle = clock_name
        if clock_name in ["hfrco"]:
            clock_phandle += "dpll"
        nodes = []
        for mux_node in dt.find("clocks").nodes:
            if p := mux_node.prop("clocks"):
                if mux_node.name not in ["hfrcodpllrt", "hfxort"] and p.value in [
                    "hfrcodpll",
                    "socpll",
                ]:
                    new_node = Node(labels=[mux_node.labels[0]])
                    new_node.add_phandle("clocks", clock_phandle)
                    nodes.append(new_node)

        cpu = Node(labels=["cpu0"])
        cpu.add_int("clock-frequency", freq[clock_name])
        nodes.append(cpu)

        cpu = Node(labels=["itm"])
        cpu.add_int("swo-ref-frequency", freq[clock_name])
        nodes.append(cpu)

        hfxo = Node(labels=["hfxo"])
        if clock_name == "hfrco":
            hfxo.status("disabled")
        else:
            hfxo.status("okay")
        nodes.append(hfxo)

        socpll = Node(labels=["socpll"])
        socpll.status("disabled")
        nodes.append(socpll)

        dpll = Node(labels=["hfrcodpll"])
        if clock_name == "hfxo":
            dpll.status("disabled")
        elif clock_name == "hfrco":
            dpll.add_int("clock-frequency", freq[clock_name])
            dpll.status("okay")
        else:
            dpll.add_int("clock-frequency", freq[clock_name])
            dpll.add_phandle("clocks", "hfxo")
            dpll.add_bool("dpll-autorecover", True)
            dpll.add_string("dpll-edge", "fall")
            dpll.add_string("dpll-lock", "phase")
            dpll.add_int("dpll-m", 1919)
            dpll.add_int("dpll-n", 3839)
        nodes.append(dpll)

        nodes.sort(key=lambda n: (n.labels, n.name))
        output[clock_name] = nodes

    nodes = []
    for mux_node in dt.find("clocks").nodes:
        if p := mux_node.prop("clocks"):
            if mux_node.name not in ["hfrcodpllrt", "hfxort"] and p.value == "lfrco":
                new_node = Node(labels=[mux_node.labels[0]])
                new_node.add_phandle("clocks", "lfxo")
                nodes.append(new_node)

    lfxo = Node(labels=["lfxo"])
    lfxo.status("okay")
    nodes.append(lfxo)

    nodes.sort(key=lambda n: (n.labels, n.name))
    output["lfxo"] = nodes

    return output
