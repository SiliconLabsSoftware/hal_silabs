# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    candidates = ["vdac0", "vdac1"]
    nodes = []

    for dac in candidates:
        if f"device_has_{dac}" in b.soc_features:
            node = Node(labels=[dac], status="okay")
            nodes.append(node)

    return nodes
