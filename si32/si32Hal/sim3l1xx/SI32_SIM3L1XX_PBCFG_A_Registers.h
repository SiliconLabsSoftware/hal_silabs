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
//
// This file applies to the SIM3L1XX_PBCFG_A module
//
// Script: 0.61
// Version: 1

#ifndef __SI32_PBCFG_A_REGISTERS_H__
#define __SI32_PBCFG_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_PBCFG_A_CONTROL0_Struct
{
   union
   {
      struct
      {
         // External Interrupt 0 Pin Selection
         volatile uint32_t INT0SEL: 4;
         // External Interrupt 0 Polarity
         volatile uint32_t INT0POL: 1;
         // External Interrupt 0 Mode
         volatile uint32_t INT0MD: 2;
         // External Interrupt 0 Enable
         volatile uint32_t INT0EN: 1;
         // External Interrupt 1 Pin Selection
         volatile uint32_t INT1SEL: 4;
         // External Interrupt 1 Polarity
         volatile uint32_t INT1POL: 1;
         // External Interrupt 1 Mode
         volatile uint32_t INT1MD: 2;
         // External Interrupt 1 Enable
         volatile uint32_t INT1EN: 1;
                  uint32_t reserved0: 8;
         // Pulse Generator Timer
         volatile uint32_t PGTIMER: 5;
                  uint32_t reserved1: 2;
         // Pulse Generator Timer Done Flag
         volatile uint32_t PGDONEF: 1;
      };
      volatile uint32_t U32;
   };
};

#define SI32_PBCFG_A_CONTROL0_INT0SEL_MASK  0x0000000F
#define SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT  0
// Select INT0.0
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_0_VALUE  0
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_0_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_0_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.1
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_1_VALUE  1
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_1_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_1_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.2
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_2_VALUE  2
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_2_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_2_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.3
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_3_VALUE  3
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_3_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_3_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.4
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_4_VALUE  4
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_4_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_4_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.5
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_5_VALUE  5
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_5_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_5_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.6
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_6_VALUE  6
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_6_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_6_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.7
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_7_VALUE  7
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_7_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_7_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.8
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_8_VALUE  8
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_8_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_8_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.9
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_9_VALUE  9
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_9_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_9_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.10
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_10_VALUE  10
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_10_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_10_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.11
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_11_VALUE  11
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_11_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_11_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.12
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_12_VALUE  12
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_12_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_12_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.13
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_13_VALUE  13
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_13_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_13_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.14
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_14_VALUE  14
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_14_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_14_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)
// Select INT0.15
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_15_VALUE  15
#define SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_15_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0SEL_INT0_15_VALUE << SI32_PBCFG_A_CONTROL0_INT0SEL_SHIFT)

#define SI32_PBCFG_A_CONTROL0_INT0POL_MASK  0x00000010
#define SI32_PBCFG_A_CONTROL0_INT0POL_SHIFT  4
// A low value or falling edge on the selected pin will cause interrupt.
#define SI32_PBCFG_A_CONTROL0_INT0POL_LOW_VALUE  0
#define SI32_PBCFG_A_CONTROL0_INT0POL_LOW_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0POL_LOW_VALUE << SI32_PBCFG_A_CONTROL0_INT0POL_SHIFT)
// A high value or rising edge on the selected pin will cause interrupt.
#define SI32_PBCFG_A_CONTROL0_INT0POL_HIGH_VALUE  1
#define SI32_PBCFG_A_CONTROL0_INT0POL_HIGH_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0POL_HIGH_VALUE << SI32_PBCFG_A_CONTROL0_INT0POL_SHIFT)

#define SI32_PBCFG_A_CONTROL0_INT0MD_MASK  0x00000060
#define SI32_PBCFG_A_CONTROL0_INT0MD_SHIFT  5
// Interrupt on logic level at pin, as selected by the INT0POL field.
#define SI32_PBCFG_A_CONTROL0_INT0MD_LEVEL_VALUE  0
#define SI32_PBCFG_A_CONTROL0_INT0MD_LEVEL_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0MD_LEVEL_VALUE << SI32_PBCFG_A_CONTROL0_INT0MD_SHIFT)
// Interrupt on either rising or falling edge, as selected by the INT0POL field.
#define SI32_PBCFG_A_CONTROL0_INT0MD_EDGE_VALUE  1
#define SI32_PBCFG_A_CONTROL0_INT0MD_EDGE_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0MD_EDGE_VALUE << SI32_PBCFG_A_CONTROL0_INT0MD_SHIFT)
// Interrupt on both rising and falling edges (ignores INT0POL).
#define SI32_PBCFG_A_CONTROL0_INT0MD_DUAL_EDGE_VALUE  2
#define SI32_PBCFG_A_CONTROL0_INT0MD_DUAL_EDGE_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0MD_DUAL_EDGE_VALUE << SI32_PBCFG_A_CONTROL0_INT0MD_SHIFT)

