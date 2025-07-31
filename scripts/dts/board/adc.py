# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node, PinctrlGroup


def pin_and_bus(b: Board, define: str):
    port = b.config[f"{define}_PORT"][-1]
    pin = int(b.config[f"{define}_PIN"])

    analog_bus = {
        "A": "A",
        "B": "B",
        "C": "CD",
        "D": "CD",
    }

    bus = f"{analog_bus[port]}{'ODD' if pin % 2 else 'EVEN'}0"
    portpin = f"P{port}{pin}"

    return (portpin, bus)


def generate(b: Board, dt: Node, pinctrl: Node):
    if b.config.get("SL_JOYSTICK_PORT"):
        adc = Node(labels=["adc0"], status="okay")
        channel_no = 0

        joystick = Node("joystick", compatible="adc-keys")
        joystick.add_phandle_array("io-channels", ["adc0", channel_no])
        joystick.add_int("keyup-threshold-mv", b.config.get("REFERENCE_VOLTAGE"))
        dt.add_node(joystick)

        dt.add_include("zephyr/dt-bindings/input/input-event-codes.h")

        keys = {
            "enter": "JOYSTICK_MV_C",
            "left": "JOYSTICK_MV_W",
            "down": "JOYSTICK_MV_S",
            "up": "JOYSTICK_MV_N",
            "right": "JOYSTICK_MV_E",
        }

        for key, define in keys.items():
            if mv := b.config.get(define):
                node = Node(f"{key}-key")
                node.add_int("press-thresholds-mv", mv)
                node.add_int("zephyr,code", f"INPUT_KEY_{key.upper()}")
                joystick.add_node(node)

        pin, bus = pin_and_bus(b, "SL_JOYSTICK")
        pins, props = b.pinctrl(
            "iadc0",
            "default",
            PinctrlGroup(
                "group0",
                None,
                abus=[f"ABUS_{bus}_IADC0"],
            ),
        )
        pinctrl.add_node(pins)
        adc.add_props(props)

        adc.add_int("#address-cells", 1)
        adc.add_int("#size-cells", 0)

        channel = Node("channel", reg=[channel_no])
        channel.add_int("zephyr,acquisition-time", "ADC_ACQ_TIME_DEFAULT")
        channel.add_string("zephyr,gain", "ADC_GAIN_1")
        channel.add_int("zephyr,input-positive", f"IADC_INPUT_{pin}")
        channel.add_string("zephyr,reference", "ADC_REF_VDD_1")
        channel.add_int("zephyr,resolution", 12)
        channel.add_int("zephyr,vref-mv", b.config.get("REFERENCE_VOLTAGE"))
        adc.add_node(channel)

        user = Node("zephyr,user")
        user.add_phandle_array("io-channels", ["adc0", channel_no])
        dt.add_node(user)

        adc.add_include("zephyr/dt-bindings/adc/silabs-adc.h")

        return [adc]
