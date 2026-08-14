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
from dts.node import Node, ClockNode, DeleteNode, ChosenNode
from dts.prop import DeferredValue, DeleteProperty, property_from_string

ZEPHYR_BASE = Path(os.getenv("ZEPHYR_BASE"))
sys.path.insert(0, str(ZEPHYR_BASE / "scripts" / "dts" / "python-devicetree" / "src"))
from devicetree import edtlib  # noqa: E402

logger = logging.getLogger(__name__)

BT_FEATURES = {
    "ble-2mbps-supported": ["device_supports_bluetooth"],
    "ble-coded-phy-supported": ["device_supports_bluetooth_coded_phy"],
    "ble-cte-tx-supported": [
        "device_supports_bluetooth_cte",
    ],
    "ble-cte-rx-supported": [
        "device_supports_bluetooth_cte",
        "device_supports_bluetooth_iq_sampling",
        "device_supports_bluetooth_antenna_switching",
    ],
    "ble-cs-supported": ["device_generic_family_efr32xg24"],
}


def create_device_tree(family, device, gen_config: util.soc.GenConfig, svd_dir: Path):
    """
    Create base device tree for a generic device family based on a representative device.
    """
    svd = cmsis_svd.parser.SVDParser.for_xml_file(svd_dir / f"{device}.svd")

    dt = Node("/")
    dt.add_include("freq.h")

    chosen = ChosenNode("chosen")
    dt.add_node(chosen)

    clocks = Node("clocks")
    dt.add_node(clocks)

    create_clock_nodes(svd, clocks, gen_config.clocks)

    cpus = Node("cpus")
    dt.add_node(cpus)
    cpus.add_int("#address-cells", 1)
    cpus.add_int("#size-cells", 0)

    cpu_compat = {
        "cm33": {"binding": "arm,cortex-m33", "include": "arm/armv8-m.dtsi"},
        "cm55": {"binding": "arm,cortex-m55", "include": "arm/armv8.1-m.dtsi"},
    }
    cpu = Node(
        "cpu",
        labels=["cpu0"],
        compatible=cpu_compat.get(gen_config.config.cmsis.get("cpu.core"), {}).get(
            "binding"
        ),
        reg=[0],
        reg_is_hex=False,
    )
    cpus.add_node(cpu)
    cpu.get_root().add_include(
        cpu_compat.get(gen_config.config.cmsis.get("cpu.core"), {}).get("include")
    )
    cpu.add_string("device_type", "cpu")
    cpu.add_int("#address-cells", 1)
    cpu.add_int("#size-cells", 1)
    cpu.add_node(
        Node(
            "itm", labels=["itm"], compatible="arm,armv8m-itm", reg=[0xE0000000, 0x1000]
        )
    )
    cpu.add_node(
        Node("mpu", labels=["mpu"], compatible="arm,armv8m-mpu", reg=[0xE000ED90, 0x40])
    )


    if family in ["sibg301", "simg301"]:
        em2_name = "em1div16"
    else:
        em2_name = "em2"

    power_states = {
        "em1": {
            "name": "runtime-idle",
            "filter": lambda x: True,
        },
        em2_name: {
            "name": "suspend-to-idle",
            "filter": lambda x: True,
        },
        "em4": {
            "name": "soft-off",
            "filter": lambda x: True,
            "status": "disabled",
        },
    }
    cpu.add_phandles(
        "cpu-power-states",
        list(
            [
                f"pstate_{em}"
                for em, data in power_states.items()
                if data["filter"](gen_config.config.cmsis)
            ]
        ),
        comment=f"The minimum residency and exit latency is managed by sl_power_manager on S{gen_config.config.cmsis.get('device.series')} devices.",
    )

    power = Node("power-states")
    cpus.add_node(power)
    for em, data in power_states.items():
        if not data["filter"](gen_config.config.cmsis):
            continue
        state = Node(em, labels=[f"pstate_{em}"], compatible="zephyr,power-state")
        state.add_string("power-state-name", data["name"])
        if status := data.get("status"):
            state.status(status)
        power.add_node(state)

    sram = Node("memory", labels=["sram0"], compatible="mmio-sram")
    sram.address = DeferredValue("memory.sram.base")
    sram.add_string("device_type", "memory")
    dt.add_node(sram)

    soc = Node("soc")
    dt.add_node(soc)

    create_peripheral_nodes(svd, soc, gen_config.config, gen_config.peripherals)
    dt.resolve_deferred_values(gen_config.config.cmsis)

    hwinfo = Node("hwinfo", labels=["hwinfo"], compatible=f"silabs,series{gen_config.config.cmsis.get('device.series')}-hwinfo")
    hwinfo.status("disabled")
    dt.add_node(hwinfo)

    nvic = Node("&nvic")
    nvic.add_int("arm,num-irq-priority-bits", DeferredValue("cpu.nvic_prio_bits"))
    nvic.resolve_deferred_values(gen_config.config.cmsis)

    return [dt, nvic]