#define SI32_PBCFG_A_CONTROL0_INT0EN_MASK  0x00000080
#define SI32_PBCFG_A_CONTROL0_INT0EN_SHIFT  7
// Disable external interrupt 0.
#define SI32_PBCFG_A_CONTROL0_INT0EN_DISABLED_VALUE  0
#define SI32_PBCFG_A_CONTROL0_INT0EN_DISABLED_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0EN_DISABLED_VALUE << SI32_PBCFG_A_CONTROL0_INT0EN_SHIFT)
// Enable external interrupt 0.
#define SI32_PBCFG_A_CONTROL0_INT0EN_ENABLED_VALUE  1
#define SI32_PBCFG_A_CONTROL0_INT0EN_ENABLED_U32 \
   (SI32_PBCFG_A_CONTROL0_INT0EN_ENABLED_VALUE << SI32_PBCFG_A_CONTROL0_INT0EN_SHIFT)

#define SI32_PBCFG_A_CONTROL0_INT1SEL_MASK  0x00000F00
#define SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT  8
// Select INT1.0
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_0_VALUE  0
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_0_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_0_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.1
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_1_VALUE  1
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_1_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_1_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.2
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_2_VALUE  2
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_2_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_2_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.3
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_3_VALUE  3
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_3_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_3_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.4
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_4_VALUE  4
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_4_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_4_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.5
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_5_VALUE  5
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_5_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_5_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.6
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_6_VALUE  6
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_6_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_6_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.7
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_7_VALUE  7
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_7_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_7_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.8
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_8_VALUE  8
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_8_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_8_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.9
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_9_VALUE  9
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_9_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_9_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.10
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_10_VALUE  10
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_10_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_10_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.11
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_11_VALUE  11
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_11_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_11_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.12
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_12_VALUE  12
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_12_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_12_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.13
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_13_VALUE  13
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_13_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_13_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.14
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_14_VALUE  14
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_14_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_14_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)
// Select INT1.15
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_15_VALUE  15
#define SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_15_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1SEL_INT1_15_VALUE << SI32_PBCFG_A_CONTROL0_INT1SEL_SHIFT)

#define SI32_PBCFG_A_CONTROL0_INT1POL_MASK  0x00001000
#define SI32_PBCFG_A_CONTROL0_INT1POL_SHIFT  12
// A low value or falling edge on the selected pin will cause interrupt.
#define SI32_PBCFG_A_CONTROL0_INT1POL_LOW_VALUE  0
#define SI32_PBCFG_A_CONTROL0_INT1POL_LOW_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1POL_LOW_VALUE << SI32_PBCFG_A_CONTROL0_INT1POL_SHIFT)
// A high value or rising edge on the selected pin will cause interrupt.
#define SI32_PBCFG_A_CONTROL0_INT1POL_HIGH_VALUE  1
#define SI32_PBCFG_A_CONTROL0_INT1POL_HIGH_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1POL_HIGH_VALUE << SI32_PBCFG_A_CONTROL0_INT1POL_SHIFT)

#define SI32_PBCFG_A_CONTROL0_INT1MD_MASK  0x00006000
#define SI32_PBCFG_A_CONTROL0_INT1MD_SHIFT  13
// Interrupt on logic level at pin, as selected by the INT1POL field.
#define SI32_PBCFG_A_CONTROL0_INT1MD_LEVEL_VALUE  0
#define SI32_PBCFG_A_CONTROL0_INT1MD_LEVEL_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1MD_LEVEL_VALUE << SI32_PBCFG_A_CONTROL0_INT1MD_SHIFT)
// Interrupt on either rising or falling edge, as selected by the INT1POL field.
#define SI32_PBCFG_A_CONTROL0_INT1MD_EDGE_VALUE  1
#define SI32_PBCFG_A_CONTROL0_INT1MD_EDGE_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1MD_EDGE_VALUE << SI32_PBCFG_A_CONTROL0_INT1MD_SHIFT)
// Interrupt on both rising and falling edges (ignores INT1POL).
#define SI32_PBCFG_A_CONTROL0_INT1MD_DUAL_EDGE_VALUE  2
#define SI32_PBCFG_A_CONTROL0_INT1MD_DUAL_EDGE_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1MD_DUAL_EDGE_VALUE << SI32_PBCFG_A_CONTROL0_INT1MD_SHIFT)

