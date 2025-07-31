# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    nodes = []

    if b.config.get("SL_CLOCK_MANAGER_HFXO_EN"):
        hfxo = Node(labels=["hfxo"], status="okay")
        hfxo.add_int("precision", b.config.get("SL_CLOCK_MANAGER_HFXO_PRECISION"))
        hfxo.add_array("ctune", [b.config.get("SL_CLOCK_MANAGER_HFXO_CTUNE")])
        nodes.append(hfxo)
        dt.add_include(b.soc_dir / "clock-hfrcodpll.dtsi")

    if b.config.get("SL_CLOCK_MANAGER_LFXO_EN"):
        lfxo = Node(labels=["lfxo"], status="okay")
        lfxo.add_int("precision", b.config.get("SL_CLOCK_MANAGER_LFXO_PRECISION"))
        lfxo.add_int("ctune", b.config.get("SL_CLOCK_MANAGER_LFXO_CTUNE"))
        nodes.append(lfxo)
        dt.add_include(b.soc_dir / "clock-lfxo.dtsi")

    return nodes
