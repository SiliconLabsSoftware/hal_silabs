# Copyright (c) 2026 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

from pathlib import Path

import yaml

from dts.node import Node
from dts.prop import PhandleArrayProperty, PhandleProperty, StringArrayProperty

from . import sdk


class BoardDb:
    def __init__(self, board_dir: Path):
        self._dir = board_dir
        self._boards = {}
        for f in (board_dir / "component").glob("*.slcc"):
            slcc = dict(yaml.safe_load(Path(f).read_text(encoding="utf-8")))
            self._boards[slcc["id"]] = slcc

    def get(self, board: str):
        return self._boards.get(board)

    def config(self, board: str):
        f = self._dir / "config" / "component" / f"{board}_config.slcc"
        slcc = dict(yaml.safe_load(f.read_text(encoding="utf-8")))
        return slcc

    def providing(self, req: str):
        for board in self._boards.values():
            if any(p["name"] == req for p in board.get("provides")):
                return board


class Board:
    def __init__(
        self, board_name: str, boards: BoardDb, soc_root: Path, dts_root: Path
    ):
        # Get kit data for board name
        if not (kit := boards.get(board_name)):
            raise ValueError(f"Unknown board: {board_name}")

        # Get board data for kit
        for r in kit.get("requires"):
            req = r["name"]
            if req.startswith("hardware_board_from_"):
                board = boards.providing(req)
                if not board:
                    raise ValueError(f"No board provides {req}")

        # Resolve board revisions if board has multiple revisions
        for r in board.get("requires"):
            if r["name"].endswith("_revision"):
                for rec in board.get("recommends"):
                    if board := boards.get(rec["id"]):
                        break
                else:
                    raise ValueError(f"No board revision provides {r['name']}")

        self._kit = kit
        self._board = board

        pn = self._tag("board:pn:") + self._tag("board:variant:")
        config = boards.config(pn.lower())
        config_dir = list(
            set(
                Path(c["path"]).parent
                for c in config.get("config_file")
                if c.get("condition") in [None, ["brd4002a"]]
            )
        )[0]
        self.config = sdk.defines_from_dir(boards._dir / "config" / config_dir)

        soc_component = list(soc_root.rglob(f"{self.soc}.slcc"))[0]
        soc_header = list(soc_root.rglob(f"{self.soc}.h"))[0]
        _, self.soc_features = sdk.get_device_features(soc_component)
        self.soc_config = sdk.CmsisDeviceConfig(soc_header)

        self.soc_dtsi = list(dts_root.rglob(f"{self.soc}.dtsi"))[0].relative_to(
            dts_root
        )
        self.soc_dir = self.soc_dtsi.parent
        self.soc_family = self.soc_dir.name

    @property
    def id(self) -> str:
        return self._kit["id"]

    def _tag(self, key, multiple=False) -> str:
        vals = []
        for t in self._board["tag"]:
            if t.startswith(key):
                val = t[len(key) :]
                if multiple:
                    vals.append(val)
                else:
                    return val
        for t in self._kit["tag"]:
            if t.startswith(key):
                val = t[len(key) :]
                if multiple:
                    vals.append(val)
                else:
                    return val
        if multiple:
            return vals
        else:
            raise KeyError(f"Tag not found: {key}")

    @property
    def name(self) -> str:
        return self._tag("kit:opn:")

    @property
    def soc(self) -> str:
        return self._tag("board:device:")

    @property
    def sensors(self) -> list[str]:
        return self._tag("hardware:has:sensor:", multiple=True)

    @property
    def spi_flash(self) -> str | None:
        flash = None
        try:
            flash = self._tag("hardware:has:memory:spi:")
        except:
            pass
        return flash

    @property
    def display(self) -> str | None:
        flash = None
        try:
            flash = self._tag("hardware:has:display:")
        except:
            pass
        return flash

    def gpios(self, keys, prop_name, polarity=None, raw=False):
        value = []
        for key in keys:
            port = self.config[f"{key}_PORT"]
            pin = self.config[f"{key}_PIN"]
            if polarity is None:
                polarity = "HIGH" in self.config.get(f"{key}_POLARITY", "HIGH")

            value.append(
                [
                    f"gpio{port[-1].lower()}",
                    pin,
                    "GPIO_ACTIVE_HIGH" if polarity else "GPIO_ACTIVE_LOW",
                ]
            )

        if raw:
            return value
        else:
            return PhandleArrayProperty(prop_name, value)

    def signals(self, peripheral_name, prefix, signals):
        out = []
        for signal in signals:
            port = self.config[f"{prefix}_{signal}_PORT"]
            pin = self.config[f"{prefix}_{signal}_PIN"]

            out.append(f"{peripheral_name}_{signal}_P{port[-1]}{pin}")

        return out

    def pinctrl(self, name, mode, *groups):
        pins = Node(f"{name}_{mode}", labels=[f"{name}_{mode}"])

        for group in groups:
            pins.add_node(group)

        props = [
            PhandleProperty("pinctrl-0", f"{name}_{mode}"),
            StringArrayProperty("pinctrl-names", [mode]),
        ]

        return pins, props