#define SI32_PBCFG_A_CONTROL0_INT1EN_MASK  0x00008000
#define SI32_PBCFG_A_CONTROL0_INT1EN_SHIFT  15
// Disable external interrupt 1.
#define SI32_PBCFG_A_CONTROL0_INT1EN_DISABLED_VALUE  0
#define SI32_PBCFG_A_CONTROL0_INT1EN_DISABLED_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1EN_DISABLED_VALUE << SI32_PBCFG_A_CONTROL0_INT1EN_SHIFT)
// Enable external interrupt 1.
#define SI32_PBCFG_A_CONTROL0_INT1EN_ENABLED_VALUE  1
#define SI32_PBCFG_A_CONTROL0_INT1EN_ENABLED_U32 \
   (SI32_PBCFG_A_CONTROL0_INT1EN_ENABLED_VALUE << SI32_PBCFG_A_CONTROL0_INT1EN_SHIFT)

#define SI32_PBCFG_A_CONTROL0_PGTIMER_MASK  0x1F000000
#define SI32_PBCFG_A_CONTROL0_PGTIMER_SHIFT  24

#define SI32_PBCFG_A_CONTROL0_PGDONEF_MASK  0x80000000
#define SI32_PBCFG_A_CONTROL0_PGDONEF_SHIFT  31
// Firmware has written to the PBPGPHASE register, but the Pulse Generator timer
// has not expired.
#define SI32_PBCFG_A_CONTROL0_PGDONEF_NOT_SET_VALUE  0U
#define SI32_PBCFG_A_CONTROL0_PGDONEF_NOT_SET_U32 \
   (SI32_PBCFG_A_CONTROL0_PGDONEF_NOT_SET_VALUE << SI32_PBCFG_A_CONTROL0_PGDONEF_SHIFT)
// The Pulse Generator cycle finished since the last time PBPGPHASE was written.
#define SI32_PBCFG_A_CONTROL0_PGDONEF_SET_VALUE  1U
#define SI32_PBCFG_A_CONTROL0_PGDONEF_SET_U32 \
   (SI32_PBCFG_A_CONTROL0_PGDONEF_SET_VALUE << SI32_PBCFG_A_CONTROL0_PGDONEF_SHIFT)



struct SI32_PBCFG_A_CONTROL1_Struct
{
   union
   {
      struct
      {
         // JTAG Enable
         volatile uint32_t JTAGEN: 1;
         // ETM Enable
         volatile uint32_t ETMEN: 1;
         // SWV Enable
         volatile uint32_t SWVEN: 1;
                  uint32_t reserved0: 5;
         // SPI1 Fixed Port Selection
         volatile uint32_t SPI1SEL: 1;
         // Port Match Interrupt Enable
         volatile uint32_t PMATCHEN: 1;
                  uint32_t reserved1: 2;
         // Low Power Timer Output Pin Select
         volatile uint32_t LPTOSEL: 1;
                  uint32_t reserved2: 18;
         // Port Bank Configuration Lock
         volatile uint32_t LOCK: 1;
      };
      volatile uint32_t U32;
   };
};

#define SI32_PBCFG_A_CONTROL1_JTAGEN_MASK  0x00000001
#define SI32_PBCFG_A_CONTROL1_JTAGEN_SHIFT  0
// JTAG functionality is not pinned out.
#define SI32_PBCFG_A_CONTROL1_JTAGEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_CONTROL1_JTAGEN_DISABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_JTAGEN_DISABLED_VALUE << SI32_PBCFG_A_CONTROL1_JTAGEN_SHIFT)
// JTAG functionality is pinned out.
#define SI32_PBCFG_A_CONTROL1_JTAGEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_CONTROL1_JTAGEN_ENABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_JTAGEN_ENABLED_VALUE << SI32_PBCFG_A_CONTROL1_JTAGEN_SHIFT)

#define SI32_PBCFG_A_CONTROL1_ETMEN_MASK  0x00000002
#define SI32_PBCFG_A_CONTROL1_ETMEN_SHIFT  1
// ETM not pinned out.
#define SI32_PBCFG_A_CONTROL1_ETMEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_CONTROL1_ETMEN_DISABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_ETMEN_DISABLED_VALUE << SI32_PBCFG_A_CONTROL1_ETMEN_SHIFT)
// ETM is enabled and pinned out.
#define SI32_PBCFG_A_CONTROL1_ETMEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_CONTROL1_ETMEN_ENABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_ETMEN_ENABLED_VALUE << SI32_PBCFG_A_CONTROL1_ETMEN_SHIFT)

