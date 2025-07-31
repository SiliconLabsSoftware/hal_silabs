# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    if b.config.get(f"SL_I2C_QWIIC_PERIPHERAL"):
        gpio_map = []
        for i, p in enumerate(["SCL", "SDA"]):
            prefix = f"SL_I2C_QWIIC_{p}"
            if prefix + "_PORT" not in b.config:
                continue

            port = "&gpio" + b.config.get(prefix + "_PORT")[-1].lower()
            pin = b.config.get(prefix + "_PIN")

            gpio_map.append([i, 0, port, pin, 0])

        if gpio_map:
            conn = Node(
                "stemma-qt-connector",
                labels=["qwiic_connector"],
                compatible="stemma-qt-connector",
            )
            conn.add_int("#gpio-cells", 2)
            conn.add_array("gpio-map", gpio_map)
            conn.prop("gpio-map").fmt_one_element_per_line = True
            conn.add_hex_array("gpio-map-mask", [0xFFFFFFFF, 0x0])
            conn.add_hex_array("gpio-map-pass-thru", [0x0, "GPIO_DT_FLAGS_MASK"])

            dt.add_node(conn)
