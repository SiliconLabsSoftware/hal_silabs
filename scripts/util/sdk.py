# Copyright (c) 2025 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

import re
import yaml
from pathlib import Path


class CmsisDeviceConfig:
    """Represents the device configuration parsed from a CMSIS-Device header file."""

    def __init__(self, hal_file):
        text = hal_file.read_text()
        self.symbols = {}
        self.interrupts = {}

        self._load_peripheral_options(text)
        self._load_cpu_options(text)
        self._load_device_options(text)
        self._load_memory_options(text)
        self._load_interrupts(text)
        self._load_fixed_routes(text)

    def get(self, key, parent=None):
        """
        Get a configuration value from the CMSIS-Device configuration
        """
        if "." in key:
            parts = key.split(".")
            c = self.symbols
            for part in parts:
                c = c[part]
        elif parent:
            c = self.symbols[parent][key]
        else:
            raise ValueError(f"Invalid config {key}")
        return c

    def _load_interrupts(self, text):
        matches = re.findall(r"  (.*?)_IRQn\s+=\s+(\d+)", text)
        self.interrupts = {name.lower(): int(num) for name, num in matches}

    def _load_peripheral_options(self, text):
        cmsis_opts = re.findall(
            r"^#define ([A-Z0-9_]+)\s+\(?0x([0-9A-F]+)UL\)?", text, flags=re.MULTILINE
        )
        for name, value in cmsis_opts:
            peripheral, symbol = name.split("_", 1)
            if peripheral.lower() not in self.symbols:
                self.symbols[peripheral.lower()] = {}
            self.symbols[peripheral.lower()][symbol] = int(value, 16)

    def _load_cpu_options(self, text):
        cpu_opts = re.findall(
            r"^#define __([A-Z0-9_]+)_PRESENT\s+([0-9A-F]+)U", text, flags=re.MULTILINE
        )
        self.symbols["cpu"] = {
            "core": re.findall(r"^#define __([A-Z0-9]+)_REV", text, flags=re.MULTILINE)[
                0
            ].lower(),
            "nvic_prio_bits": int(
                re.findall(
                    r"^#define __NVIC_PRIO_BITS\s+([0-9]+)U", text, flags=re.MULTILINE
                )[0]
            ),
        }
        for name, value in cpu_opts:
            self.symbols["cpu"][name.lower()] = bool(value)

    def _load_device_options(self, text):
        device_opts = re.findall(
            r"^#define _SILICON_LABS_(?:(?:32B|GECKO_INTERNAL)_([A-Z0-9_]+)|"
            r"([A-Z0-9_]+)_(?:TYPE|FEATURE|DBM))\s+([0-9A-Z_]+)",
            text,
            flags=re.MULTILINE,
        )
        self.symbols["device"] = {}
        for name1, name2, value in device_opts:
            name = name1.lower() if name1 else name2.lower()
            value = value.rsplit("_", 1)[-1] if "_" in value else int(value)
            self.symbols["device"][name] = value

    def _load_memory_options(self, text):
        memory_opts = re.findall(
            r"^#define (FLASH|SRAM)_(BASE|(?:PAGE_)?SIZE)\s+\(0x([0-9A-F]+)UL\)",
            text,
            flags=re.MULTILINE,
        )
        self.symbols["memory"] = {}
        for region, prop, value in memory_opts:
            if region.lower() not in self.symbols["memory"]:
                self.symbols["memory"][region.lower()] = {}
            self.symbols["memory"][region.lower()][prop.lower()] = int(value, 16)

    def _load_fixed_routes(self, text):
        routes = {}
        for per, sig, port_pin, value in re.findall(
            r"^#define ([A-Z0-9]+)_([A-Z0-9_]+)_(PORT|PIN)\s+([0-9A-Z_]+)",
            text,
            flags=re.MULTILINE,
        ):
            per = per.lower()
            sig = sig.lower()
            if port_pin == "PORT":
                port = value[6].lower()
                if per not in routes:
                    routes[per] = {}
                if sig not in routes[per]:
                    routes[per][sig] = (port, None)
                else:
                    routes[per][sig] = (port, routes[per][sig][1])
            else:
                pin = int(value.rstrip("U"), 10)
                if per not in routes:
                    routes[per] = {}
                if sig not in routes[per]:
                    routes[per][sig] = (None, pin)
                else:
                    routes[per][sig] = (routes[per][sig][0], pin)

        self.symbols["routes"] = routes


def get_device_features(component_path: Path):
    """
    Returns all provided features from a given SLC component as a list
    """
    slcc = dict(yaml.safe_load(component_path.read_text()))
    return (slcc["id"].lower(), [p["name"] for p in slcc["provides"]])


def get_device_provides(sdk_path):
    """
    Returns a dict mapping from device family to provided features for every soc
    in the SDK.
    """
    data = {}
    component_path = sdk_path / "component"
    if not component_path.exists():
        raise ValueError(f"Invalid SDK path: {sdk_path}")

    for f in component_path.glob("*.slcc"):
        slcc_id, provides = get_device_features(f)
        family = None
        generic_family = "mcu"
        for provide in provides:
            if provide.startswith("device_family_"):
                family = provide.split("_", 2)[-1]
            if provide.startswith("device_generic_family_"):
                generic_family = provide.split("_", 3)[-1]

        if generic_family not in data:
            data[generic_family] = {}
        if family not in data[generic_family]:
            data[generic_family][family] = {}

        data[generic_family][family][slcc_id] = provides

    return data


def get_clock_config(hal_file):
    """
    Returns a dict with the configuration of every clock branch in the given
    SL Device Manager clock file from the HAL
    """
    text = (Path(__file__).parents[2] / "simplicity_sdk" / hal_file).read_text()
    matches = re.findall(
        r"const sl_peripheral_(?:[a-z0-9]+_)?val_t.*?"
        r"base = ([A-Z0-9_]+)_BASE.*?"
        r"clk_branch = SL_([A-Z0-9_]+).*?"
        r"bus_clock = SL_BUS_([A-Z0-9_]+)",
        text,
        flags=re.MULTILINE | re.DOTALL,
    )

    clocks = {}
    for base, branch, clock in matches:
        if (
            branch != "CLOCK_BRANCH_INVALID"
            or clock != "CLOCK_INVALID"
            or base in ["ACMP0", "ACMP1"]
        ):
            clocks[base.lower()] = {
                "branch": branch,
                "clock": clock if clock != "CLOCK_INVALID" else "CLOCK_AUTO",
            }

    return clocks


def defines_from_dir(dir):
    """
    Returns a dict with the configuration defines parsed from every file in the given directory.
    """
    config_defines = {}
    for f in sorted(dir.glob("*.h")):
        text = f.read_text()
        matches = re.findall(
            r"^#define ([A-Z0-9_]+)(?:[\t ]+)(.+)", text, flags=re.MULTILINE
        )
        for name, value in matches:
            if name in config_defines:
                continue
            config_defines[name] = value
    return config_defines