#define SI32_PBCFG_A_CONTROL1_SWVEN_MASK  0x00000004
#define SI32_PBCFG_A_CONTROL1_SWVEN_SHIFT  2
// SWV is not pinned out.
#define SI32_PBCFG_A_CONTROL1_SWVEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_CONTROL1_SWVEN_DISABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_SWVEN_DISABLED_VALUE << SI32_PBCFG_A_CONTROL1_SWVEN_SHIFT)
// SWV is enabled and pinned out.
#define SI32_PBCFG_A_CONTROL1_SWVEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_CONTROL1_SWVEN_ENABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_SWVEN_ENABLED_VALUE << SI32_PBCFG_A_CONTROL1_SWVEN_SHIFT)

#define SI32_PBCFG_A_CONTROL1_SPI1SEL_MASK  0x00000100
#define SI32_PBCFG_A_CONTROL1_SPI1SEL_SHIFT  8
// Disconnect SPI1 from the dedicated pins.
#define SI32_PBCFG_A_CONTROL1_SPI1SEL_DISABLED_VALUE  0
#define SI32_PBCFG_A_CONTROL1_SPI1SEL_DISABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_SPI1SEL_DISABLED_VALUE << SI32_PBCFG_A_CONTROL1_SPI1SEL_SHIFT)
// Connect SPI1 to the dedicated pins.
#define SI32_PBCFG_A_CONTROL1_SPI1SEL_ENABLED_VALUE  1
#define SI32_PBCFG_A_CONTROL1_SPI1SEL_ENABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_SPI1SEL_ENABLED_VALUE << SI32_PBCFG_A_CONTROL1_SPI1SEL_SHIFT)

#define SI32_PBCFG_A_CONTROL1_PMATCHEN_MASK  0x00000200
#define SI32_PBCFG_A_CONTROL1_PMATCHEN_SHIFT  9
// Disable the port match logic. The PBnMAT registers are not read/write accessible
// on the APB bus.
#define SI32_PBCFG_A_CONTROL1_PMATCHEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_CONTROL1_PMATCHEN_DISABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_PMATCHEN_DISABLED_VALUE << SI32_PBCFG_A_CONTROL1_PMATCHEN_SHIFT)
// Enable the port match logic to generate a port match interrupt. The PBnMAT
// registers are read/write accessible on the APB bus.
#define SI32_PBCFG_A_CONTROL1_PMATCHEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_CONTROL1_PMATCHEN_ENABLED_U32 \
   (SI32_PBCFG_A_CONTROL1_PMATCHEN_ENABLED_VALUE << SI32_PBCFG_A_CONTROL1_PMATCHEN_SHIFT)

#define SI32_PBCFG_A_CONTROL1_LPTOSEL_MASK  0x00001000
#define SI32_PBCFG_A_CONTROL1_LPTOSEL_SHIFT  12
// Route the Low Power Timer output to LPT0OUT0.
#define SI32_PBCFG_A_CONTROL1_LPTOSEL_LPT0OUT0_VALUE  0
#define SI32_PBCFG_A_CONTROL1_LPTOSEL_LPT0OUT0_U32 \
   (SI32_PBCFG_A_CONTROL1_LPTOSEL_LPT0OUT0_VALUE << SI32_PBCFG_A_CONTROL1_LPTOSEL_SHIFT)
// Route the Low Power Timer output to LPT0OUT1.
#define SI32_PBCFG_A_CONTROL1_LPTOSEL_LPT0OUT1_VALUE  1
#define SI32_PBCFG_A_CONTROL1_LPTOSEL_LPT0OUT1_U32 \
   (SI32_PBCFG_A_CONTROL1_LPTOSEL_LPT0OUT1_VALUE << SI32_PBCFG_A_CONTROL1_LPTOSEL_SHIFT)

#define SI32_PBCFG_A_CONTROL1_LOCK_MASK  0x80000000
#define SI32_PBCFG_A_CONTROL1_LOCK_SHIFT  31
// Port Bank Configuration and Control registers are unlocked.
#define SI32_PBCFG_A_CONTROL1_LOCK_UNLOCKED_VALUE  0U
#define SI32_PBCFG_A_CONTROL1_LOCK_UNLOCKED_U32 \
   (SI32_PBCFG_A_CONTROL1_LOCK_UNLOCKED_VALUE << SI32_PBCFG_A_CONTROL1_LOCK_SHIFT)
