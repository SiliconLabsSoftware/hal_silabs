#!/usr/bin/env python3

# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

import argparse
import importlib
import logging
import os
import pkgutil
from pathlib import Path

import dts.board
from util import copyright_header, board
from dts.node import Node, ChosenNode

logger = logging.getLogger(__name__)

ZEPHYR_BASE = Path(os.getenv("ZEPHYR_BASE"))


def main():
    parser = argparse.ArgumentParser(
        description="Generate .dts files for Series 2 boards."
    )

    parser.add_argument(
        "--out",
        "-o",
        type=Path,
        default=Path(__file__).parent / "out",
        help="Output directory. Defaults to the directory ./out/ relative to the script. "
        "Set to a directory in $ZEPHYR_BASE/boards/silabs/ to directly generate output "
        "into the expected location within the Zephyr main tree.",
    )

    parser.add_argument(
        "--sdk",
        "-s",
        type=Path,
        default=Path(__file__).parent.parent / "simplicity_sdk",
        help="Path to Simplicity SDK to extract data from. Defaults to the directory "
        "../simplicity_sdk relative to the script.",
    )

    parser.add_argument(
        "--board",
        "-b",
        default="xg24_dk2601b",
        help="Device family to generate .dtsi for. Defaults to xg24_dk2601b if not set.",
    )
    parser.add_argument(
        "--verbose",
        "-v",
        action="store_true",
        help="Enable debug logging.",
    )

    args = parser.parse_args()

    logging.basicConfig(
        level=logging.DEBUG if args.verbose else logging.INFO,
        format="%(message)s",
    )

    args.out.mkdir(exist_ok=True)

    kit_pn = args.board.replace("_", "-")

    if (args.sdk / "devices").exists():
        soc_dir = args.sdk / "devices" / "platform" / "Device"
        board_dir = args.sdk / "boards" / "hardware" / "board"
    elif (args.sdk / "platform_core").exists():
        soc_dir = args.sdk / "platform_core" / "platform" / "Device"
        board_dir = args.sdk / "boards" / "hardware" / "board"
    else:
        soc_dir = args.sdk / "platform" / "Device"
        board_dir = args.sdk / "hardware" / "board"

    dts_root = ZEPHYR_BASE / "dts" / "arm"

    boards = board.BoardDb(board_dir)
    b = board.Board(args.board, boards, soc_dir, dts_root)

    nodes = []
    dt = Node("/")
    dt.root = True
    dt.add_include(b.soc_dtsi, priority=-100)

    dt.add_node(ChosenNode("aliases"))
    dt.add_node(ChosenNode("chosen"))

    dt.add_string("model", f"Silicon Labs {b.name}")
    dt.add_string("compatible", f"silabs,{b.id}")

    pinctrl = Node(labels=["pinctrl"])

    for _loader, module_name, _is_pkg in pkgutil.iter_modules(dts.board.__path__):
        full_name = f"{dts.board.__name__}.{module_name}"
        module = importlib.import_module(full_name)

        n = module.generate(b, dt, pinctrl)
        if n:
            nodes += n
    nodes.sort(key=lambda n: n.labels)

    for node in nodes:
        dt.update_includes(node)
        node.remove_includes()

    pinctrl_file = f"{args.board}-pinctrl.dtsi"
    dt.add_include(pinctrl_file, local=True)

    # Write the output to a .dts file
    nodes = [dt] + nodes
    out_path = args.out / f"{args.board}.dts"
    out_path.parent.mkdir(parents=True, exist_ok=True)
    logger.info("Creating %s", out_path.name)
    copyright_string = copyright_header.from_path(out_path)
    out_path.write_text(
        copyright_string + "\n".join([str(node) for node in nodes]), encoding="utf-8"
    )

    pinctrl_path = args.out / pinctrl_file
    pinctrl_path.parent.mkdir(parents=True, exist_ok=True)
    logger.info("Creating %s", pinctrl_path.name)
    copyright_string = copyright_header.from_path(pinctrl_path)
    pinctrl_path.write_text(
        copyright_string + "\n".join([str(pinctrl)]), encoding="utf-8"
    )


if __name__ == "__main__":
    main()
