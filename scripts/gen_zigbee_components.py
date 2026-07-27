#!/usr/bin/env python3

"""
Copyright (c) 2026 Silicon Laboratories Inc.

SPDX-License-Identifier: Apache-2.0
"""

from __future__ import annotations

import argparse
import json
import re
import shutil
import textwrap
from dataclasses import dataclass, field
from pathlib import Path

from ruamel.yaml import YAML


ZIGBEE_COMPONENT_DIRS = (
    ("stack", Path("component")),
    ("app_framework", Path("app/framework/component")),
    # Util plugins (e.g. byte_utilities) live outside stack/AF component trees.
    ("util", Path("util/plugin/component")),
)

COMPONENT_SYMBOL_OVERRIDES = {
    "zigbee_debug_basic": "SILABS_SISDK_ZIGBEE_DEBUG_BASIC_COMPONENT",
    "zigbee_source_route": "SILABS_SISDK_ZIGBEE_SOURCE_ROUTE_COMPONENT",
}

EXTERNAL_COMPONENT_DEPENDENCIES = {
    "zigbee_debug_basic": ("SILABS_SISDK_ZIGBEE_DEBUG_BASIC",),
    "zigbee_gp": ("SILABS_SISDK_ZIGBEE_GREEN_POWER",),
    "zigbee_pro_leaf_stack": ("SILABS_SISDK_ZIGBEE_STACK_LEAF",),
    "zigbee_pro_router_stack": ("SILABS_SISDK_ZIGBEE_STACK_ROUTER",),
    "zigbee_pro_stack": ("SILABS_SISDK_ZIGBEE_STACK_PRO",),
    "zigbee_source_route": ("SILABS_SISDK_ZIGBEE_SOURCE_ROUTE",),
    "zigbee_zll": ("SILABS_SISDK_ZIGBEE_LIGHT_LINK",),
}

ACTIVE_CONDITION_ALIASES = {
    "btl_app_properties": ("GECKO_BOOTLOADER_INTERFACE",),
    "bootloader_app_properties": ("GECKO_BOOTLOADER_INTERFACE",),
    "cli": ("CLI",),
    "device_cortexm": (),
    "device_has_radio": (),
    "device_series_2": (),
    "legacy_hal_wdog": ("LEGACY_HAL_WDOG",),
    "power_manager": ("POWER_MANAGER",),
    "rail_util_ant_div": ("RAIL_UTIL_ANT_DIV", "SL_RAIL_UTIL_ANT_DIV"),
    "rail_util_coex": ("RAIL_UTIL_COEX",),
    "sl_main": ("SL_MAIN",),
    "sl_rail_util_ieee802154_phy_select": (
        "SL_RAIL_UTIL_IEEE802154_PHY_SELECT",
        "RAIL_UTIL_IEEE802154_PHY_SELECT",
    ),
    "zigbee_use_release_libraries": (),
}

FALSE_CONDITIONS = {
    "bluetooth_stack",
    "cli",
    "cmsis_rtos2",
    "device_series_3",
    "freertos",
    "native_host",
    "ot_stack",
    "rail_lib_simulation",
    "rail_mux",
    "zigbee_ezsp",
    "zigbee_high_datarate_phy",
    "zigbee_ncp",
    "zigbee_simulation",
    "zigbee_use_ipc",
}

SKIP_SOURCE_PREFIXES = (
    "stack/internal/src/baremetal/",
)

# Omit from both module copy and components.cmake.
SKIP_SOURCES = {
    "app/util/common/app_properties.c",
}

# Sources owned by one component but gated by another Kconfig.
SOURCE_KCONFIG_OVERRIDES = {
    "app/framework/util/print-formatter.c": "SILABS_SISDK_ZIGBEE_DEBUG_PRINT",
}

SKIP_HELPER_COMPONENT_IDS = {
    "zigbee_stack_code_classification",
}

FUNCTION_KEYS = (
    "function_name",
    "handler",
    "service_function",
)


@dataclass
class Component:
    component_id: str
    label: str
    category: str
    scope: str
    slcc_path: Path
    provides: set[str] = field(default_factory=set)
    catalog_values: set[str] = field(default_factory=set)
    requires: list[dict] = field(default_factory=list)
    source: list[dict] = field(default_factory=list)
    include: list[dict] = field(default_factory=list)
    config_files: list[str] = field(default_factory=list)
    template_contributions: list[dict] = field(default_factory=list)
    kconfig_symbol: str = ""
    uses_existing_symbol: bool = False