// The following registers are locked from write access: CONTROL1, XBAR0, and all
// PBSKIP registers.
#define SI32_PBCFG_A_CONTROL1_LOCK_LOCKED_VALUE  1U
#define SI32_PBCFG_A_CONTROL1_LOCK_LOCKED_U32 \
   (SI32_PBCFG_A_CONTROL1_LOCK_LOCKED_VALUE << SI32_PBCFG_A_CONTROL1_LOCK_SHIFT)



struct SI32_PBCFG_A_XBAR0_Struct
{
   union
   {
      struct
      {
         // USART0 Enable
         volatile uint32_t USART0EN: 1;
         // USART0 Flow Control Enable
         volatile uint32_t USART0FCEN: 1;
         // USART0 Clock Signal Enable
         volatile uint32_t USART0CEN: 1;
         // DMA Trigger 0 Enable
         volatile uint32_t DMA0T0EN: 1;
         // DMA Trigger 1 Enabled
         volatile uint32_t DMA0T1EN: 1;
         // IDAC0 Trigger Enable
         volatile uint32_t IDAC0TEN: 1;
         // SPI0 Enable
         volatile uint32_t SPI0EN: 1;
         // SPI0 NSS Pin Enable
         volatile uint32_t SPI0NSSEN: 1;
         // EPCA0 Channel Enable
         volatile uint32_t EPCA0EN: 3;
         // EPCA0 ECI Enable
         volatile uint32_t EECI0EN: 1;
         // I2C0 Enable
         volatile uint32_t I2C0EN: 1;
         // Comparator 0 Synchronous Output (CMP0S) Enable
         volatile uint32_t CMP0SEN: 1;
         // Comparator 0 Asynchronous Output (CMP0A) Enable
         volatile uint32_t CMP0AEN: 1;
         // Comparator 1 Synchronous Output (CMP1S) Enable
         volatile uint32_t CMP1SEN: 1;
         // Comparator 1 Asynchronous Output (CMP1A) Enable
         volatile uint32_t CMP1AEN: 1;
         // TIMER0 T0CT Enable
         volatile uint32_t TMR0CTEN: 1;
         // TIMER0 T0EX Enable
         volatile uint32_t TMR0EXEN: 1;
         // TIMER1 T1CT Enable
         volatile uint32_t TMR1CTEN: 1;
         // TIMER1 T1EX Enable
         volatile uint32_t TMR1EXEN: 1;
         // SARADC0 Trigger Enable
         volatile uint32_t SARADC0TEN: 1;
         // AHB Clock Output Enable
         volatile uint32_t AHBEN: 1;
                  uint32_t reserved0: 8;
         // Crossbar 0 Enable
         volatile uint32_t XBAR0EN: 1;
      };
      volatile uint32_t U32;
   };
};

#define SI32_PBCFG_A_XBAR0_USART0EN_MASK  0x00000001
#define SI32_PBCFG_A_XBAR0_USART0EN_SHIFT  0
// Disable USART0 RX and TX on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_USART0EN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_USART0EN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_USART0EN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_USART0EN_SHIFT)
// Enable USART0 RX and TX on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_USART0EN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_USART0EN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_USART0EN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_USART0EN_SHIFT)

#define SI32_PBCFG_A_XBAR0_USART0FCEN_MASK  0x00000002
#define SI32_PBCFG_A_XBAR0_USART0FCEN_SHIFT  1
// Disable USART0 flow control on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_USART0FCEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_USART0FCEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_USART0FCEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_USART0FCEN_SHIFT)
// Enable USART0 flow control on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_USART0FCEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_USART0FCEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_USART0FCEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_USART0FCEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_USART0CEN_MASK  0x00000004
#define SI32_PBCFG_A_XBAR0_USART0CEN_SHIFT  2
// Disable USART0 clock on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_USART0CEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_USART0CEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_USART0CEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_USART0CEN_SHIFT)
// Enable USART0 clock on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_USART0CEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_USART0CEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_USART0CEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_USART0CEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_DMA0T0EN_MASK  0x00000008
#define SI32_PBCFG_A_XBAR0_DMA0T0EN_SHIFT  3
// Disable the DMA trigger 0 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_DMA0T0EN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_DMA0T0EN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_DMA0T0EN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_DMA0T0EN_SHIFT)
// Enable the DMA trigger 0 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_DMA0T0EN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_DMA0T0EN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_DMA0T0EN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_DMA0T0EN_SHIFT)