def create_clock_nodes(
    svd: cmsis_svd.parser.SVDParser,
    clocks: ClockNode,
    cfg: util.soc.ClockConfig,
):
    """
    Parse clock muxes from SVD and add them to devicetree
    """
    cmu: cmsis_svd.parser.SVDPeripheral = next(
        filter(lambda p: p.name == "CMU_NS", svd.get_device().peripherals)
    )
    clock_names = set()

    for reg in cmu.registers:
        if reg.name.endswith("CTRL") and reg.name not in ["DPLLREFCLKCTRL"]:
            clock_name = reg.name.rstrip("CTRL").lower()

            for field in reg.fields:
                # Add clock muxes from CLKSEL registers
                if field.name == "CLKSEL":
                    if clock_name in cfg.skip:
                        continue
                    clock_names.add(clock_name)

                    mask = ((1 << field.bit_width) - 1) << field.bit_offset
                    default = (reg.reset_value & mask) >> field.bit_offset
                    parent = None
                    for val in field.enumerated_values:
                        clksel_name = val.name.lower()
                        if clksel_name == "disabled":
                            continue
                        clock_names.add(clksel_name)

                        if val.value == default:
                            parent = clksel_name

                    clocks.add_node(
                        ClockNode(clock_name, cfg.selection.get(clock_name, parent))
                    )

            for field in reg.fields:
                # Add clock dividers from PRESC registers
                if field.name == "PRESC":
                    if clock_name in cfg.skip:
                        continue

                    # Single prescaler associated with the mux itself, or a child of the mux.
                    # Try to update the mux node.
                    node = clocks.find(clock_name)
                    if node is None:
                        # Create a child if not found
                        node = ClockNode(clock_name, cfg.selection.get(clock_name))
                        clocks.add_node(node)

                    mask = ((1 << field.bit_width) - 1) << field.bit_offset
                    default = (reg.reset_value & mask) >> field.bit_offset
                    node.add_int("clock-div", default + 1)
                elif field.name.endswith("PRESC"):
                    # Multiple prescalers that are children of the mux. Add new nodes.
                    clock_name = field.name.rstrip("PRESC").lower()
                    if clock_name in cfg.skip:
                        continue
                    for name in [clock_name] + cfg.extra_children.get(clock_name, []):
                        clock_node = ClockNode(name, cfg.selection.get(name))
                        clock_node.add_int("clock-div", cfg.divider.get(name, 1))
                        clocks.add_node(clock_node)

    # Additional clock nodes that are not directly derived from registers
    clocks.add_node(ClockNode("systickclk", "hclk"))
    if "hfxort" in clock_names:
        clocks.add_node(ClockNode("hfxort", "hfxo"))
    if "hfrcodpllrt" in clock_names:
        clocks.add_node(ClockNode("hfrcodpllrt", "hfrcodpll"))
    if "hclkdiv1024" in clock_names:
        node = ClockNode("hclkdiv1024", "hclk")
        node.add_int("clock-div", 1024)
        clocks.add_node(node)


def create_peripheral_nodes(svd, soc, config, peripheral_config):
    """
    Create devicetree node for a peripheral.
    """
    binding_paths = glob.glob(f"{ZEPHYR_BASE}/dts/bindings/**/*.y*ml", recursive=True)
    bindings = edtlib.bindings_from_paths(binding_paths, ignore_errors=True)

    for peripheral in svd.get_device().peripherals:
        if not peripheral.name.endswith(("_NS", "_NS_HOST")):
            continue
        if peripheral.name.endswith("_NS_HOST"):
            name = peripheral.name[:-8].lower()
        else:
            name = peripheral.name[:-3].lower()

        for cfg in peripheral_config:
            if re.match(cfg.get("svd"), name):
                break
        else:
            raise ValueError(f"No matching peripheral found for {peripheral.name}")

        if cfg.get("skip", False):
            continue

        p = create_node_from_config(soc, config, cfg, bindings, name, peripheral)

        if (clock := config.clocks.get(name)) and name not in ["hfrco0", "socpll0"]:
            p.add_phandle_array("clocks", [["cmu", clock["clock"], clock["branch"]]])

        if "ldma" in name:
            if clock := config.clocks.get(name.replace("ldma", "ldmaxbar")):
                p.prop("clocks").value.append(["cmu", clock["clock"], clock["branch"]])
                p.add_string_array("clock-names", ["ldma", "xbar"])

        extra_interrupts = [
            int_name.replace("{peripheral}", name)
            for int_name in cfg.get("interrupts", [])
        ]
        add_interrupts_to_node(p, peripheral, extra_interrupts, config.cmsis.interrupts)


