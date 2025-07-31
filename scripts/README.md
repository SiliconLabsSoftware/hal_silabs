# Utility Scripts for HAL Import

The Python scripts in this directory are used to generate content for use in the Zephyr main tree
from Silicon Labs HAL content, as well as to import the HAL itself.

## HAL Import

These script are usually required when:

* a new version of Simplicity SDK or WiSeConnect is available
* a new feature in the Zephyr main tree requires not yet imported files

### Simplicity SDK

Simplicity SDK is imported using the `import_simplicity_sdk.py` script. It is wrapped by the
`update_simplicity_sdk.py` script, which takes care of applying patches to the imported content.

### WiSeConnect SDK

WiSeConnect SDK is imported using the `import_wiseconnect.py` script.

## Devicetree Binding Headers

These scripts are only required to implement support for a new part in Zephyr.

Devicetree binding headers for Series 2 are generated using the following scripts:

* Comparator bindings: `gen_acmp.py`
* ADC bindings: `gen_adc.py`
* Clock Control bindings: `gen_clock_control.py`
* Pin Control bindings: `gen_pinctrl.py`
* DAC bindings: `gen_vdac.py`

## Devicetree Files

### SoC Devicetree

SoC devicetree for Series 2 is generated using the `gen_dts_soc_series2.py` script.
The script takes the following inputs:

* `sdk` -- Path to Simplicity SDK or device package to extract data from.
* `family` -- The family to generate .dtsi files for.
* `soc-yml` -- The soc.yml to use for filtering.
* `out` -- The output path.

Example usage:

```sh
./scripts/gen_dts_soc_series2.py \
    -f xg24 \
    -s ~/sisdk-release/ \
    -o $ZEPHYR_BASE/dts/arm/silabs/ \
    -y $ZEPHYR_BASE/soc/silabs/soc.yml
```

### Board Devicetree

Board devicetree is generated using the `gen_dts_board.py` script.
The script takes the following inputs:

* `sdk` -- Path to Simplicity SDK or boards package to extract data from.
* `board` -- The board to generate .dts files for.
* `out` -- The output path.

Example usage:

```sh
./scripts/gen_dts_board.py \
    -b xg24_dk2601b \
    -s ~/sisdk-release/ \
    -o $ZEPHYR_BASE/boards/silabs/dev_kits/xg24_dk2601b/ 
```