#define SI32_PBCFG_A_XBAR0_DMA0T1EN_MASK  0x00000010
#define SI32_PBCFG_A_XBAR0_DMA0T1EN_SHIFT  4
// Disable the DMA trigger 1 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_DMA0T1EN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_DMA0T1EN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_DMA0T1EN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_DMA0T1EN_SHIFT)
// Enable the DMA trigger 1 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_DMA0T1EN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_DMA0T1EN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_DMA0T1EN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_DMA0T1EN_SHIFT)

#define SI32_PBCFG_A_XBAR0_IDAC0TEN_MASK  0x00000020
#define SI32_PBCFG_A_XBAR0_IDAC0TEN_SHIFT  5
// Disable the IDAC0 trigger on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_IDAC0TEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_IDAC0TEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_IDAC0TEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_IDAC0TEN_SHIFT)
// Enable the IDAC0 trigger on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_IDAC0TEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_IDAC0TEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_IDAC0TEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_IDAC0TEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_SPI0EN_MASK  0x00000040
#define SI32_PBCFG_A_XBAR0_SPI0EN_SHIFT  6
// Disable SPI0 SCK, MISO, and MOSI on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_SPI0EN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_SPI0EN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_SPI0EN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_SPI0EN_SHIFT)
// Enable SPI0 SCK, MISO, and MOSI on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_SPI0EN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_SPI0EN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_SPI0EN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_SPI0EN_SHIFT)

#define SI32_PBCFG_A_XBAR0_SPI0NSSEN_MASK  0x00000080
#define SI32_PBCFG_A_XBAR0_SPI0NSSEN_SHIFT  7
// Disable SPI0 NSS on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_SPI0NSSEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_SPI0NSSEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_SPI0NSSEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_SPI0NSSEN_SHIFT)
// Enable SPI0 NSS on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_SPI0NSSEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_SPI0NSSEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_SPI0NSSEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_SPI0NSSEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_EPCA0EN_MASK  0x00000700
#define SI32_PBCFG_A_XBAR0_EPCA0EN_SHIFT  8
// Disable all EPCA0 channels on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EPCA0EN_NONE_VALUE  0
#define SI32_PBCFG_A_XBAR0_EPCA0EN_NONE_U32 \
   (SI32_PBCFG_A_XBAR0_EPCA0EN_NONE_VALUE << SI32_PBCFG_A_XBAR0_EPCA0EN_SHIFT)
// Enable EPCA0 CEX0 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_0_VALUE  1
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_0_U32 \
   (SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_0_VALUE << SI32_PBCFG_A_XBAR0_EPCA0EN_SHIFT)
// Enable EPCA0 CEX0 and CEX1 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_1_VALUE  2
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_1_U32 \
   (SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_1_VALUE << SI32_PBCFG_A_XBAR0_EPCA0EN_SHIFT)
// Enable EPCA0 CEX0, CEX1, and CEX2 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_2_VALUE  3
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_2_U32 \
   (SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_2_VALUE << SI32_PBCFG_A_XBAR0_EPCA0EN_SHIFT)
// Enable EPCA0 CEX0, CEX1, CEX2, and CEX3 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_3_VALUE  4
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_3_U32 \
   (SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_3_VALUE << SI32_PBCFG_A_XBAR0_EPCA0EN_SHIFT)
// Enable EPCA0 CEX0, CEX1, CEX2, CEX3, and CEX4 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_4_VALUE  5
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_4_U32 \
   (SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_4_VALUE << SI32_PBCFG_A_XBAR0_EPCA0EN_SHIFT)
// Enable EPCA0 CEX0, CEX1, CEX2, CEX3, CEX4, and CEX5 on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_5_VALUE  6
#define SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_5_U32 \
   (SI32_PBCFG_A_XBAR0_EPCA0EN_CEX0_5_VALUE << SI32_PBCFG_A_XBAR0_EPCA0EN_SHIFT)

#define SI32_PBCFG_A_XBAR0_EECI0EN_MASK  0x00000800
#define SI32_PBCFG_A_XBAR0_EECI0EN_SHIFT  11
// Disable EPCA0 ECI on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EECI0EN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_EECI0EN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_EECI0EN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_EECI0EN_SHIFT)
// Enable EPCA0 ECI on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_EECI0EN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_EECI0EN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_EECI0EN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_EECI0EN_SHIFT)