def create_node_from_config(
    parent, output_config, cfg, bindings, name=None, peripheral=None, reg=None
):
    """
    Construct a devicetree node from YAML configuration
    """
    if "binding" in cfg:
        binding = next(filter(lambda b: b.compatible == cfg.get("binding"), bindings))
    else:
        binding = None
    family = output_config.name

    if name is None and "labels" in cfg:
        name = cfg["labels"][0]

    if not reg:
        reg = cfg.get("reg")

    if cfg.get("reg_format", "hex") != "hex":
        reg_is_hex = False
    else:
        reg_is_hex = True

    if peripheral and not reg:
        start = peripheral.base_address
        if cfg.get("reg_mode") == "narrow":
            size = peripheral.registers[-1].address_offset + 4
        else:
            size = peripheral.address_blocks[0].size * 4
        reg = [start, size]

    p = Node(
        cfg.get("node", name),
        labels=cfg.get("labels", [name] if name else None),
        compatible=binding.compatible if binding else None,
        reg=reg,
        peripheral_name=name,
        reg_is_hex=reg_is_hex,
    )

    if "address" in cfg:
        p.address = cfg["address"]

    if binding:
        # Add required constants from binding
        if not cfg.get("skip_default_properties", False):
            for prop, spec in binding.prop2specs.items():
                if spec.required and spec.const is not None:
                    p.add_prop(property_from_string(spec.type, prop, spec.const))

        # Add values from config yaml
        for prop, val in cfg.get("properties", {}).items():
            if prop == "ranges":
                t = "boolean" if isinstance(val, bool) else "array"
                p.add_prop(property_from_string(t, prop, val))
            else:
                spec = binding.prop2specs.get(prop)
                assert spec, f"No spec found for {prop} in {binding.compatible}"
                p.add_prop(property_from_string(spec.type, prop, val))

        # Add peripheral-id if required by the binding
        # This should disappear once all drivers use clock control
        if pid := binding.prop2specs.get("peripheral-id"):
            if pid.required:
                peripheral_id = name.removeprefix(p.name)
                p.add_int("peripheral-id", peripheral_id)

    # Add child nodes
    for child in cfg.get("children", []):
        if h := child.get("handler"):
            if h == "gpio":
                em4_pins = {}
                for wu, (port, pin) in output_config.cmsis.get("routes.gpio").items():
                    if not wu.startswith("em4wu"):
                        continue
                    wu = int(wu[5:], 10)
                    if port not in em4_pins:
                        em4_pins[port] = []
                    em4_pins[port].append((wu, pin))

                for reg in peripheral.registers:
                    if m := re.match("PORT(.)_CTRL", reg.name):
                        port = m.group(1).lower()
                        if pins := em4_pins.get(port):
                            child["properties"]["silabs,wakeup-ints"] = [
                                [v[0]] for v in pins
                            ]
                            child["properties"]["silabs,wakeup-pins"] = [
                                [v[1]] for v in pins
                            ]
                        create_node_from_config(
                            p,
                            output_config,
                            child,
                            bindings,
                            f"gpio{port}",
                            None,
                            [peripheral.base_address + reg.address_offset, 0x30],
                        )
            if h == "extmem":
                child["reg"] = reg
                create_node_from_config(p, output_config, child, bindings)
        else:
            create_node_from_config(p, output_config, child, bindings)

    if s := cfg.get("status"):
        p.status(s)

    parent.add_node(p)

    if inc := cfg.get("include"):
        p.get_root().add_include(inc.replace("{config}", family))

    if c := cfg.get("chosen"):
        p.get_root().find("chosen").select(c, p)

    for sibling in cfg.get("siblings", []):
        sibling_name = None
        sibling_reg = None
        if h := sibling.get("handler"):
            if h == "pinctrl":
                dbus = next(
                    filter(lambda r: r.name == "DBGROUTEPEN", peripheral.registers)
                ).address_offset
                abus = next(
                    filter(lambda r: r.name == "ABUSALLOC", peripheral.registers)
                ).address_offset
                sibling_name = "pinctrl"
                sibling_reg = {
                    "dbus": [
                        peripheral.base_address + dbus,
                        peripheral.address_blocks[0].size - dbus,
                    ],
                    "abus": [peripheral.base_address + abus, 0x40],
                }
            elif h == "clkin0":
                for reg in peripheral.registers:
                    if reg.name == "CMU_CLKIN0ROUTE":
                        sibling_name = "clkin0"
                        sibling_reg = [
                            peripheral.base_address + reg.address_offset,
                            0x4,
                        ]
            else:
                raise ValueError(f"No sibling handler '{h}' for {name}")
        create_node_from_config(
            parent, output_config, sibling, bindings, sibling_name, None, sibling_reg
        )

    return p