class ComponentIndex:
    def __init__(self) -> None:
        self.by_id: dict[str, Component] = {}
        self.by_catalog: dict[str, Component] = {}
        self.by_name: dict[str, Component] = {}
        self.providers: dict[str, list[Component]] = {}

    def add(self, component: Component) -> None:
        self.by_id[component.component_id] = component
        for value in component.catalog_values:
            self.by_catalog[value] = component
        for name in component.provides | {component.component_id}:
            self.by_name[name] = component
            self.providers.setdefault(name, []).append(component)

    def resolve(self, name: str, active_ids: set[str] | None = None) -> Component | None:
        """
        Resolve a component id, catalog value, or provides-name.

        When multiple components provide the same capability, prefer one that is
        already active. Otherwise pick a stable default (exact id, then shortest
        component id) so SLCP expansion does not arbitrarily select CSL/sub-GHz
        variants.
        """
        if name in self.by_id:
            return self.by_id[name]

        providers = self.providers.get(name, [])
        if providers:
            if active_ids is not None:
                active_providers = [p for p in providers if p.component_id in active_ids]
                if active_providers:
                    return sorted(active_providers, key=lambda p: p.component_id)[0]
            exact = [p for p in providers if p.component_id == name]
            if exact:
                return exact[0]
            return sorted(providers, key=lambda p: (len(p.component_id), p.component_id))[0]

        return self.by_catalog.get(name) or self.by_name.get(name)


