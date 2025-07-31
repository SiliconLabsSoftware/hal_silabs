# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node, PinctrlGroup

sensors = {
    "veml6035": {
        "node": Node(
            "veml6035", labels=["veml6035"], compatible="vishay,veml7700", reg=[0x29]
        ),
    },
    "si7021": {
        "node": Node(
            "si7021", labels=["si7021"], compatible="silabs,si7006", reg=[0x40]
        ),
        "alias": "dht0",
        "enable": ("vin-supply", "SL_BOARD_ENABLE_SENSOR_RHT", "rht_enable"),
    },
    "si7210": {
        "node": Node(
            "si7210", labels=["si7210"], compatible="silabs,si7210", reg=[0x30]
        ),
    },
}


def generate(b: Board, dt: Node, pinctrl: Node):
    nodes = []

    if i2c := b.config.get("SL_I2C_SENSOR_PERIPHERAL"):
        node = Node(labels=[i2c.lower()], status="okay")

        pins, props = b.pinctrl(
            i2c.lower(),
            "default",
            PinctrlGroup(
                "group0",
                b.signals(i2c, "SL_I2C_SENSOR", ["SDA", "SCL"]),
                "bias-pull-up",
                "drive-open-drain",
            ),
        )
        pinctrl.add_node(pins)
        node.add_props(props)
        nodes.append(node)

        for sensor in b.sensors:
            if data := sensors.get(sensor):
                sensor_dt = data["node"]
                if en := data.get("enable"):
                    if b.config.get(en[1] + "_PORT"):
                        sensor_dt.add_phandle(en[0], en[2])

                node.add_node(sensor_dt)

                if c := data.get("chosen"):
                    dt.find("chosen").select(c, sensor_dt)

                if alias := data.get("alias"):
                    dt.find("aliases").select(alias, sensor_dt)

    connectors = {
        "QWIIC": "zephyr_i2c",
        "MIKROE": "mikrobus_i2c",
    }

    for connector, label in connectors.items():
        if i2c := b.config.get(f"SL_I2C_{connector}_PERIPHERAL"):
            for node in nodes:
                if node.labels[0] == i2c.lower():
                    node.labels.append(label)
                    break
            else:
                node = Node(labels=[i2c.lower(), label], status="okay")

                pins, props = b.pinctrl(
                    i2c.lower(),
                    "default",
                    PinctrlGroup(
                        "group0",
                        b.signals(i2c, f"SL_I2C_{connector}", ["SDA", "SCL"]),
                        "bias-pull-up",
                        "drive-open-drain",
                    ),
                )
                pinctrl.add_node(pins)
                node.add_props(props)
                nodes.append(node)

    return nodes