def add_interrupts_to_node(node, svd, extra_interrupt_names, interrupt_numbers, prio=2):
    """
    Add interrupts to a devicetree node.
    """
    interrupts = {}

    if svd:
        for i in svd.interrupts:
            if i.name.endswith(("_RX", "_TX")):
                peripheral, dts_name = i.name.lower().split("_")
                if not svd.name.lower().startswith(peripheral):
                    logger.warning(
                        "Skip interrupt with mismatched name: %s for %s",
                        i.name,
                        svd.name,
                    )
                    continue
            else:
                dts_name = i.name.lower()
            interrupts[dts_name] = [i.value, prio]

    for int_name in extra_interrupt_names:
        if int_name.endswith(("_rx", "_tx")):
            dts_name = int_name.split("_")[-1]
        else:
            dts_name = int_name
        if dts_name not in interrupts and int_name in interrupt_numbers:
            interrupts[dts_name] = [interrupt_numbers[int_name], prio]

    if interrupts:
        if "sysrtc_app" in interrupts:
            # Ensure app interrupt comes first
            interrupts = dict(sorted(interrupts.items(), key=lambda item: item[0]))
        else:
            interrupts = dict(sorted(interrupts.items(), key=lambda item: item[1]))
        node.add_array("interrupts", list(interrupts.values()))
        node.add_string_array("interrupt-names", list(interrupts.keys()))


def get_max_output_power(cmsis: util.sdk.CmsisDeviceConfig) -> int:
    """
    Get the maximum output power of the highest-power PA of a given device.
    """
    try:
        return cmsis.get("device.efr32_subghz_hp_pa_max_output")
    except KeyError:
        pass

    try:
        return cmsis.get("device.efr32_2g4hz_hp_pa_max_output")
    except KeyError:
        pass

    try:
        return cmsis.get("device.efr32_2g4hz_mp_pa_max_output")
    except KeyError:
        pass

    try:
        return cmsis.get("device.efr32_2g4hz_lp_pa_max_output")
    except KeyError:
        return 0


