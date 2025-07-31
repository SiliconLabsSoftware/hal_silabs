# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, pinctrl: Node):
    ports = {
        "gpioa": [],
        "gpiob": [],
        "gpioc": [],
        "gpiod": [],
    }

    if port := b.config.get("SL_BOARD_ENABLE_VCOM_PORT"):
        port = "gpio" + port[-1].lower()
        pin = b.config.get("SL_BOARD_ENABLE_VCOM_PIN")

        hog = Node("board-controller-enable")
        hog.add_bool("gpio-hog", True)
        hog.add_array("gpios", [pin, "GPIO_ACTIVE_HIGH"])
        hog.add_bool("output-high", True)

        ports[port].append(hog)

    nodes = []

    for port, children in ports.items():
        node = Node(labels=[port], status="okay")
        node.add_nodes(children)
        nodes.append(node)

    return nodes
