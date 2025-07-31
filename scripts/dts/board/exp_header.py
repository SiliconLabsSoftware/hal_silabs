# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    gpio_map = []
    for i in range(3, 17):
        prefix = f"SL_HAL_GPIO_INIT_EXP_{i}"
        if prefix + "_PORT" not in b.config:
            continue

        port = "&gpio" + b.config.get(prefix + "_PORT")[-1].lower()
        pin = b.config.get(prefix + "_PIN")

        gpio_map.append([i, 0, port, pin, 0])

    if gpio_map:
        exp = Node("exp-header", labels=["exp_header"], compatible="silabs,exp-header")
        exp.add_int("#gpio-cells", 2)
        exp.add_array("gpio-map", gpio_map)
        exp.prop("gpio-map").fmt_one_element_per_line = True
        exp.add_hex_array("gpio-map-mask", [0xFFFFFFFF, 0x0])
        exp.add_hex_array("gpio-map-pass-thru", [0x0, "GPIO_DT_FLAGS_MASK"])

        dt.add_node(exp)