def write_if_changed(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists() and path.read_text() == content:
        return
    path.write_text(content)


def normalize_symbol_suffix(component_id: str) -> str:
    suffix = component_id
    if suffix.startswith("zigbee_"):
        suffix = suffix[len("zigbee_") :]
    return re.sub(r"[^A-Z0-9]+", "_", suffix.upper()).strip("_")


def symbol_for_component(component_id: str) -> tuple[str, bool]:
    if component_id in COMPONENT_SYMBOL_OVERRIDES:
        return COMPONENT_SYMBOL_OVERRIDES[component_id], False
    return f"SILABS_SISDK_ZIGBEE_{normalize_symbol_suffix(component_id)}", False


def parse_active_catalogs(header_path: Path) -> set[str]:
    content = header_path.read_text()
    return set(re.findall(r"SL_CATALOG_([A-Z0-9_]+)_PRESENT", content))


def parse_slcp_component_ids(slcp_path: Path) -> list[str]:
    """Return component ids listed in an .slcp project file."""
    data = YAML(typ="safe").load(slcp_path.read_text())
    selected: list[str] = []
    for entry in data.get("component") or []:
        if not isinstance(entry, dict):
            continue
        component_id = entry.get("id")
        if not component_id:
            continue
        conditions = entry.get("condition") or []
        # Drop entries that are unconditionally false for the Zephyr port.
        if any(token in FALSE_CONDITIONS for token in conditions):
            continue
        selected.append(str(component_id))
    return selected


def load_components(zigbee_root: Path) -> ComponentIndex:
    yaml = YAML(typ="safe")
    index = ComponentIndex()

    for scope, relative_dir in ZIGBEE_COMPONENT_DIRS:
        for slcc_path in sorted((zigbee_root / relative_dir).rglob("*.slcc")):
            data = yaml.load(slcc_path.read_text())
            template_contributions = data.get("template_contribution") or []
            catalog_values = {
                str(entry.get("value"))
                for entry in template_contributions
                if entry.get("name") == "component_catalog" and entry.get("value")
            }
            provides = {
                str(entry.get("name"))
                for entry in (data.get("provides") or [])
                if entry.get("name")
            }
            component = Component(
                component_id=data["id"],
                label=data.get("label", data["id"]),
                category=data.get("category", ""),
                scope=scope,
                slcc_path=slcc_path,
                provides=provides,
                catalog_values=catalog_values,
                requires=list(data.get("requires") or []),
                source=list(data.get("source") or []),
                include=list(data.get("include") or []),
                config_files=[str(entry["path"]) for entry in (data.get("config_file") or []) if entry.get("path")],
                template_contributions=template_contributions,
            )
            component.kconfig_symbol, component.uses_existing_symbol = symbol_for_component(component.component_id)
            index.add(component)

    return index


def condition_is_true(token: str, active_catalogs: set[str], active_component_ids: set[str], index: ComponentIndex) -> bool:
    if token in index.by_id:
        return token in active_component_ids

    providers = index.providers.get(token)
    if providers:
        return any(provider.component_id in active_component_ids for provider in providers)

    if token in FALSE_CONDITIONS:
        return False

    aliases = ACTIVE_CONDITION_ALIASES.get(token)
    if aliases is not None:
        if not aliases:
            return True
        return any(alias in active_catalogs for alias in aliases)

    return token.upper() in active_catalogs


def entry_is_enabled(entry: dict, active_catalogs: set[str], active_component_ids: set[str], index: ComponentIndex) -> bool:
    conditions = entry.get("condition") or []
    unless = entry.get("unless") or []

    if any(not condition_is_true(token, active_catalogs, active_component_ids, index) for token in conditions):
        return False
    if any(condition_is_true(token, active_catalogs, active_component_ids, index) for token in unless):
        return False
    return True


def should_track_requirement(requirement_name: str, index: ComponentIndex) -> bool:
    """Track Zigbee stack/AF deps and util-plugin components (e.g. byte_utilities).

    Do not resolve arbitrary provides (legacy_hal, common_token_manager, ...) to
    host-only providers such as zigbee_stack_unix that happen to be in the index.
    """
    if requirement_name.startswith("zigbee_"):
        return True
    component = index.by_id.get(requirement_name)
    return component is not None and component.scope == "util"

def should_include_helper_component(component: Component) -> bool:
    if component.component_id in SKIP_HELPER_COMPONENT_IDS:
        return False
    if component.component_id.endswith("_library_internal"):
        return False
    return True


def expand_zigbee_requirements(
    index: ComponentIndex,
    active_ids: set[str],
    active_catalogs: set[str],
) -> set[str]:
    """Transitively add in-index Zigbee-package requirements into active_ids."""
    changed = True
    while changed:
        changed = False
        for component_id in set(active_ids):
            component = index.by_id[component_id]
            for requirement in component.requires:
                if not should_track_requirement(requirement["name"], index):
                    continue
                tokens = requirement.get("condition") or []
                if any(
                    not condition_is_true(token, active_catalogs, active_ids, index)
                    for token in tokens
                ):
                    continue
                target = index.resolve(requirement["name"], active_ids)
                if target is None or target.component_id in active_ids:
                    continue
                if not should_include_helper_component(target):
                    continue
                active_ids.add(target.component_id)
                active_catalogs.update(value.upper() for value in target.catalog_values)
                changed = True
    return active_ids


def collect_active_components(index: ComponentIndex, active_catalogs: set[str]) -> list[Component]:
    active_ids = {
        component.component_id
        for catalog, component in index.by_catalog.items()
        if catalog.upper() in active_catalogs
    }
    expand_zigbee_requirements(index, active_ids, active_catalogs)
    return sorted(
        (index.by_id[component_id] for component_id in active_ids),
        key=lambda item: item.component_id,
    )


def collect_active_components_from_slcp(
    index: ComponentIndex, slcp_path: Path
) -> tuple[list[Component], set[str]]:
    """
    Resolve active Zigbee components from an .slcp project file.

    Seeds with Zigbee components listed in the SLCP, then walks .slcc requires.
    Non-Zigbee SLCP ids are kept only as condition tokens in active_catalogs.
    """
    active_ids: set[str] = set()
    active_catalogs: set[str] = set()

    for component_id in parse_slcp_component_ids(slcp_path):
        active_catalogs.add(component_id.upper())
        component = index.resolve(component_id, active_ids)
        if component is None:
            continue
        active_ids.add(component.component_id)
        active_catalogs.update(value.upper() for value in component.catalog_values)

    expand_zigbee_requirements(index, active_ids, active_catalogs)
    components = sorted(
        (index.by_id[component_id] for component_id in active_ids),
        key=lambda item: item.component_id,
    )
    return components, active_catalogs


def component_dependency_ids(
    component: Component,
    active_catalogs: set[str],
    active_component_ids: set[str],
    index: ComponentIndex,
) -> list[str]:
    component_ids: list[str] = []
    for requirement in component.requires:
        if not should_track_requirement(requirement["name"], index):
            continue
        tokens = requirement.get("condition") or []
        if any(
            not condition_is_true(token, active_catalogs, active_component_ids, index)
            for token in tokens
        ):
            continue
        target = index.resolve(requirement["name"], active_component_ids)
        if target is None:
            continue
        if target.component_id not in active_component_ids:
            continue
        if target.component_id != component.component_id and target.component_id not in component_ids:
            component_ids.append(target.component_id)
    return component_ids


def component_dependency_symbols(component: Component, graph: dict[str, list[str]], component_map: dict[str, Component]) -> list[str]:
    return [component_map[dep_id].kconfig_symbol for dep_id in graph.get(component.component_id, [])]


def build_dependency_graph(
    components: list[Component],
    active_catalogs: set[str],
    index: ComponentIndex,
) -> dict[str, list[str]]:
    active_ids = {component.component_id for component in components}
    return {
        component.component_id: component_dependency_ids(component, active_catalogs, active_ids, index)
        for component in components
    }


def strongly_connected_components(graph: dict[str, list[str]]) -> list[list[str]]:
    index_counter = 0
    stack: list[str] = []
    on_stack: set[str] = set()
    indices: dict[str, int] = {}
    lowlinks: dict[str, int] = {}
    sccs: list[list[str]] = []

    def visit(node: str) -> None:
        nonlocal index_counter
        indices[node] = index_counter
        lowlinks[node] = index_counter
        index_counter += 1
        stack.append(node)
        on_stack.add(node)

        for successor in graph.get(node, []):
            if successor not in indices:
                visit(successor)
                lowlinks[node] = min(lowlinks[node], lowlinks[successor])
            elif successor in on_stack:
                lowlinks[node] = min(lowlinks[node], indices[successor])

        if lowlinks[node] == indices[node]:
            scc: list[str] = []
            while True:
                successor = stack.pop()
                on_stack.remove(successor)
                scc.append(successor)
                if successor == node:
                    break
            sccs.append(sorted(scc))

    for node in graph:
        if node not in indices:
            visit(node)

    return sorted(sccs, key=lambda scc: (len(scc) == 1, scc))


def scc_membership(sccs: list[list[str]]) -> dict[str, frozenset[str]]:
    return {
        component_id: frozenset(scc)
        for scc in sccs
        for component_id in scc
    }


def split_dependency_symbols(
    component: Component,
    graph: dict[str, list[str]],
    component_map: dict[str, Component],
    membership: dict[str, frozenset[str]],
    emit_cyclic: bool = True,
) -> tuple[list[str], list[str]]:
    hard: list[str] = []
    soft: list[str] = []
    component_scc = membership[component.component_id]
    for dep_id in graph.get(component.component_id, []):
        dep_symbol = component_map[dep_id].kconfig_symbol
        if membership[dep_id] == component_scc:
            if emit_cyclic and component.kconfig_symbol < dep_symbol and dep_symbol not in soft:
                soft.append(dep_symbol)
        else:
            if dep_symbol not in hard:
                hard.append(dep_symbol)
    return hard, soft


def normalize_relative_dir(path: str) -> str:
    normalized = Path(path).as_posix().rstrip("/")
    if normalized in (".", ""):
        return ""
    return normalized


def normalize_relative_file(path: str) -> str:
    return Path(path).as_posix()


def source_owner_key(component_id: str) -> tuple[int, int, str]:
    return (component_id.endswith("_cli"), len(component_id), component_id)


def collect_component_files(
    components: list[Component],
    active_catalogs: set[str],
    index: ComponentIndex,
) -> tuple[dict[str, list[str]], dict[str, list[str]], set[str], list[dict]]:
    active_ids = {component.component_id for component in components}
    file_manifest: dict[str, list[str]] = {}
    source_manifest: dict[str, list[str]] = {}
    include_dirs: set[str] = {"protocol/zigbee/config"}
    unresolved_conditions: list[dict] = []

    for component in components:
        copied_paths: list[str] = []
        source_paths: list[str] = []

        for entry in component.source:
            entry_path = normalize_relative_file(entry["path"])
            if entry_is_enabled(entry, active_catalogs, active_ids, index):
                if entry_path in SKIP_SOURCES:
                    continue
                copied_paths.append(entry_path)
                if not entry_path.startswith(SKIP_SOURCE_PREFIXES):
                    source_paths.append(entry_path)
            elif entry.get("condition") or entry.get("unless"):
                unresolved_conditions.append(
                    {
                        "component": component.component_id,
                        "kind": "source",
                        "path": entry_path,
                        "condition": entry.get("condition") or [],
                        "unless": entry.get("unless") or [],
                    }
                )

        for entry in component.include:
            include_path = normalize_relative_dir(entry["path"])
            if entry_is_enabled(entry, active_catalogs, active_ids, index):
                include_dirs.add(
                    "protocol/zigbee"
                    if not include_path
                    else f"protocol/zigbee/{include_path}"
                )
                for file_entry in entry.get("file_list") or []:
                    if isinstance(file_entry, str):
                        rel_path = normalize_relative_file(
                            "/".join(filter(None, [include_path, file_entry]))
                        )
                        copied_paths.append(rel_path)
                        continue

                    file_entry_path = normalize_relative_file(file_entry["path"])
                    if entry_is_enabled(file_entry, active_catalogs, active_ids, index):
                        rel_path = normalize_relative_file(
                            "/".join(filter(None, [include_path, file_entry_path]))
                        )
                        copied_paths.append(rel_path)
                    elif file_entry.get("condition") or file_entry.get("unless"):
                        unresolved_conditions.append(
                            {
                                "component": component.component_id,
                                "kind": "include_file",
                                "path": normalize_relative_file(
                                    "/".join(filter(None, [include_path, file_entry_path]))
                                ),
                                "condition": file_entry.get("condition") or [],
                                "unless": file_entry.get("unless") or [],
                            }
                        )
            elif entry.get("condition") or entry.get("unless"):
                unresolved_conditions.append(
                    {
                        "component": component.component_id,
                        "kind": "include",
                        "path": include_path,
                        "condition": entry.get("condition") or [],
                        "unless": entry.get("unless") or [],
                    }
                )

        for config_path in component.config_files:
            config_path = normalize_relative_file(config_path)
            copied_paths.append(config_path)
            include_dirs.add(f"protocol/zigbee/{Path(config_path).parent.as_posix()}")

        file_manifest[component.component_id] = sorted(dict.fromkeys(copied_paths))
        source_manifest[component.component_id] = sorted(dict.fromkeys(source_paths))

    source_owners: dict[str, str] = {}
    for component_id in sorted(source_manifest, key=source_owner_key):
        for rel_path in source_manifest[component_id]:
            source_owners.setdefault(rel_path, component_id)

    for component_id, rel_paths in source_manifest.items():
        source_manifest[component_id] = [
            rel_path for rel_path in rel_paths if source_owners.get(rel_path) == component_id
        ]

    return file_manifest, source_manifest, include_dirs, unresolved_conditions


def copy_component_files(
    zigbee_root: Path,
    module_root: Path,
    file_manifest: dict[str, list[str]],
) -> list[str]:
    copied: set[str] = set()
    destination_root = module_root / "simplicity_sdk/protocol/zigbee"

    for paths in file_manifest.values():
        for rel_path in paths:
            src = zigbee_root / rel_path
            if not src.exists():
                raise FileNotFoundError(f"Missing Zigbee component file: {src}")
            dst = destination_root / rel_path
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, dst)
            copied.add(rel_path)

    return sorted(copied)