def create_soc_device_tree(
    soc: str,
    family: util.soc.FamilyConfig,
    shared_config: util.soc.SharedConfig,
    cmsis: util.sdk.CmsisDeviceConfig,
    module_config: dict,
):
    """
    Create SoC-specific devicetree including the family devicettree and setting any
    SoC-specific properties.
    """
    generic_family_name = shared_config.name
    soc_dt = Node("/")
    soc_dt.add_include("mem.h")
    soc_dt.add_include(f"silabs/{generic_family_name}/{family.name}.dtsi")
    compatibles = [
        f"silabs,{soc}",
        f"silabs,{family.name}",
        f"silabs,{generic_family_name}",
    ]

    if family.any("device_has_radio"):
        compatibles.append("silabs,efr32")
    else:
        compatibles.append("silabs,efm32")
    compatibles.append("simple-bus")
    soc_dt.add_node(Node("soc", compatible=compatibles))

    nodes = [soc_dt]

    if family.any("device_supports_bluetooth") and not family.soc_has(
        soc, "device_supports_bluetooth"
    ):
        nodes.append(DeleteNode(label="bt_hci_silabs"))

    dcdc = Node(labels=["dcdc"])
    if module_config.get("SL_DEVICE_INIT_DCDC_PFMX_IPKVAL_OVERRIDE") == "1":
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
        ipkval = module_config.get("SL_DEVICE_INIT_DCDC_PFMX_IPKVAL", 120)
        dcdc.add_int("silabs,pfmx-peak-current-milliamp", ipkvals[ipkval])
    if "device_dcdc_boost" in family.provides.get(
        soc
    ) and "device_dcdc_buck" not in family.provides.get(soc):
        dcdc.add_bool("regulator-boot-on", True)
        dcdc.add_int("regulator-initial-mode", "SILABS_DCDC_MODE_BOOST")
        dcdc.add_int("regulator-init-microvolt", 1800000)
        dcdc.status("okay")
    if dcdc.props:
        nodes.append(dcdc)
        soc_dt.add_include("zephyr/dt-bindings/regulator/silabs_dcdc.h")

    try:
        flash_size = cmsis.get("memory.flash.size")
    except KeyError:
        flash_size = 0
    flash = Node(labels=["flash0"])
    flash.add_hex_array(
        "reg",
        [
            cmsis.get("memory.flash.base"),
            f"DT_SIZE_K({flash_size // 1024})",
        ],
    )
    flash.add_hex_array(
        "ranges",
        [
            0,
            cmsis.get("memory.flash.base"),
            f"DT_SIZE_K({flash_size // 1024})",
        ],
    )
    nodes.append(flash)

    if hfxo_en := module_config.get("SL_CLOCK_MANAGER_HFXO_EN"):
        if hfxo_en == "SL_CLOCK_MANAGER_HFXO_EN_ENABLE":
            hfxo = Node(labels=["hfxo"])

            freq = int(module_config.get("SL_CLOCK_MANAGER_HFXO_FREQ"), 10)
            if freq not in [38400000, 39000000]:
                if (freq % 1000000) == 0:
                    freq = f"DT_FREQ_M({freq // 1000000})"
                else:
                    freq = f"DT_FREQ_K({freq // 1000})"
                hfxo.add_int("clock-frequency", freq)

            hfxo.add_array("ctune", [int(module_config["SL_CLOCK_MANAGER_HFXO_CTUNE"])])
            hfxo.add_int(
                "precision",
                module_config["SL_CLOCK_MANAGER_HFXO_PRECISION"],
            )
            hfxo.status("okay")
            nodes.append(hfxo)

    if lfxo_en := module_config.get("SL_CLOCK_MANAGER_LFXO_EN"):
        if lfxo_en == "1":
            lfxo = Node(labels=["lfxo"])
            lfxo.add_int("ctune", module_config["SL_CLOCK_MANAGER_LFXO_CTUNE"])
            lfxo.add_int(
                "precision",
                module_config["SL_CLOCK_MANAGER_LFXO_PRECISION"],
            )
            lfxo.status("okay")
            nodes.append(lfxo)
            soc_dt.add_include(f"silabs/{generic_family_name}/clock-lfxo.dtsi")
        else:
            lfrco = Node(labels=["lfrco"])
            lfrco.add_bool("precision-mode", True)
            nodes.append(lfrco)

    radio = Node(labels=["radio"])
    if (
        family.any("device_has_radio")
        and shared_config.any("device_has_radio_2g4hz")
        and not family.soc_has(soc, "device_has_radio_2g4hz")
    ):
        radio.add_prop(DeleteProperty("pa-2p4ghz"))
    if (
        family.any("device_has_radio")
        and shared_config.any("device_has_radio_subghz")
        and not family.soc_has(soc, "device_has_radio_subghz")
    ):
        radio.add_prop(DeleteProperty("pa-subghz"))

    if family.soc_has(soc, "device_has_radio"):
        family_max_power = get_max_output_power(shared_config.cmsis)
        soc_max_power = get_max_output_power(cmsis)
        if soc_max_power != family_max_power:
            radio.add_int("pa-max-power-dbm", soc_max_power)

    if voltage := module_config.get("SL_RAIL_UTIL_PA_VOLTAGE_MV"):
        if int(voltage) != 3300:
            radio.add_int("pa-voltage-mv", module_config["SL_RAIL_UTIL_PA_VOLTAGE_MV"])

    for prop, feature in BT_FEATURES.items():
        if family.soc_has(soc, feature) and not shared_config.all(
            feature, radio_only=True
        ):
            radio.add_bool(prop, True)

    if radio.props:
        nodes.append(radio)

    sram = Node(labels=["sram0"])
    sram.add_hex_array(
        "reg",
        [
            cmsis.get("memory.sram.base"),
            f"DT_SIZE_K({cmsis.get('memory.sram.size') // 1024})",
        ],
    )
    nodes.append(sram)

    for g in ["a", "b", "c", "d"]:
        mask = cmsis.get(f"P{g.upper()}_MASK", "gpio")
        ngpios = mask.bit_length()
        reserved = []
        in_reserved = False
        for i in range(ngpios):
            if ~mask & 2**i:
                if not in_reserved:
                    reserved.append([i])
                    in_reserved = True
            else:
                if in_reserved:
                    reserved[-1].append(i - reserved[-1][0])
                    in_reserved = False

        gpio = Node(labels=[f"gpio{g}"])
        gpio.add_int("ngpios", ngpios)
        if reserved:
            gpio.add_array("gpio-reserved-ranges", reserved)
        nodes.append(gpio)

    nodes.sort(key=lambda n: (n.labels, n.name))
    return nodes
