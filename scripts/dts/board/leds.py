# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    led_spec = {
        "led0": "SL_SIMPLE_LED_LED0",
        "led1": "SL_SIMPLE_LED_LED1",
        "led2": "SL_SIMPLE_LED_LED2",
    }
    leds = []
    for label, define in led_spec.items():
        if define + "_PORT" not in b.config:
            continue
        led = Node(f"led_{label[-1]}", [label])
        led.add_prop(b.gpios([define], "gpios"))
        leds.append(led)

    if leds:
        aliases = dt.find("aliases")

        leds_dt = Node("leds", compatible="gpio-leds")
        for led in leds:
            leds_dt.add_node(led)
            aliases.select(led.labels[0], led)
        dt.add_node(leds_dt)