def generate_component_kconfig(
    components: list[Component],
    graph: dict[str, list[str]],
    component_map: dict[str, Component],
    membership: dict[str, frozenset[str]],
) -> str:
    lines = [
        "# Copyright (c) 2026 Silicon Laboratories Inc.",
        "# SPDX-License-Identifier: Apache-2.0",
        "",
        "# Generated by scripts/gen_zigbee_components.py",
        "",
        'menu "Zigbee component sources"',
        "\tdepends on SILABS_SISDK_ZIGBEE",
        "",
    ]

    for component in components:
        lines.extend(
            [
                f"config {component.kconfig_symbol}",
                f'\tbool "{component.label}"',
                "\tdepends on SILABS_SISDK_ZIGBEE",
            ]
        )
        for dep in EXTERNAL_COMPONENT_DEPENDENCIES.get(component.component_id, ()):
            lines.append(f"\tdepends on {dep}")
        hard_deps, soft_deps = split_dependency_symbols(component, graph, component_map, membership)
        for dep in hard_deps:
            lines.append(f"\tdepends on {dep}")
        for dep in soft_deps:
            lines.append(f"\timply {dep}")

        help_parts = [
            f"Generated from {component.slcc_path.name}. Category: {component.category or 'uncategorized'}."
        ]
        if hard_deps:
            help_parts.append(f"Acyclic component requirements: {', '.join(hard_deps)}.")
        if soft_deps:
            help_parts.append(
                f"Cyclic component relationships represented as soft implies: {', '.join(soft_deps)}."
            )
        lines.extend(
            [
                "\thelp",
                textwrap.indent(
                    textwrap.fill(
                        " ".join(help_parts),
                        width=70,
                    ),
                    "\t  ",
                ),
                "",
            ]
        )

    lines.extend(
        [
            "endmenu",
            "",
        ]
    )
    return "\n".join(lines)


