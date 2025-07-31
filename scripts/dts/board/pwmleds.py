# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node, PinctrlGroup


def generate(b: Board, dt: Node, pinctrl: Node):
    led_spec = {
        "pwm_led0": "SL_PWM_LED0",
        "pwm_led1": "SL_PWM_LED1",
        "pwm_led2": "SL_PWM_LED2",
    }
    timer = "timer0"
    leds = []
    signals = []

    for label, define in led_spec.items():
        idx = label[-1]
        if define + "_OUTPUT_PORT" not in b.config:
            continue
        led = Node(f"pwm_led_{idx}", [label])

        port = b.config[f"{define}_OUTPUT_PORT"]
        pin = b.config[f"{define}_OUTPUT_PIN"]
        invert = "LOW" in b.config.get(f"{define}_POLARITY", "HIGH")

        led.add_phandle_array(
            "pwms",
            [
                f"{timer}_pwm",
                idx,
                "PWM_MSEC(20)",
                f"PWM_POLARITY_{'INVERTED' if invert else 'NORMAL'}",
            ],
        )
        leds.append(led)
        signals.append((f"TIMER0_CC{idx}_P{port[-1]}{pin}", invert))

    if leds:
        aliases = dt.find("aliases")

        dt.add_include("zephyr/dt-bindings/pwm/pwm.h")

        leds_dt = Node("pwmleds", compatible="pwm-leds")
        for led in leds:
            leds_dt.add_node(led)
            aliases.select(led.labels[0].replace("_", "-"), led)
        dt.add_node(leds_dt)

        pins, props = b.pinctrl(
            timer,
            "default",
            PinctrlGroup(
                "group0",
                [s[0] for s in signals],
                "drive-push-pull",
                "output-high" if signals[0][1] else "output-low",
            ),
        )

        pinctrl.add_node(pins)

        t = Node(labels=[timer], status="okay")

        pwm = Node("pwm", labels=[f"{timer}_pwm"], status="okay")
        for prop in props:
            pwm.add_prop(prop)
        t.add_node(pwm)

        return [t]
