# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    node = Node(labels=["wdog0"], status="okay")

    dt.find("aliases").select("watchdog0", node)

    return [node]