#define SI32_PBCFG_A_XBAR0_I2C0EN_MASK  0x00001000
#define SI32_PBCFG_A_XBAR0_I2C0EN_SHIFT  12
// Disable I2C0 SDA and SCL on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_I2C0EN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_I2C0EN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_I2C0EN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_I2C0EN_SHIFT)
// Enable I2C0 SDA and SCL on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_I2C0EN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_I2C0EN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_I2C0EN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_I2C0EN_SHIFT)

#define SI32_PBCFG_A_XBAR0_CMP0SEN_MASK  0x00002000
#define SI32_PBCFG_A_XBAR0_CMP0SEN_SHIFT  13
// Disable Comparator 0 Synchronous Output (CMP0S) on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_CMP0SEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_CMP0SEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_CMP0SEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_CMP0SEN_SHIFT)
// Enable Comparator 0 Synchronous Output (CMP0S) on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_CMP0SEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_CMP0SEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_CMP0SEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_CMP0SEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_CMP0AEN_MASK  0x00004000
#define SI32_PBCFG_A_XBAR0_CMP0AEN_SHIFT  14
// Disable Comparator 0 Asynchronous Output (CMP0A) on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_CMP0AEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_CMP0AEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_CMP0AEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_CMP0AEN_SHIFT)
// Enable Comparator 0 Asynchronous Output (CMP0A) on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_CMP0AEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_CMP0AEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_CMP0AEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_CMP0AEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_CMP1SEN_MASK  0x00008000
#define SI32_PBCFG_A_XBAR0_CMP1SEN_SHIFT  15
// Disable Comparator 1 Synchronous Output (CMP1S) on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_CMP1SEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_CMP1SEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_CMP1SEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_CMP1SEN_SHIFT)
// Enable Comparator 1 Synchronous Output (CMP1S) on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_CMP1SEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_CMP1SEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_CMP1SEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_CMP1SEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_CMP1AEN_MASK  0x00010000
#define SI32_PBCFG_A_XBAR0_CMP1AEN_SHIFT  16
// Disable Comparator 1 Asynchronous Output (CMP1A) on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_CMP1AEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_CMP1AEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_CMP1AEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_CMP1AEN_SHIFT)
// Enable Comparator 1 Asynchronous Output (CMP1A) on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_CMP1AEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_CMP1AEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_CMP1AEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_CMP1AEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_TMR0CTEN_MASK  0x00020000
#define SI32_PBCFG_A_XBAR0_TMR0CTEN_SHIFT  17
// Disable TIMER0 CT on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_TMR0CTEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_TMR0CTEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_TMR0CTEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_TMR0CTEN_SHIFT)
// Enable TIMER0 CT on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_TMR0CTEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_TMR0CTEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_TMR0CTEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_TMR0CTEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_TMR0EXEN_MASK  0x00040000
#define SI32_PBCFG_A_XBAR0_TMR0EXEN_SHIFT  18
// Disable TIMER0 EX on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_TMR0EXEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_TMR0EXEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_TMR0EXEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_TMR0EXEN_SHIFT)
// Enable TIMER0 EX on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_TMR0EXEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_TMR0EXEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_TMR0EXEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_TMR0EXEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_TMR1CTEN_MASK  0x00080000
#define SI32_PBCFG_A_XBAR0_TMR1CTEN_SHIFT  19
// Disable TIMER1 CT on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_TMR1CTEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_TMR1CTEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_TMR1CTEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_TMR1CTEN_SHIFT)
// Enable TIMER1 CT on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_TMR1CTEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_TMR1CTEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_TMR1CTEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_TMR1CTEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_TMR1EXEN_MASK  0x00100000
#define SI32_PBCFG_A_XBAR0_TMR1EXEN_SHIFT  20
// Disable TIMER1 EX on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_TMR1EXEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_TMR1EXEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_TMR1EXEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_TMR1EXEN_SHIFT)
// Enable TIMER1 EX on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_TMR1EXEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_TMR1EXEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_TMR1EXEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_TMR1EXEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_SARADC0TEN_MASK  0x00200000
#define SI32_PBCFG_A_XBAR0_SARADC0TEN_SHIFT  21
// Disable SARADC0 conversion start trigger on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_SARADC0TEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_SARADC0TEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_SARADC0TEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_SARADC0TEN_SHIFT)
// Enable SARADC0 conversion start trigger on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_SARADC0TEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_SARADC0TEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_SARADC0TEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_SARADC0TEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_AHBEN_MASK  0x00400000
#define SI32_PBCFG_A_XBAR0_AHBEN_SHIFT  22
// Disable the AHB Clock / 16 output on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_AHBEN_DISABLED_VALUE  0
#define SI32_PBCFG_A_XBAR0_AHBEN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_AHBEN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_AHBEN_SHIFT)
// Enable the AHB Clock / 16 output on Crossbar 0.
#define SI32_PBCFG_A_XBAR0_AHBEN_ENABLED_VALUE  1
#define SI32_PBCFG_A_XBAR0_AHBEN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_AHBEN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_AHBEN_SHIFT)

