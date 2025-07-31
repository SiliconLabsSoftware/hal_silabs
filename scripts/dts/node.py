# Copyright (c) 2025 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0

import textwrap
from pathlib import Path

from .prop import *


class Node:
    def __init__(
        self,
        name=None,
        labels=None,
        compatible=None,
        reg=None,
        peripheral_name=None,
        is_ref=False,
        reg_is_hex=True,
        status=None,
    ):
        self.name = name
        self.peripheral_name = peripheral_name
        self.address = None
        self.props = []
        self.nodes = []
        self.labels = labels if labels is not None else []
        self.parent = None
        self.indent = 1
        self.includes = {
            "local": [],
            "system": [],
        }
        self.is_ref = is_ref or self.name is None
        self.root = False

        if compatible:
            if not isinstance(compatible, list):
                compatible = [compatible]
            self.add_prop(StringArrayProperty("compatible", compatible))

        if reg:
            if isinstance(reg, dict):
                regs = []
                names = []
                for name, r in reg.items():
                    names.append(name)
                    regs.append(r)
                if reg_is_hex:
                    self.add_prop(HexArrayProperty("reg", regs))
                else:
                    self.add_prop(ArrayProperty("reg", regs))
                self.add_prop(StringArrayProperty("reg-names", names))
            else:
                if reg_is_hex:
                    self.add_prop(HexArrayProperty("reg", reg))
                else:
                    self.add_prop(ArrayProperty("reg", reg))

        if status is not None:
            self.status(status)

    def __str__(self):
        self.sort_props()
        self.sort_nodes()

        c = ""
        suffix = ""

        if self.root:
            c += "/dts-v1/;\n"

        if self.includes["system"]:
            for inc in sorted(self.includes["system"]):
                c += f"#include <{inc[1]}>\n"
        if self.includes["local"]:
            if self.includes["system"]:
                c += "\n"
            for inc in sorted(self.includes["local"]):
                c += f'#include "{inc[1]}"\n'

        if not self.labels and not self.props and not self.nodes and not self.parent:
            # Empty root node, emit nothing except any registered includes
            return c

        if self.includes["local"] or self.includes["system"]:
            c += "\n"

        if self.is_ref:
            if len(self.labels) > 1:
                for l in sorted(self.labels[1:]):
                    suffix += f"\n{l}: &{self.labels[0]} {{}};\n"
            c += f"&{self.labels[0]} {{\n"
        else:
            for l in self.labels:
                c += f"{l}: "
            a = f"@{self.address:x}" if self.address is not None else ""
            c += f"{self.name}{a} {{\n"

        s = ""
        for p in self.props:
            if sp := str(p):
                s += f"{sp}\n"
        for n in self.nodes:
            if s:
                s += "\n"
            s += str(n)
        c += textwrap.indent(str(s), "\t")
        c += "};\n"

        return c + suffix

    def sort_props(self):
        # https://docs.kernel.org/devicetree/bindings/dts-coding-style.html#order-of-properties-in-device-node
        def prop_sort_key(p):
            if p.name == "compatible":
                category = 1
            elif p.name == "reg":
                category = 2
            elif p.name in ["ranges", "pins", "pinmux"]:
                category = 3
            elif "," in p.name:
                category = 5
            elif p.name == "status":
                category = 6
            else:
                category = 4
            return (category, p.name)

        self.props.sort(key=prop_sort_key)

    def sort_nodes(self):
        # https://docs.kernel.org/devicetree/bindings/dts-coding-style.html#order-of-nodes
        self.nodes.sort(key=lambda n: (n.address or 0, n.name))

    def add_node(self, node):
        node.parent = self
        node.indent = self.indent + 1
        self.nodes.append(node)

    def add_nodes(self, nodes):
        for node in nodes:
            node.parent = self
            node.indent = self.indent + 1
        self.nodes += nodes

    def add_prop(self, prop):
        if prop.name == "reg":
            self.address = prop.value[0]
        if isinstance(self.address, list):
            self.address = self.address[0]
        prop.node = self
        self.props.append(prop)
        return prop

    def add_props(self, props):
        for prop in props:
            self.add_prop(prop)

    def add_bool(self, *args, **kwargs):
        return self.add_prop(BoolProperty(*args, **kwargs))

    def add_int(self, *args, **kwargs):
        return self.add_prop(IntProperty(*args, **kwargs))

    def add_array(self, *args, **kwargs):
        return self.add_prop(ArrayProperty(*args, **kwargs))

    def add_hex_array(self, *args, **kwargs):
        return self.add_prop(HexArrayProperty(*args, **kwargs))

    def add_uint8_array(self, *args, **kwargs):
        return self.add_prop(Uint8ArrayProperty(*args, **kwargs))

    def add_string(self, *args, **kwargs):
        return self.add_prop(StringProperty(*args, **kwargs))

    def add_string_array(self, *args, **kwargs):
        return self.add_prop(StringArrayProperty(*args, **kwargs))

    def add_phandle(self, *args, **kwargs):
        return self.add_prop(PhandleProperty(*args, **kwargs))

    def add_phandles(self, *args, **kwargs):
        return self.add_prop(PhandlesProperty(*args, **kwargs))

    def add_phandle_array(self, *args, **kwargs):
        return self.add_prop(PhandleArrayProperty(*args, **kwargs))

    def add_include(self, include, local=False, priority=0):
        include_type = "local" if local else "system"
        inc = (priority, Path(include))
        if inc not in self.includes[include_type]:
            self.includes[include_type].append(inc)

    def update_includes(self, other):
        for t in ["local", "system"]:
            for inc in other.includes[t]:
                self.add_include(inc[1], local=(t == "local"), priority=inc[0])

    def remove_includes(self):
        for t in ["local", "system"]:
            self.includes[t] = []

    def get_root(self):
        node = self
        while node.parent:
            node = node.parent
        return node

    def find(self, name, address=True):
        if self.name == name:
            return self

        name = name.lstrip("/")
        if "/" in name:
            name, query = name.split("/", 1)
        else:
            query = None

        for n in self.nodes:
            if address:
                a = f"@{n.address:x}" if n.address is not None else ""
                node_name = f"{n.name}{a}"
            else:
                node_name = n.name

            if node_name == name:
                if query:
                    return n.find(query, address)
                else:
                    return n

    def prop(self, name):
        for p in self.props:
            if p.name == name:
                return p
        return None

    def status(self, value):
        status = self.prop("status")
        if not status:
            status = self.add_string("status", value)
        status.value = value

    def resolve_deferred_values(self, config):
        if isinstance(self.address, DeferredValue):
            self.address = config.get(self.address.value, self.peripheral_name)

        for prop in self.props:
            if isinstance(prop.value, DeferredValue):
                prop.value = config.get(prop.value.value, self.peripheral_name)

        for node in self.nodes:
            node.resolve_deferred_values(config)


