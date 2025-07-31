# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    candidates = {"semailbox": "se", "cryptoacc": "trng"}

    for feat, label in candidates.items():
        if f"device_has_{feat}" in b.soc_features:
            node = Node(labels=[label], status="okay")
            return [node]
