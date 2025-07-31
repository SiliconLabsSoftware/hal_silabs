# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    if "device_supports_bluetooth" in b.soc_features:
        node = Node(labels=["bt_hci_silabs"], status="okay")

        dt.find("chosen").select("zephyr,bt-hci", node)
        return [node]
