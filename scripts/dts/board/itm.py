# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node, PinctrlGroup


def generate(b: Board, dt: Node, pinctrl: Node):
    node = Node(labels=["itm"])

    pins, props = b.pinctrl(
        "itm",
        "default",
        PinctrlGroup(
            "group0",
            ["GPIO_SWV_PA3"],
            "drive-push-pull",
            "output-high",
        ),
    )
    pinctrl.add_node(pins)
    node.add_props(props)

    return [node]
