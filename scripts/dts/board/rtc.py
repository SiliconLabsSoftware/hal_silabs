# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    candidates = ["sysrtc0", "rtcc0"]

    for rtc in candidates:
        if f"device_has_{rtc}" in b.soc_features:
            node = Node(labels=[rtc], status="okay")
            return [node]
