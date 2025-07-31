# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, pinctrl: Node):
    if b.soc_config.get("device.dcdc") == "BOOST":
        # Boost DCDC is handled at SoC level
        return

    if b.config.get("SL_DEVICE_INIT_DCDC_ENABLE") in [None, "1"]:
        node = Node(labels=["dcdc"], status="okay")
        node.add_include("zephyr/dt-bindings/regulator/silabs_dcdc.h")

        if b.config.get("SL_DEVICE_INIT_DCDC_BYPASS") != "1":
            node.add_bool("regulator-boot-on", True)

        node.add_int("regulator-initial-mode", "SILABS_DCDC_MODE_BUCK")

        ipkvals = {
            "3": 50,
            "4": 65,
            "5": 73,
            "6": 80,
            "7": 86,
            "8": 93,
            "9": 100,
            "10": 106,
            "11": 113,
            "12": 120,
        }

        ipkval = None
        if b.config.get("SL_DEVICE_INIT_DCDC_PFMX_IPKVAL_OVERRIDE") == "1":
            ipkval = b.config.get("SL_DEVICE_INIT_DCDC_PFMX_IPKVAL", "12")
        elif b.soc_family == "xg23":
            ipkval = "9"
            if b.soc_config.get("device.efr32_subghz_hp_pa_max_output") == "20":
                ipkval = "6"
        elif b.soc_family == "xg24":
            try:
                b.soc_config.get("device.efr32_2g4hz_hp_pa_max_output")
                ipkval = "9"
            except KeyError:
                ipkval = "12"
        elif b.soc_family == "xg26":
            ipkval = "12"
        elif b.soc_family == "xg28":
            ipkval = "9"

        if ipkval is not None:
            node.add_int("silabs,pfmx-peak-current-milliamp", ipkvals[ipkval])

        return [node]
