# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node, PinctrlGroup


def generate(b: Board, dt: Node, pinctrl: Node):
    if b.soc_family in ["xg22"]:
        # Prefer EUART since USART can also do SPI
        candidates = [
            "SL_IOSTREAM_EUSART_VCOM",
            "SL_IOSTREAM_USART_VCOM",
        ]
    else:
        # Prefer USART
        candidates = [
            "SL_IOSTREAM_USART_VCOM",
            "SL_IOSTREAM_EUSART_VCOM",
        ]

    for c in candidates:
        if peripheral := b.config.get(c + "_PERIPHERAL"):
            node = Node(labels=[peripheral.lower()], status="okay")

            pins, props = b.pinctrl(
                peripheral.lower(),
                "default",
                PinctrlGroup(
                    "group0",
                    b.signals(peripheral, c, ["TX"]),
                    "drive-push-pull",
                    "output-high",
                ),
                PinctrlGroup(
                    "group1",
                    b.signals(peripheral, c, ["RX"]),
                    "input-enable",
                    "silabs,input-filter",
                ),
            )
            pinctrl.add_node(pins)
            node.add_props(props)
            node.add_int("current-speed", 115200)

            chosen = dt.find("chosen")
            chosen.select("zephyr,console", node)
            chosen.select("zephyr,shell-uart", node)
            chosen.select("zephyr,uart-pipe", node)

            return [node]
