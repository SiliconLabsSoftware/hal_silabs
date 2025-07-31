# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node, PinctrlGroup


def generate(b: Board, dt: Node, pinctrl: Node):
    if pti := b.config.get("SL_RAIL_UTIL_PTI_PERIPHERAL"):
        node = Node(labels=[pti.lower()], status="okay")

        pins, props = b.pinctrl(
            pti.lower(),
            "default",
            PinctrlGroup(
                "group0",
                b.signals(pti, "SL_RAIL_UTIL_PTI", ["DOUT", "DFRAME"]),
                "drive-push-pull",
                "output-high",
            ),
        )
        pinctrl.add_node(pins)
        node.add_props(props)

        return [node]