def generate_component_cmake(
    source_manifest: dict[str, list[str]],
    include_dirs: set[str],
    component_map: dict[str, Component],
    module_variable: str = "${ZEPHYR_HAL_SILABS_EXTRA_MODULE_DIR}",
    generated_config_dir: str = "${CMAKE_CURRENT_LIST_DIR}/../config",
) -> str:
    lines = [
        "# Copyright (c) 2026 Silicon Laboratories Inc.",
        "# SPDX-License-Identifier: Apache-2.0",
        "",
        "# Generated by scripts/gen_zigbee_components.py",
        "",
        "if(CONFIG_SILABS_SISDK_ZIGBEE)",
    ]

    include_dir_lines = [f"  {generated_config_dir}"]
    include_dir_lines.extend(f"  {module_variable}/simplicity_sdk/{path}" for path in sorted(include_dirs))
    if include_dir_lines:
        lines.append("  zephyr_include_directories(")
        lines.extend(include_dir_lines)
        lines.append("  )")
        lines.append("")

    override_sources: dict[str, list[str]] = {}
    for component_id in sorted(source_manifest):
        component = component_map[component_id]
        sources = source_manifest[component_id]
        if not sources:
            continue
        primary_sources: list[str] = []
        for rel_path in sources:
            override_symbol = SOURCE_KCONFIG_OVERRIDES.get(rel_path)
            if override_symbol is not None:
                override_sources.setdefault(override_symbol, []).append(rel_path)
            else:
                primary_sources.append(rel_path)
        if primary_sources:
            lines.append(f"  zephyr_library_sources_ifdef(CONFIG_{component.kconfig_symbol}")
            for rel_path in primary_sources:
                lines.append(
                    f"    {module_variable}/simplicity_sdk/protocol/zigbee/{rel_path}"
                )
            lines.append("  )")
            lines.append("")

    for override_symbol in sorted(override_sources):
        rel_paths = override_sources[override_symbol]
        lines.append(f"  zephyr_library_sources_ifdef(CONFIG_{override_symbol}")
        for rel_path in rel_paths:
            lines.append(f"    {module_variable}/simplicity_sdk/protocol/zigbee/{rel_path}")
        lines.append("  )")
        lines.append("")

    lines.append("endif()")
    lines.append("")
    return "\n".join(lines)


