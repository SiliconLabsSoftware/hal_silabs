# Copyright (c) 2025 Silicon Laboratories Inc.
# SPDX-License-Identifier: Apache-2.0


class PropertyType:
    PATH = "path"
    PHANDLE = "phandle"
    PHANDLES = "phandles"
    PHANDLE_ARRAY = "phandle-array"
    ARRAY = "array"
    STRING = "string"
    STRING_ARRAY = "string-array"
    INTEGER = "integer"
    UINT8_ARRAY = "uint8-array"
    BOOLEAN = "boolean"


class Property:
    def __init__(self, name, value, comment=None):
        self.name = name
        self.value = value
        self.labels = []
        self.node = None
        self.comment = comment
        self.fmt_one_element_per_line = False

    def _str_format_comment(self):
        import textwrap

        if not self.comment:
            return ""

        comment = "/*"
        max_width = 100 - 8 * self.node.indent - 6
        if len(self.comment) > max_width:
            comment += (
                "\n"
                + "\n".join(
                    textwrap.wrap(
                        self.comment,
                        width=max_width + 3,
                        initial_indent=" * ",
                        subsequent_indent=" * ",
                    )
                )
                + "\n"
            )
        else:
            comment += " " + self.comment

        comment += " */\n"

        return comment

    def _str_format_list(self, values):
        values_str = self._str_format_comment()

        if self.node:
            indent = self.node.indent
        else:
            indent = 0

        name_len = len(self.name) + 2
        max_width = 100 - 8 * indent - name_len - 1
        indent = "\t" * (name_len // 8) + " " * (name_len % 8)
        width = 0
        for v in values:
            if self.fmt_one_element_per_line and width != 0:
                values_str += "\n" + indent
            width += len(v) + 2
            if not self.fmt_one_element_per_line and width > max_width:
                values_str += "\n" + indent
                width = len(v) + 2
            values_str += f" {v},"

        return f"{self.name} ={values_str.rstrip(',')};"


class DeleteProperty(Property):
    def __init__(self, name, comment=None):
        super().__init__(name, None, comment)

    def __str__(self):
        c = self._str_format_comment()
        return f"{c}/delete-property/ {self.name};"


class PathProperty(Property):
    def __init__(self, name, value, comment=None):
        super().__init__(name, value, comment)
        self.type = PropertyType.PATH

    def __str__(self):
        c = self._str_format_comment()
        return f"{c}{self.name} = &{self.value};"


class PhandleProperty(Property):
    def __init__(self, name, value, comment=None):
        super().__init__(name, value, comment)
        self.type = PropertyType.PHANDLE

    def __str__(self):
        c = self._str_format_comment()
        return f"{c}{self.name} = <&{self.value}>;"


class PhandlesProperty(Property):
    def __init__(self, name, value, comment=None):
        super().__init__(name, value, comment)
        self.type = PropertyType.PHANDLES

    def __str__(self):
        c = self._str_format_comment()
        return f"{c}{self.name} = <{' '.join(f'&{v}' for v in self.value)}>;"


class PhandleArrayProperty(Property):
    def __init__(self, name, values, comment=None):
        super().__init__(name, values, comment)
        self.type = PropertyType.PHANDLE_ARRAY

    def __str__(self):
        if not isinstance(self.value[0], list):
            self.value = [self.value]

        values = [f"<&{' '.join(map(str, v))}>" for v in self.value]
        return self._str_format_list(values)


class ArrayProperty(Property):
    def __init__(self, name, values, comment=None):
        super().__init__(name, values, comment)
        self.type = PropertyType.ARRAY
        self.fmt = ["{}", "{}", "{}", "{}", "{}"]

    def __str__(self):
        if not isinstance(self.value[0], list):
            self.value = [self.value]

        values = [
            f"<{' '.join(self.fmt[((e.bit_length() - 1) // 8) if e.bit_length() else -1].format(e) if isinstance(e, int) else e for e in v)}>"
            for v in self.value
        ]
        return self._str_format_list(values)


class HexArrayProperty(ArrayProperty):
    def __init__(self, name, values, comment=None):
        super().__init__(name, values, comment)
        self.fmt = ["0x{:02x}", "0x{:04x}", "0x{:08x}", "0x{:08x}", "0x{:x}"]


class Uint8ArrayProperty(Property):
    def __init__(self, name, values, comment=None):
        super().__init__(name, values, comment)
        self.type = PropertyType.UINT8_ARRAY

    def __str__(self):
        c = self._str_format_comment()
        values_str = f"[{' '.join(f'{v:02x}' for v in self.value)}]"
        return f"{c}{self.name} = {values_str};"


class StringProperty(Property):
    def __init__(self, name, value, comment=None):
        super().__init__(name, value, comment)
        self.type = PropertyType.STRING

    def __str__(self):
        c = self._str_format_comment()
        return f'{c}{self.name} = "{self.value}";'


class StringArrayProperty(Property):
    def __init__(self, name, value, comment=None):
        super().__init__(name, value, comment)
        self.type = PropertyType.STRING_ARRAY

    def __str__(self):
        return self._str_format_list(f'"{v}"' for v in self.value)


class IntProperty(Property):
    def __init__(self, name, value, comment=None):
        super().__init__(name, value, comment)
        self.type = PropertyType.INTEGER

    def __str__(self):
        c = self._str_format_comment()
        return f"{c}{self.name} = <{self.value}>;"


class BoolProperty(Property):
    def __init__(self, name, value, comment=None):
        super().__init__(name, value, comment)
        self.type = PropertyType.BOOLEAN

    def __str__(self):
        c = self._str_format_comment()
        return f"{c}{self.name};" if self.value else ""


class DeferredValue:
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return f"<deferred>{self.value}</deferred>"


def property_from_string(spec_type, prop, val):
    if spec_type == "boolean":
        return BoolProperty(prop, val)
    elif spec_type == "int":
        return IntProperty(prop, val)
    elif spec_type == "array":
        return ArrayProperty(prop, val)
    elif spec_type == "uint8-array":
        return Uint8ArrayProperty(prop, val)
    elif spec_type == "string":
        return StringProperty(prop, val)
    elif spec_type == "string-array":
        return StringArrayProperty(prop, val)
    elif spec_type == "phandle":
        return PhandleProperty(prop, val)
    elif spec_type == "phandles":
        return PhandlesProperty(prop, val)
    elif spec_type == "phandle-array":
        return PhandleArrayProperty(prop, val)
    else:
        raise ValueError(f"Unsupported property type {spec_type} for {prop}")
