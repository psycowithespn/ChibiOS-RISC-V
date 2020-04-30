/*
    ChibiOS - Copyright (C) 2020 Patrick Seidel

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    fe310_pcri.h
 * @brief   FE310 PCRI units common header.
 *
 * @addtogroup FE310_PCRI
 * @{
 */

#ifndef FE310_PCRI_H
#define FE310_PCRI_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    PCRI definitions
 * @{
 */
#define PCRI                           ((fe310_pcri_t *)0x10008000)
/** @} */

/**
 * @name    HFROSCCFG register definitions
 * @{
 */
#define PCRI_HFR_DIV_SHIFT              0
#define PCRI_HFR_DIV_MASK               0x3F
#define PCRI_HFR_DIV(n)                 (((n) & PCRI_HFR_DIV_MASK) << PCRI_HFR_DIV_SHIFT)

#define PCRI_HFR_TRIM_SHIFT             16
#define PCRI_HFR_TRIM_MASK              0x3F
#define PCRI_HFR_TRIM(n)                (((n) & PCRI_HFR_TRIM_MASK) << PCRI_HFR_TRIM_SHIFT)

#define PCRI_HFR_EN                     (1 << 30)

#define PCRI_HFR_RDY                    (1 << 31)
/** @} */

/**
 * @name    HFXOSCCFG register definitions
 * @{
 */
#define PCRI_HFX_EN                     (1 << 30)

#define PCRI_HFX_RDY                    (1 << 31)
/** @} */

/**
 * @name    PLLCFG register definitions
 * @{
 */
#define PCRI_PLL_R_SHIFT                0
#define PCRI_PLL_R_MASK                 0x7
#define PCRI_PLL_R(n)                   (((n) & PCRI_PLL_R_MASK) << PCRI_PLL_R_SHIFT)

#define PCRI_PLL_F_SHIFT                4
#define PCRI_PLL_F_MASK                 0x3F
#define PCRI_PLL_F(n)                   (((n) & PCRI_PLL_F_MASK) << PCRI_PLL_F_SHIFT)

#define PCRI_PLL_Q_SHIFT                10
#define PCRI_PLL_Q_MASK                 0x3
#define PCRI_PLL_Q(n)                   (((n) & PCRI_PLL_Q_MASK) << PCRI_PLL_Q_SHIFT)

#define PCRI_PLL_SEL_PLL                (1 << 16)
#define PCRI_PLL_REFSEL_HFX             (1 << 17)
#define PCRI_PLL_BYPASS                 (1 << 18)

#define PCRI_PLL_LOCK                   (1 << 31)
/** @} */

/**
 * @name    PLL Divider register definitions
 * @{
 */
#define PCRI_PLLDIV_SHIFT                0
#define PCRI_PLLDIV_MASK                 0x3F
#define PCRI_PLLDIV(n)                   (((n) & PCRI_PLLDIV_MASK) << PCRI_PLLDIV_SHIFT)

#define PCRI_PLLDIV_BY1_SHIFT            8
#define PCRI_PLLDIV_BY1_MASK             0x3F
#define PCRI_PLLDIV_BY1(n)               (((n) & PCRI_PLLDIV_BY1_MASK) << PCRI_PLLDIV_BY1_SHIFT)
/** @} */

/**
 * @name    LFR register definitions
 * @{
 */
#define PCRI_LFR_DIV_SHIFT               0
#define PCRI_LFR_DIV_MASK                0x3F
#define PCRI_LFR_DIV(n)                  (((n) & PCRI_LFR_DIV_MASK) << PCRI_LFR_DIV_SHIFT)

#define PCRI_LFR_TRIM_SHIFT              16
#define PCRI_LFR_TRIM_MASK               0x1F
#define PCRI_LFR_BY1(n)                  (((n) & PCRI_LFR_TRIM_MASK) << PCRI_LFR_TRIM_SHIFT)

#define PCRI_LFR_EN                      (1 << 30)
#define PCRI_LFR_RDY                     (1 << 31)
/** @} */

/**
 * @name    LFX register definitions
 * @{
 */
#define PCRI_LFX_SEL_LFX                 (1 << 0)

#define PCRI_LFX_MUX_STATUS              (1 << 31)
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   FE310 PCRI registers block.
 */
typedef struct {

  volatile uint32_t   HFROSCCFG;
  volatile uint32_t   HFXOSCCFG;
  volatile uint32_t   PLLCFG;
  volatile uint32_t   PLLOUTDIV;
  volatile uint32_t   PADDING0[24];
  volatile uint32_t   LFROSCCFG;
  volatile uint32_t   PADDING1[2];
  volatile uint32_t   LFXOSCCFG;
  volatile uint32_t   PADDING2[28];
  volatile uint32_t   PROCMONCFG;
} fe310_pcri_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* FE310_PCRI_H */

/** @} */