class DeleteNode(Node):
    def __init__(self, name=None, label=None, reg=None):
        if label is not None:
            label = [label]
        super().__init__(name, label, reg=reg)

    def __str__(self):
        if self.labels:
            return f"/delete-node/ &{self.labels[0]};\n"
        else:
            return f"/delete-node/ {self.name};\n"


class ClockNode(Node):
    def __init__(self, name, parent, labels=None):
        aliases = {"sysrtc0clk": "sysrtcclk"}
        name = aliases.get(name, name)

        super().__init__(name, labels)
        self.labels.append(name)

        self.add_prop(StringProperty("compatible", "fixed-factor-clock"))
        self.add_prop(IntProperty("#clock-cells", "0"))
        self.add_prop(PhandleProperty("clocks", parent))


class ChosenNode(Node):
    def __init__(self, name):
        super().__init__(name, None)

    def select(self, key, node):
        self.add_prop(PathProperty(key, node.labels[0]))


class PinctrlGroup(Node):
    def __init__(self, name, pins, *props, abus=None):
        super().__init__(name, None)

        if pins is not None:
            self.add_prop(ArrayProperty("pins", [[s] for s in pins]))
        if abus is not None:
            self.add_prop(ArrayProperty("silabs,analog-bus", [[b] for b in abus]))
        for prop in props:
            if prop is not None:
                self.add_prop(BoolProperty(prop, True))
