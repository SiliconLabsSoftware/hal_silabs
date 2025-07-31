# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node, PinctrlGroup
from dts.prop import (
    ArrayProperty,
    IntProperty,
    BoolProperty,
    Uint8ArrayProperty,
    StringProperty,
)

flashes = {
    "mx25r8035f": [
        Uint8ArrayProperty("jedec-id", [0xC2, 0x28, 0x14]),
        ArrayProperty("dpd-wakeup-sequence", [30000, 20, 35000]),
        BoolProperty("has-dpd", True),
        StringProperty("mxicy,mx25r-power-mode", "low-power"),
        BoolProperty("zephyr,pm-device-runtime-auto", True),
        IntProperty("size", "DT_SIZE_M(8)"),
        IntProperty("spi-max-frequency", "DT_FREQ_M(33)"),
    ],
    "mx25r3235f": [
        Uint8ArrayProperty("jedec-id", [0xC2, 0x28, 0x16]),
        ArrayProperty("dpd-wakeup-sequence", [30000, 20, 35000]),
        BoolProperty("has-dpd", True),
        StringProperty("mxicy,mx25r-power-mode", "low-power"),
        BoolProperty("zephyr,pm-device-runtime-auto", True),
        IntProperty("size", "DT_SIZE_M(32)"),
        IntProperty("spi-max-frequency", "DT_FREQ_M(80)"),
    ],
}


def default_spi_config(label):
    node = Node(labels=[label], status="okay")
    node.add_int("#address-cells", 1)
    node.add_int("#size-cells", 0)
    node.add_int("clock-frequency", "DT_FREQ_M(8)")

    return {
        "node": node,
        "out_signals": set(),
        "in_signals": set(),
        "reg": 0,
    }


def add_cs_gpio(b: Board, node: Node, key: str, polarity: bool = None):
    if gpio := node.prop("cs-gpios"):
        gpio.value += b.gpios([key], "cs-gpios", polarity=polarity, raw=True)
    else:
        node.add_prop(b.gpios([key], "cs-gpios", polarity=polarity))


def create_on_bus(node, name, compatible=None):
    reg = 0
    if len(node.nodes):
        reg = node.nodes[-1].address + 1

    child = Node(
        name, labels=[name], compatible=compatible, reg=[reg], reg_is_hex=False
    )
    node.add_node(child)

    return child


def generate(b: Board, dt: Node, pinctrl: Node):
    peripherals = {}

    if flash := b.config.get("SL_MX25_FLASH_SHUTDOWN_PERIPHERAL"):
        if flash not in peripherals:
            peripherals[flash] = default_spi_config(flash.lower())

        peripherals[flash]["out_signals"].update(
            b.signals(
                flash,
                "SL_MX25_FLASH_SHUTDOWN",
                ["TX", "SCLK" if flash.startswith("E") else "CLK"],
            )
        )
        peripherals[flash]["in_signals"].update(
            b.signals(flash, "SL_MX25_FLASH_SHUTDOWN", ["RX"])
        )

        add_cs_gpio(b, peripherals[flash]["node"], "SL_MX25_FLASH_SHUTDOWN_CS", False)

        child = create_on_bus(
            peripherals[flash]["node"], b.spi_flash, compatible="jedec,spi-nor"
        )
        if data := flashes.get(b.spi_flash):
            child.add_props(data)
        dt.find("aliases").select("spi-flash0", child)

    if display := b.config.get("SL_MEMLCD_SPI_PERIPHERAL"):
        if display not in peripherals:
            peripherals[display] = default_spi_config(display.lower())

        peripherals[display]["out_signals"].update(
            b.signals(
                display,
                "SL_MEMLCD_SPI",
                ["TX", "SCLK" if display.startswith("E") else "CLK"],
            )
        )

        add_cs_gpio(b, peripherals[display]["node"], "SL_MEMLCD_SPI_CS", True)

        child = create_on_bus(
            peripherals[flash]["node"], b.display, compatible="sharp,ls0xx"
        )
        child.add_int("height", 128)
        child.add_int("width", 128)
        child.add_int("spi-max-frequency", "DT_FREQ_K(1100)")
        try:
            child.add_prop(b.gpios(["SL_MEMLCD_EXTCOMIN"], "extcomin-gpios"))
            child.add_int("extcomin-frequency", 60)
        except KeyError:
            pass
        try:
            child.add_prop(b.gpios(["SL_BOARD_ENABLE_DISPLAY"], "disp-en-gpios"))
        except KeyError:
            pass

        dt.find("chosen").select("zephyr,display", child)

    if mikrobus := b.config.get("SL_SPIDRV_EUSART_MIKROE_PERIPHERAL"):
        if mikrobus not in peripherals:
            peripherals[mikrobus] = default_spi_config(mikrobus.lower())

        peripherals[mikrobus]["node"].labels.append("mikrobus_spi")
        peripherals[mikrobus]["node"].labels.append("zephyr_spi")

        peripherals[mikrobus]["out_signals"].update(
            b.signals(mikrobus, "SL_SPIDRV_EUSART_MIKROE", ["TX", "SCLK"])
        )
        peripherals[mikrobus]["in_signals"].update(
            b.signals(mikrobus, "SL_SPIDRV_EUSART_MIKROE", ["RX"])
        )

        add_cs_gpio(
            b, peripherals[mikrobus]["node"], "SL_SPIDRV_EUSART_MIKROE_CS", True
        )

    for name, data in peripherals.items():
        pins, props = b.pinctrl(
            name.lower(),
            "default",
            PinctrlGroup(
                "group0",
                data["out_signals"],
                "drive-push-pull",
                "output-high",
            ),
            PinctrlGroup(
                "group1",
                data["in_signals"],
                "input-enable",
                "silabs,input-filter",
            ),
        )
        pinctrl.add_node(pins)
        data["node"].add_props(props)

    return [p["node"] for p in peripherals.values()]