def generate_catalog_translation_headers(components: list[Component]) -> tuple[str, str]:
    translation_lines = [
        "#ifndef SL_CATALOG_KCONFIG_TRANSLATION_H",
        "#define SL_CATALOG_KCONFIG_TRANSLATION_H",
        "",
        "/* Generated by scripts/gen_zigbee_components.py */",
        "",
    ]
    wrapper_lines = [
        "#ifndef SL_COMPONENT_CATALOG_H",
        "#define SL_COMPONENT_CATALOG_H",
        "",
        '#include "sl_catalog_kconfig_translation.h"',
        "",
        "#endif /* SL_COMPONENT_CATALOG_H */",
        "",
    ]

    for component in sorted(components, key=lambda item: item.component_id):
        for catalog_value in sorted(component.catalog_values):
            macro = f"SL_CATALOG_{catalog_value.upper()}_PRESENT"
            translation_lines.extend(
                [
                    f"#if defined(CONFIG_{component.kconfig_symbol}) && CONFIG_{component.kconfig_symbol}",
                    f"#define {macro} 1",
                    "#endif",
                    "",
                ]
            )

    translation_lines.append("#endif /* SL_CATALOG_KCONFIG_TRANSLATION_H */")
    translation_lines.append("")
    return "\n".join(translation_lines), "\n".join(wrapper_lines)


def extract_template_functions(component: Component) -> list[dict]:
    functions: list[dict] = []
    for contribution in component.template_contributions:
        name = contribution.get("name")
        if name == "component_catalog":
            continue
        value = contribution.get("value")
        if isinstance(value, dict):
            matches = {key: value[key] for key in FUNCTION_KEYS if key in value}
            if matches:
                functions.append(
                    {
                        "contribution": name,
                        "details": matches,
                        "condition": contribution.get("condition") or [],
                    }
                )
    return functions


def generate_prj_conf(components: list[Component]) -> str:
    lines = [
        "# Generated by scripts/gen_zigbee_components.py",
        "# Enable active Zigbee component sources for this application profile.",
        "",
    ]
    for component in components:
        lines.append(f"CONFIG_{component.kconfig_symbol}=y")
    lines.append("")
    return "\n".join(lines)


