#!/usr/bin/env python3

# Copyright (c) 2025 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

import argparse
import logging
from pathlib import Path

import yaml

import util.copyright_header
import util.download
import util.sdk
import util.soc
from dts.soc.series2 import (
    create_device_tree,
    create_clock_device_trees,
    create_radio_device_tree,
    create_family_device_tree,
    create_soc_device_tree,
)
from dts.node import Node
from dts.prop import DeferredValue

logger = logging.getLogger(__name__)


def main():
    gen_config = util.soc.GenConfig(
        Path(__file__).parent / "dts" / "soc" / "series2.yml"
    )

    parser = argparse.ArgumentParser(
        description="Generate .dtsi files for Series 2 SoCs."
    )
    parser.add_argument(
        "--out",
        "-o",
        type=Path,
        default=Path(__file__).parent / "out",
        help="Output directory. Defaults to the directory ./out/ relative to the "
        "script. Set to $ZEPHYR_BASE/dts/arm/silabs/ to directly generate output "
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
        "--family",
        "-f",
        default="xg24",
        choices=gen_config.config_names,
        help="Device family to generate .dtsi for. Defaults to xg24 if not set.",
    )
    parser.add_argument(
        "--soc-yml",
        "-y",
        type=Path,
        help="Path to soc.yml to use for OPN filtering. Set to "
        "$ZEPHYR_BASE/soc/silabs/soc.yml to use the file in the main tree.",
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

    if (args.sdk / "devices").exists():
        devices_dir = args.sdk / "devices" / "platform" / "Device"
        modules_dir = args.sdk / "devices" / "hardware" / "module" / "config"
    elif (args.sdk / "platform_core").exists():
        devices_dir = args.sdk / "platform_core" / "platform" / "Device"
        modules_dir = args.sdk / "platform_core" / "hardware" / "module" / "config"
    else:
        devices_dir = args.sdk / "platform" / "Device"
        modules_dir = args.sdk / "hardware" / "module" / "config"

    soc_filter = {}
    if args.soc_yml and args.soc_yml.exists():
        soc_yml = yaml.safe_load(args.soc_yml.read_text(encoding="utf-8"))
        for family in soc_yml.get("family", []):
            for series in family.get("series", []):
                soc_filter[series["name"]] = []
                for soc in series.get("socs", []):
                    soc_filter[series["name"]].append(soc["name"])

    gen_config.select_config(args.family, devices_dir)
    logger.info("Creating %s.dtsi", gen_config.config.name)

    packs = {}
    for f in gen_config.config.families:
        packs[f.name] = util.download.cmsis_pack(
            Path(__file__).parent.absolute() / "cache", f.name
        )

    # Create .dtsi file for generic soc using first family
    family = gen_config.config.families[0]
    svd_dir = packs[family.name] / "SVD" / family.name.upper()
    nodes = create_device_tree(
        family.name, family.representative_device, gen_config, svd_dir
    )

    # Write the output to a .dtsi file
    out_path = args.out / gen_config.config.name / f"{gen_config.config.name}.dtsi"
    out_path.parent.mkdir(parents=True, exist_ok=True)
    copyright_string = util.copyright_header.from_path(out_path)
    out_path.write_text(
        copyright_string + "\n".join([str(node) for node in nodes]), encoding="utf-8"
    )

    # Create .dtsi files for default clock configurations
    for clock, tree in create_clock_device_trees(nodes[0]).items():
        out_path = args.out / gen_config.config.name / f"clock-{clock}.dtsi"
        copyright_string = util.copyright_header.from_path(out_path)
        out_path.write_text(
            copyright_string + "\n".join([str(node) for node in tree]), encoding="utf-8"
        )

    # Create .dtsi file for the radio-enabled soc
    logger.info("Creating efr32%s.dtsi", gen_config.config.name)

    radio_dt = create_radio_device_tree(gen_config.config)

    out_path = args.out / gen_config.config.name / f"efr32{gen_config.config.name}.dtsi"
    out_path.parent.mkdir(parents=True, exist_ok=True)
    copyright_string = util.copyright_header.from_path(out_path)

    out_path.write_text(copyright_string + str(radio_dt), encoding="utf-8")

    for family in gen_config.config.families:
        if soc_filter:
            if family.name not in soc_filter:
                logger.info("Skipping %s, not in soc.yml", family.name)
                continue

        logger.info("Creating %s.dtsi", family.name)

        nodes = create_family_device_tree(family, gen_config.config)

        out_path = args.out / gen_config.config.name / f"{family.name}.dtsi"
        copyright_string = util.copyright_header.from_path(out_path)
        out_path.write_text(
            copyright_string + "\n".join(str(n) for n in nodes), encoding="utf-8"
        )

        svd_dir = packs[family.name] / "SVD" / family.name.upper()

        if not soc_filter:
            logger.info("Including all SoCs in %s, no soc.yml given", family.name)

        for soc in svd_dir.glob("*.svd"):
            soc = soc.stem.lower()

            if soc_filter and soc not in soc_filter.get(family.name, []):
                logger.info("Skipping %s, not in soc.yml", soc)
                continue

            logger.info("Creating %s.dtsi", soc)

            cmsis_path = (
                devices_dir
                / "SiliconLabs"
                / family.name.upper()
                / "Include"
                / f"{soc}.h"
            )
            if not cmsis_path.exists():
                raise ValueError(f"Invalid SDK path {devices_dir}")
            cmsis_config = util.sdk.CmsisDeviceConfig(cmsis_path)
            module_config = util.sdk.defines_from_dir(modules_dir / soc.upper())

            nodes = create_soc_device_tree(
                soc, family, gen_config.config, cmsis_config, module_config
            )

            out_path = args.out / gen_config.config.name / f"{soc}.dtsi"
            copyright_string = util.copyright_header.from_path(out_path)
            out_path.write_text(
                copyright_string + "\n".join(str(n) for n in nodes), encoding="utf-8"
            )


if __name__ == "__main__":
    main()