#define SI32_PBCFG_A_XBAR0_XBAR0EN_MASK  0x80000000
#define SI32_PBCFG_A_XBAR0_XBAR0EN_SHIFT  31
// Disable Crossbar 0.
#define SI32_PBCFG_A_XBAR0_XBAR0EN_DISABLED_VALUE  0U
#define SI32_PBCFG_A_XBAR0_XBAR0EN_DISABLED_U32 \
   (SI32_PBCFG_A_XBAR0_XBAR0EN_DISABLED_VALUE << SI32_PBCFG_A_XBAR0_XBAR0EN_SHIFT)
// Enable Crossbar 0.
#define SI32_PBCFG_A_XBAR0_XBAR0EN_ENABLED_VALUE  1U
#define SI32_PBCFG_A_XBAR0_XBAR0EN_ENABLED_U32 \
   (SI32_PBCFG_A_XBAR0_XBAR0EN_ENABLED_VALUE << SI32_PBCFG_A_XBAR0_XBAR0EN_SHIFT)



struct SI32_PBCFG_A_PBKEY_Struct
{
   union
   {
      struct
      {
         // Port Bank Key
         volatile uint8_t KEY;
                  uint32_t reserved0: 24;
      };
      volatile uint32_t U32;
   };
};

#define SI32_PBCFG_A_PBKEY_KEY_MASK  0x000000FF
#define SI32_PBCFG_A_PBKEY_KEY_SHIFT  0
// Port Bank registers are locked and no valid values have been written to PBKEY.
#define SI32_PBCFG_A_PBKEY_KEY_LOCKED_VALUE  0
#define SI32_PBCFG_A_PBKEY_KEY_LOCKED_U32 \
   (SI32_PBCFG_A_PBKEY_KEY_LOCKED_VALUE << SI32_PBCFG_A_PBKEY_KEY_SHIFT)
// Port Bank registers are locked and the first valid value (0xA5) has been written
// to PBKEY.
#define SI32_PBCFG_A_PBKEY_KEY_INTERMEDIATE_VALUE  1
#define SI32_PBCFG_A_PBKEY_KEY_INTERMEDIATE_U32 \
   (SI32_PBCFG_A_PBKEY_KEY_INTERMEDIATE_VALUE << SI32_PBCFG_A_PBKEY_KEY_SHIFT)
// Port Bank registers are unlocked. Any subsequent writes to the Port Bank
// registers or PBKEY will lock the interface.
#define SI32_PBCFG_A_PBKEY_KEY_UNLOCKED_VALUE  2
#define SI32_PBCFG_A_PBKEY_KEY_UNLOCKED_U32 \
   (SI32_PBCFG_A_PBKEY_KEY_UNLOCKED_VALUE << SI32_PBCFG_A_PBKEY_KEY_SHIFT)



typedef struct SI32_PBCFG_A_Struct
{
   struct SI32_PBCFG_A_CONTROL0_Struct             CONTROL0       ; // Base Address + 0x0
   volatile uint32_t                               CONTROL0_SET;
   volatile uint32_t                               CONTROL0_CLR;
   uint32_t                                        reserved0;
   struct SI32_PBCFG_A_CONTROL1_Struct             CONTROL1       ; // Base Address + 0x10
   volatile uint32_t                               CONTROL1_SET;
   volatile uint32_t                               CONTROL1_CLR;
   uint32_t                                        reserved1;
   struct SI32_PBCFG_A_XBAR0_Struct                XBAR0          ; // Base Address + 0x20
   volatile uint32_t                               XBAR0_SET;
   volatile uint32_t                               XBAR0_CLR;
   uint32_t                                        reserved2;
   struct SI32_PBCFG_A_PBKEY_Struct                PBKEY          ; // Base Address + 0x30
   uint32_t                                        reserved3;
   uint32_t                                        reserved4;
   uint32_t                                        reserved5;
} SI32_PBCFG_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_PBCFG_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------
