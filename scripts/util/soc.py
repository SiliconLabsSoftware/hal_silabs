# Copyright (c) 2025 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

import copy
from pathlib import Path

import yaml

import util.sdk
from dts.prop import DeferredValue


class GenConfig:
    def __init__(self, path: Path):
        cfg = yaml.safe_load(path.read_text())
        self._configs = cfg.get("configs", [])
        self._config = None
        self.peripherals = cfg.get("peripherals", [])
        self.clocks = ClockConfig(cfg.get("clocks", {}))
        self.sdk = None
        self.provides = None

    @property
    def config_names(self):
        return list(map(lambda c: c["name"], self._configs))

    def select_config(self, name, sdk):
        self.sdk = sdk
        provides = util.sdk.get_device_provides(self.sdk)
        for config in self._configs:
            if config["name"] == name:
                self._config = SharedConfig(config, self.sdk, provides)
                break
        else:
            raise ValueError(
                f"Configuration '{name}' not found in device configuration."
            )

        self.peripherals = self._resolve_values(copy.deepcopy(self.peripherals), name)
        for k, v in self.clocks.selection.items():
            self.clocks.selection[k] = self._resolve_value(
                f"clocks.selection.{k}", v, name
            )

    @property
    def config(self):
        return self._config

    def _resolve_value(self, prop, val, family):
        if isinstance(val, list) and isinstance(val[0], dict) and "when" in val[0]:
            for opt in val:
                if family in opt.get("when", [family]) or "when" not in opt:
                    val = opt.get("value")
                    break
            else:
                raise ValueError(
                    f"No matching option found for {prop} (family {family})"
                )
        elif isinstance(val, dict) and "cmsis_symbol" in val:
            val = DeferredValue(val["cmsis_symbol"])

        return val

    def _resolve_values(self, cfgs, family):
        for cfg in cfgs:
            for prop, val in cfg.get("properties", {}).items():
                cfg["properties"][prop] = self._resolve_value(prop, val, family)
            if "address" in cfg:
                cfg["address"] = self._resolve_value("address", cfg["address"], family)
            if "children" in cfg:
                cfg["children"] = self._resolve_values(cfg.get("children", []), family)
            if "binding" in cfg:
                cfg["binding"] = self._resolve_value("binding", cfg["binding"], family)

        return cfgs


class FamilyConfig:
    """
    Configuration for a SoC family, e.g. efr32mg24
    """

    def __init__(self, cfg):
        self.name = cfg["name"]
        self.representative_device = cfg.get("representative_device")
        self.provides = None

    def soc_has(self, soc, needle):
        """
        Returns true if the given ``soc`` provides every feature in ``needle``
        """
        if not isinstance(needle, list):
            needle = [needle]

        return all(n in self.provides.get(soc) for n in needle)

    def any(self, needle):
        """
        Returns true if any soc in the family provides every feature in ``needle``
        """
        if not isinstance(needle, list):
            needle = [needle]

        return any(
            all(n in provides for n in needle) for _, provides in self.provides.items()
        )

    def all(self, needle):
        """
        Returns true if all socs in the family provide every feature in ``needle``
        """
        if not isinstance(needle, list):
            needle = [needle]

        return all(
            all(n in provides for n in needle) for _, provides in self.provides.items()
        )


class SharedConfig:
    """
    Configuration for a generic family, e.g. xg24
    """

    def __init__(self, config, sdk, provides):
        self.name = config["name"]
        self.clocks = util.sdk.get_clock_config(config["clocks"])
        self.families = [FamilyConfig(family) for family in config["families"]]
        for family in self.families:
            if family.name in provides[f"efr32{self.name}"]:
                family.provides = provides[f"efr32{self.name}"][family.name]
            else:
                family.provides = provides["mcu"][family.name]

        representative_cmsis_path = (
            sdk
            / "SiliconLabs"
            / self.families[0].name.upper()
            / "Include"
            / f"{self.families[0].representative_device.lower()}.h"
        )
        self.cmsis = util.sdk.CmsisDeviceConfig(representative_cmsis_path)

    def any(self, provides):
        """
        Returns true if any soc in any family provides every feature in ``provides``
        """
        return any(f.any(provides) for f in self.families)

    def all(self, provides, radio_only=False):
        """
        Returns true if all socs in all families provide every feature in ``provides``.
        If ``radio_only`` is true, only socs with a radio are checked.
        """

        if radio_only:
            return all(
                f.all(provides) or not f.any("device_has_radio") for f in self.families
            )
        else:
            return all(f.all(provides) for f in self.families)


class ClockConfig:
    extra_children: dict[str, list[str]]
    selection: dict[str, str]
    skip: list[str]
    divider: dict[str, int]

    def __init__(self, cfg: dict):
        self.extra_children = cfg.get("extra_children", {})
        self.selection = cfg.get("selection", {})
        self.skip = cfg.get("skip", [])
        self.divider = cfg.get("divider", {})
