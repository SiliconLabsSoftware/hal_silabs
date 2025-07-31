# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, pinctrl: Node):
    radio = Node(labels=["radio"])

    if voltage := b.config.get("SL_RAIL_UTIL_PA_VOLTAGE_MV"):
        if int(voltage) != 3300:
            radio.add_int("pa-voltage-mv", voltage)

    if switch_mode := b.config.get("SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_MODE"):
        if "COMBINE" in switch_mode:
            radio.add_bool("rf-path-switch-combine", True)

    if b.config.get("SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_PORT"):
        radio.add_prop(
            b.gpios(
                ["SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE"],
                "rf-path-switch-radio-active-gpios",
                True,
            )
        )

    if b.config.get("SL_RAIL_UTIL_RF_PATH_SWITCH_CONTROL_PORT"):
        radio.add_prop(
            b.gpios(
                ["SL_RAIL_UTIL_RF_PATH_SWITCH_CONTROL"],
                "rf-path-switch-control-gpios",
                False,
            )
        )

    if b.config.get("SL_RAIL_UTIL_RF_PATH_SWITCH_INVERTED_CONTROL_PORT"):
        radio.add_prop(
            b.gpios(
                ["SL_RAIL_UTIL_RF_PATH_SWITCH_INVERTED_CONTROL"],
                "rf-path-switch-control-gpios",
                True,
            )
        )

    if radio.props:
        return [radio]
    else:
        return None
