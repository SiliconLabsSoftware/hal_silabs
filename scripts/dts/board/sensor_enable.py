# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    sensors = [
        "SL_BOARD_ENABLE_SENSOR_RHT",
        "SL_BOARD_ENABLE_SENSOR_HALL",
        "SL_BOARD_ENABLE_SENSOR_PRESSURE",
        "SL_BOARD_ENABLE_SENSOR_LIGHT",
        "SL_BOARD_ENABLE_SENSOR_IMU",
        "SL_BOARD_ENABLE_SENSOR_MICROPHONE",
    ]

    nodes = {}

    for en in sensors:
        if en + "_PORT" not in b.config:
            continue
        gpios = b.gpios([en], "enable-gpios")

        name = f"{en.rsplit('_', 1)[-1].lower()}-enable"

        if str(gpios) in nodes:
            nodes[str(gpios)].labels.append(name.replace("-", "_"))
            nodes[str(gpios)].name = "sensor-enable"
        else:
            node = Node(
                name, labels=[name.replace("-", "_")], compatible="regulator-fixed"
            )
            node.add_prop(gpios)

            nodes[str(gpios)] = node

    for node in nodes.values():
        node.add_string("regulator-name", node.name)
        dt.add_node(node)
