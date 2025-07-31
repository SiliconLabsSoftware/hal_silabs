# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from util.board import Board
from dts.node import Node


def generate(b: Board, dt: Node, _pinctrl: Node):
    flash = Node(labels=["flash0"])
    sram = Node(labels=["sram0"])

    chosen = dt.find("chosen")
    chosen.select("zephyr,flash", flash)
    chosen.select("zephyr,sram", sram)

    partitions = Node("partitions")
    partitions.add_bool("ranges", True)
    partitions.add_int("#address-cells", 1)
    partitions.add_int("#size-cells", 1)
    flash.add_node(partitions)

    flash_size_kb = b.soc_config.get("memory.flash.size") // 1024

    boot_partition_size_kb = 48
    storage_partition_size_kb = 32

    remaining = flash_size_kb - boot_partition_size_kb - storage_partition_size_kb
    image0_pages = remaining // 16
    image0_partition_size_kb = image0_pages * 8
    image1_partition_size_kb = remaining - image0_partition_size_kb

    boot_partition = Node(
        "partition",
        compatible="zephyr,mapped-partition",
        labels=["boot_partition"],
        reg=[0, f"DT_SIZE_K({boot_partition_size_kb})"],
    )
    boot_partition.add_string("label", "mcuboot")
    partitions.add_node(boot_partition)
    offset = boot_partition_size_kb

    image0_partition = Node(
        "partition",
        compatible="zephyr,mapped-partition",
        labels=["slot0_partition"],
        reg=[offset * 1024, f"DT_SIZE_K({image0_partition_size_kb})"],
    )
    image0_partition.add_string("label", "image-0")
    partitions.add_node(image0_partition)
    dt.find("chosen").select("zephyr,code-partition", image0_partition)
    offset += image0_partition_size_kb

    image1_partition = Node(
        "partition",
        compatible="zephyr,mapped-partition",
        labels=["slot1_partition"],
        reg=[offset * 1024, f"DT_SIZE_K({image1_partition_size_kb})"],
    )
    image1_partition.add_string("label", "image-1")
    partitions.add_node(image1_partition)
    offset += image1_partition_size_kb

    storage_partition = Node(
        "partition",
        compatible="zephyr,mapped-partition",
        labels=["storage_partition"],
        reg=[offset * 1024, f"DT_SIZE_K({storage_partition_size_kb})"],
    )
    storage_partition.add_string("label", "storage")
    partitions.add_node(storage_partition)

    return [flash]
