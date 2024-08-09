//-----------------------------------------------------------------------------
// Copyright 2012 (c) Silicon Laboratories Inc.
//
// SPDX-License-Identifier: Zlib
//
// This siHAL software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//-----------------------------------------------------------------------------
/// @file SI32_LDO_A_Type.h
//
// This file applies to the SIM3L1XX_LDO_A module
//
// Script: 0.62
// HAL Source: 0.3
// Version: 1

#ifndef __SI32_LDO_A_TYPE_H__
#define __SI32_LDO_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SIM3L1XX_LDO_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_LDO_A_write_control(SI32_LDO_A_Type* basePointer,
///      uint32_t control)
///
/// @brief
/// Write to CONTROL register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///
void
_SI32_LDO_A_write_control(SI32_LDO_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_LDO_A_write_control(basePointer, control)
#define SI32_LDO_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_LDO_A_read_control(SI32_LDO_A_Type* basePointer)
///
/// @brief
/// Reads CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_LDO_A_read_control(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_read_control(basePointer)
#define SI32_LDO_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_LDO_A_select_digital_source_vbat_pin(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_digital_source_vbat_pin(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_digital_source_vbat_pin(basePointer)
#define SI32_LDO_A_select_digital_source_vbat_pin(basePointer) \
   (basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_DLDOSSEL_MASK)


/// @fn _SI32_LDO_A_select_digital_source_dcdc_output(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_digital_source_dcdc_output(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_digital_source_dcdc_output(basePointer)
#define SI32_LDO_A_select_digital_source_dcdc_output(basePointer) \
   (basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_DLDOSSEL_DCDC_U32)


/// @fn _SI32_LDO_A_select_digital_bias_high(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_digital_bias_high(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_digital_bias_high(basePointer)
#define SI32_LDO_A_select_digital_bias_high(basePointer) \
   (basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_DLDOBSEL_HIGH_U32)


/// @fn _SI32_LDO_A_select_digital_bias_low(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_digital_bias_low(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_digital_bias_low(basePointer)
#define SI32_LDO_A_select_digital_bias_low(basePointer) \
   (basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_DLDOBSEL_MASK)


/// @fn _SI32_LDO_A_set_digital_output_value(SI32_LDO_A_Type* basePointer,
///      uint32_t value)
///
/// @brief
/// Sets the output voltage of the digital LDO between 0.8 and 1.9 V in 50
/// mV steps.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  value
///  Valid range is 5 bits.
///
void
_SI32_LDO_A_set_digital_output_value(SI32_LDO_A_Type* /*basePointer*/,
   uint32_t /*value*/);
///
/// @def SI32_LDO_A_set_digital_output_value(basePointer, value)
#define SI32_LDO_A_set_digital_output_value(basePointer, value) \
   (basePointer->CONTROL.DLDOOVAL = value)


/// @fn _SI32_LDO_A_get_digital_output_value(SI32_LDO_A_Type* basePointer)
///
/// @brief
/// Gets the output voltage setting of the digital LDO.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_LDO_A_get_digital_output_value(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_get_digital_output_value(basePointer)
#define SI32_LDO_A_get_digital_output_value(basePointer) \
(basePointer->CONTROL.DLDOOVAL)


/// @fn _SI32_LDO_A_select_memory_source_vbat_pin(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_memory_source_vbat_pin(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_memory_source_vbat_pin(basePointer)
#define SI32_LDO_A_select_memory_source_vbat_pin(basePointer) \
   (basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_MLDOSSEL_MASK)


/// @fn _SI32_LDO_A_select_memory_source_dcdc_output(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_memory_source_dcdc_output(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_memory_source_dcdc_output(basePointer)
#define SI32_LDO_A_select_memory_source_dcdc_output(basePointer) \
   (basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_MLDOSSEL_DCDC_U32)


/// @fn _SI32_LDO_A_select_memory_bias_high(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_memory_bias_high(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_memory_bias_high(basePointer)
#define SI32_LDO_A_select_memory_bias_high(basePointer) \
   (basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_MLDOBSEL_HIGH_U32)


/// @fn _SI32_LDO_A_select_memory_bias_low(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_memory_bias_low(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_memory_bias_low(basePointer)
#define SI32_LDO_A_select_memory_bias_low(basePointer) \
   (basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_MLDOBSEL_MASK)


/// @fn _SI32_LDO_A_set_memory_output_value(SI32_LDO_A_Type* basePointer,
///      uint32_t value)
///
/// @brief
/// Sets the output voltage of the memory LDO between 0.8 and 1.9 V in 50
/// mV steps.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  value
///  Valid range is 5 bits.
///
void
_SI32_LDO_A_set_memory_output_value(SI32_LDO_A_Type* /*basePointer*/,
   uint32_t /*value*/);
///
/// @def SI32_LDO_A_set_memory_output_value(basePointer, value)
#define SI32_LDO_A_set_memory_output_value(basePointer, value) \
   (basePointer->CONTROL.MLDOOVAL = value)


/// @fn _SI32_LDO_A_get_memory_output_value(SI32_LDO_A_Type* basePointer)
///
/// @brief
/// Gets the output voltage setting of the memory LDO.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_LDO_A_get_memory_output_value(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_get_memory_output_value(basePointer)
#define SI32_LDO_A_get_memory_output_value(basePointer) \
(basePointer->CONTROL.MLDOOVAL)


/// @fn _SI32_LDO_A_select_analog_source_vbat_pin(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_analog_source_vbat_pin(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_analog_source_vbat_pin(basePointer)
#define SI32_LDO_A_select_analog_source_vbat_pin(basePointer) \
   (basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_ALDOSSEL_MASK)


/// @fn _SI32_LDO_A_select_analog_source_dcdc_output(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_analog_source_dcdc_output(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_analog_source_dcdc_output(basePointer)
#define SI32_LDO_A_select_analog_source_dcdc_output(basePointer) \
   (basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_ALDOSSEL_DCDC_U32)


/// @fn _SI32_LDO_A_select_analog_bias_high(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_analog_bias_high(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_analog_bias_high(basePointer)
#define SI32_LDO_A_select_analog_bias_high(basePointer) \
   (basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_ALDOBSEL_HIGH_U32)


/// @fn _SI32_LDO_A_select_analog_bias_low(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_analog_bias_low(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_analog_bias_low(basePointer)
#define SI32_LDO_A_select_analog_bias_low(basePointer) \
   (basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_ALDOBSEL_MASK)


/// @fn _SI32_LDO_A_set_analog_output_value(SI32_LDO_A_Type* basePointer,
///      uint32_t value)
///
/// @brief
/// Sets the output voltage of the analog LDO between 0.8 and 1.9 V in 50
/// mV steps.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  value
///  Valid range is 5 bits.
///
void
_SI32_LDO_A_set_analog_output_value(SI32_LDO_A_Type* /*basePointer*/,
   uint32_t /*value*/);
///
/// @def SI32_LDO_A_set_analog_output_value(basePointer, value)
#define SI32_LDO_A_set_analog_output_value(basePointer, value) \
   (basePointer->CONTROL.ALDOOVAL = value)


/// @fn _SI32_LDO_A_get_analog_output_value(SI32_LDO_A_Type* basePointer)
///
/// @brief
/// Gets the output voltage setting of the analog LDO.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_LDO_A_get_analog_output_value(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_get_analog_output_value(basePointer)
#define SI32_LDO_A_get_analog_output_value(basePointer) \
(basePointer->CONTROL.ALDOOVAL)



#ifdef __cplusplus
}
#endif

#endif // __SI32_LDO_A_TYPE_H__

//-eof--------------------------------------------------------------------------