def generate_report(
    components: list[Component],
    graph: dict[str, list[str]],
    component_map: dict[str, Component],
    membership: dict[str, frozenset[str]],
    sccs: list[list[str]],
    source_manifest: dict[str, list[str]],
    copied_files: list[str],
    unresolved_conditions: list[dict],
) -> str:
    lines = [
        "# Z3 Light Zigbee Component Report",
        "",
        "Generated from the selected Zigbee application profile (.slcp or sl_component_catalog.h).",
        "",
        "## Active Zigbee Components",
        "",
        "| Component | Scope | Kconfig | Hard Kconfig deps | Cyclic deps |",
        "| --- | --- | --- | --- | --- |",
    ]

    for component in components:
        hard_deps, _ = split_dependency_symbols(component, graph, component_map, membership)
        _, cyclic_deps = split_dependency_symbols(
            component, graph, component_map, membership, emit_cyclic=False
        )
        hard_text = ", ".join(f"`{dep}`" for dep in hard_deps) if hard_deps else "-"
        soft_text = ", ".join(f"`{dep}`" for dep in cyclic_deps) if cyclic_deps else "-"
        lines.append(
            f"| `{component.component_id}` | `{component.scope}` | `{component.kconfig_symbol}` | {hard_text} | {soft_text} |"
        )

    lines.extend(
        [
            "",
            "## Dependency Cycles",
            "",
        ]
    )

    cycle_groups = [scc for scc in sccs if len(scc) > 1]
    if cycle_groups:
        for idx, scc in enumerate(cycle_groups, start=1):
            lines.append(
                f"{idx}. " + ", ".join(f"`{component_map[component_id].kconfig_symbol}`" for component_id in scc)
            )
    else:
        lines.append("No active component dependency cycles detected.")

    lines.extend(
        [
            "",
            "## Template Contributions With Functions",
            "",
        ]
    )

    any_functions = False
    for component in components:
        function_entries = extract_template_functions(component)
        if not function_entries:
            continue
        any_functions = True
        lines.append(f"### `{component.component_id}`")
        lines.append("")
        for entry in function_entries:
            detail = ", ".join(f"`{key}`=`{value}`" for key, value in entry["details"].items())
            condition = f" (condition: {', '.join(entry['condition'])})" if entry["condition"] else ""
            lines.append(f"- `{entry['contribution']}`: {detail}{condition}")
        lines.append("")

    if not any_functions:
        lines.append("No function-bearing template contributions were found.")
        lines.append("")

    lines.extend(
        [
            "## Copied Zigbee Source Files",
            "",
            f"Total copied files: `{len(copied_files)}`",
            "",
        ]
    )

    for component in components:
        sources = source_manifest[component.component_id]
        if not sources:
            continue
        lines.append(f"### `{component.component_id}`")
        lines.append("")
        for rel_path in sources:
            lines.append(f"- `{rel_path}`")
        lines.append("")

    lines.extend(
        [
            "## Skipped Or Inactive Conditional Entries",
            "",
        ]
    )
    if unresolved_conditions:
        for entry in unresolved_conditions:
            condition = ", ".join(entry["condition"]) if entry["condition"] else "-"
            unless = ", ".join(entry["unless"]) if entry["unless"] else "-"
            lines.append(
                f"- `{entry['component']}` `{entry['kind']}` `{entry['path']}` "
                f"(condition: `{condition}`, unless: `{unless}`)"
            )
    else:
        lines.append("- None")
    lines.append("")
    return "\n".join(lines)


