# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from pathlib import Path

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    button_spec = {
        "button0": "SL_SIMPLE_BUTTON_BTN0",
        "button1": "SL_SIMPLE_BUTTON_BTN1",
        "button2": "SL_SIMPLE_BUTTON_BTN2",
    }
    buttons = []
    for label, define in button_spec.items():
        if define + "_PORT" not in b.config:
            continue
        btn = Node(f"button_{label[-1]}", [label])
        btn.add_prop(b.gpios([define], "gpios", False))
        btn.add_string("label", f"Push Button {label[-1]}")
        btn.add_int("zephyr,code", f"INPUT_BTN_{label[-1]}")
        buttons.append(btn)

    if buttons:
        aliases = dt.find("aliases")

        buttons_dt = Node("buttons", compatible="gpio-keys")
        for btn in buttons:
            buttons_dt.add_node(btn)
            aliases.select(f"sw{btn.labels[0][-1]}", btn)
        dt.add_node(buttons_dt)

        dt.add_include("zephyr/dt-bindings/input/input-event-codes.h")