def main() -> None:
    parser = argparse.ArgumentParser(description="Generate Zigbee component glue and manifests")
    parser.add_argument("--zigbee-root", type=Path, required=True)
    parser.add_argument(
        "--slcp",
        type=Path,
        help="Zigbee application .slcp used to select active components and their sources.",
    )
    parser.add_argument(
        "--active-catalog-header",
        type=Path,
        help="Optional Studio-generated sl_component_catalog.h (alternative to --slcp).",
    )
    parser.add_argument(
        "--module-root",
        type=Path,
        help="Module root that receives copied component source files "
        "(e.g. zephyr-hal-silabs-extra).",
    )
    parser.add_argument(
        "--zephyr-root",
        type=Path,
        help="Zephyr repo root that will receive generated zigbee glue under modules/hal_silabs/",
    )
    parser.add_argument(
        "--overlay-root",
        type=Path,
        help="Direct modules/hal_silabs overlay root. Overrides --zephyr-root when provided.",
    )
    parser.add_argument(
        "--report-out",
        type=Path,
        help="Optional explicit report path. Defaults under the generated zephyr overlay tree.",
    )
    parser.add_argument(
        "--no-copy",
        action="store_true",
        help="Only emit generated Kconfig/CMake/catalog glue; do not copy sources into --module-root.",
    )
    parser.add_argument(
        "--copy-only",
        action="store_true",
        help="Only copy active component sources into --module-root; do not emit overlay glue.",
    )
    parser.add_argument(
        "--prj-conf-out",
        type=Path,
        help="Write a Zephyr prj.conf fragment enabling all active component Kconfig symbols.",
    )
    args = parser.parse_args()

    if args.no_copy and args.copy_only:
        parser.error("--no-copy and --copy-only are mutually exclusive")
    if not args.no_copy and args.module_root is None:
        parser.error("--module-root is required unless --no-copy is set")
    if args.copy_only and args.prj_conf_out is not None:
        parser.error("--prj-conf-out cannot be used with --copy-only")
    if args.slcp is None and args.active_catalog_header is None:
        parser.error("one of --slcp or --active-catalog-header is required")
    if args.slcp is not None and args.active_catalog_header is not None:
        parser.error("--slcp and --active-catalog-header are mutually exclusive")

    zigbee_root = args.zigbee_root.resolve(strict=True)
    module_root = args.module_root.expanduser().resolve() if args.module_root is not None else None
    overlay_root: Path | None = None
    if not args.copy_only:
        if args.overlay_root is not None:
            overlay_root = args.overlay_root.resolve(strict=True)
        elif args.zephyr_root is not None:
            overlay_root = (args.zephyr_root.resolve(strict=True) / "modules/hal_silabs").resolve()
        else:
            parser.error("one of --zephyr-root or --overlay-root is required unless --copy-only is set")

    index = load_components(zigbee_root)
    if args.slcp is not None:
        components, active_catalogs = collect_active_components_from_slcp(
            index, args.slcp.resolve(strict=True)
        )
    else:
        active_catalogs = parse_active_catalogs(args.active_catalog_header.resolve(strict=True))
        components = collect_active_components(index, active_catalogs)
    component_map = {component.component_id: component for component in components}
    dependency_graph = build_dependency_graph(components, active_catalogs, index)
    sccs = strongly_connected_components(dependency_graph)
    membership = scc_membership(sccs)

    file_manifest, source_manifest, include_dirs, unresolved_conditions = collect_component_files(
        components,
        active_catalogs,
        index,
    )
    if args.no_copy:
        copied_files = sorted(
            {rel_path for paths in file_manifest.values() for rel_path in paths}
        )
    else:
        module_root.mkdir(parents=True, exist_ok=True)
        copied_files = copy_component_files(zigbee_root, module_root, file_manifest)

    if args.copy_only:
        print(
            f"Copied {len(copied_files)} files for {len(components)} active components "
            f"into {module_root / 'simplicity_sdk/protocol/zigbee'}"
        )
        return

    translation_header, wrapper_header = generate_catalog_translation_headers(components)
    kconfig = generate_component_kconfig(components, dependency_graph, component_map, membership)
    cmake = generate_component_cmake(
        source_manifest,
        include_dirs,
        component_map,
        generated_config_dir="${CMAKE_CURRENT_LIST_DIR}/../config",
    )
    report = generate_report(
        components,
        dependency_graph,
        component_map,
        membership,
        sccs,
        source_manifest,
        copied_files,
        unresolved_conditions,
    )

    zigbee_overlay_root = overlay_root / "simplicity_sdk/zigbee"
    generated_root = zigbee_overlay_root / "generated"
    config_root = zigbee_overlay_root / "config"
    report_out = (
        args.report_out.resolve()
        if args.report_out is not None
        else generated_root / "Z3_LIGHT_COMPONENTS.md"
    )

    write_if_changed(generated_root / "Kconfig.components", kconfig)
    write_if_changed(generated_root / "components.cmake", cmake)
    write_if_changed(config_root / "sl_catalog_kconfig_translation.h", translation_header)
    write_if_changed(config_root / "sl_component_catalog.h", wrapper_header)
    write_if_changed(report_out, report)
    write_if_changed(
        generated_root / "z3_light_component_manifest.json",
        json.dumps(
            {
                "components": [
                    {
                        "id": component.component_id,
                        "label": component.label,
                        "category": component.category,
                        "scope": component.scope,
                        "kconfig": component.kconfig_symbol,
                        "hard_kconfig_deps": split_dependency_symbols(
                            component, dependency_graph, component_map, membership
                        )[0],
                        "cyclic_kconfig_deps": split_dependency_symbols(
                            component, dependency_graph, component_map, membership, emit_cyclic=False
                        )[1],
                        "catalog_values": sorted(component.catalog_values),
                        "source_files": source_manifest[component.component_id],
                        "copied_files": file_manifest[component.component_id],
                        "template_functions": extract_template_functions(component),
                    }
                    for component in components
                ],
                "copied_files": copied_files,
                "include_dirs": sorted(include_dirs),
                "dependency_cycles": sccs,
                "unresolved_conditions": unresolved_conditions,
            },
            indent=2,
            sort_keys=True,
        )
        + "\n",
    )

    if args.prj_conf_out is not None:
        write_if_changed(args.prj_conf_out.resolve(), generate_prj_conf(components))


if __name__ == "__main__":
    main()
