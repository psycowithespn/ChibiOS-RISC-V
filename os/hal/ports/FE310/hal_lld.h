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
 * @file    FE310/hal_lld.h
 * @brief   FE310 HAL subsystem low level driver header.
 *          .
 *          One of the following macros must also be defined:
 *          - FE310_G002
 *
 * @addtogroup HAL
 * @{
 */

#ifndef HAL_LLD_H
#define HAL_LLD_H

#include "fe310_prci.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Platform identification macros
 * @{
 */
#if defined(FE310_G002) || defined(__DOXYGEN__)
#define PLATFORM_NAME           "FE310-G002"

#else
#error "FE310 device unsupported or not specified"
#endif
/** @} */

/**
 * @name    Absolute Maximum Ratings
 * @{
 */
/**
 * @brief   Maximum system clock frequency.
 */
#define FE310_CORECLK_MAX        320000000

/**
 * @brief   Maximum HFX clock frequency.
 */
#define FE310_HFXCLK_MAX        20000000

/**
 * @brief   Minimum HFX clock frequency.
 */
#define FE310_HFXCLK_MIN        10000000

/**
 * @brief   Maximum LFALT clock frequency.
 */
#define FE310_LFXCLK_MAX        500000

/**
 * @brief   Minimum LFALT clock frequency.
 */
#define FE310_LFXCLK_MIN        1

/**
 * @brief   Maximum PLL input clock frequency.
 */
#define FE310_PLLIN_MAX         48000000

/**
 * @brief   Minimum PLL input clock frequency.
 */
#define FE310_PLLIN_MIN         6000000

/**
 * @brief   Maximum PLL VCO clock frequency.
 */
#define FE310_PLLVCO_MAX        768000000

/**
 * @brief   Minimum PLL VCO clock frequency.
 */
#define FE310_PLLVCO_MIN        384000000

/**
 * @brief   Maximum PLL output clock frequency.
 */
#define FE310_PLLOUT_MAX        384000000

/**
 * @brief   Minimum PLL output clock frequency.
 */
#define FE310_PLLOUT_MIN        48000000

/** @} */

/**
 * @name    Internal clock sources
 * @{
 */
#define FE310_HFRCLK            72000000     /**< High speed internal clock. */
#define FE310_LFRCLK            40000       /**< Low speed internal clock.  */
/** @} */

#define FE310_CORECLK_HFR       0    /**< CORECLK source is HFR. */
#define FE310_CORECLK_HFX       1    /**< CORECLK source is HFX. */
#define FE310_CORECLK_PLL       2    /**< CORECLK source is PLL. */

#define FE310_PLLSRC_HFR        0   /**< PLL clock source is HFR. */
#define FE310_PLLSRC_HFX        1   /**< PLL clock source is HFX. */

#define FE310_LFCLK_LFR         0   /**< LF clock source is LFR. */
#define FE310_LFCLK_LFX         1   /**< LF clock source is LFX. */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   Disables the PWR/RCC initialization in the HAL.
 */
#if !defined(FE310_NO_INIT) || defined(__DOXYGEN__)
#define FE310_NO_INIT                       FALSE
#endif

/**
 * @brief   Enables or disables the HFR clock source.
 */
#if !defined(FE310_HFR_ENABLED) || defined(__DOXYGEN__)
#define FE310_HFR_ENABLED                   FALSE
#endif

/**
 * @brief   Enables or disables the LFR clock source.
 */
#if !defined(FE310_LFR_ENABLED) || defined(__DOXYGEN__)
#define FE310_LFR_ENABLED                   FALSE
#endif

/**
 * @brief   Enables or disables the HFX clock source.
 */
#if !defined(FE310_HFX_ENABLED) || defined(__DOXYGEN__)
#define FE310_HFX_ENABLED                   TRUE
#endif

/**
 * @brief   Enables or disables the LFX clock source.
 */
#if !defined(FE310_LFX_ENABLED) || defined(__DOXYGEN__)
#define FE310_LFX_ENABLED                   TRUE
#endif

/**
 * @brief   Main clock source selection.
 * @note    If the selected clock source is not the PLL then the PLL is not
 *          initialized and started.
 * @note    The default value is calculated for a 48MHz system clock from
 *          a 16MHz crystal using the PLL.
 */
#if !defined(FE310_CORECLK_SEL) || defined(__DOXYGEN__)
#define FE310_CORECLK_SEL                   FE310_CORECLK_PLL
#endif

/**
 * @brief   Main clock source selection.
 * @note    The default value is calculated for a 32.768kHz low frequency clock
 *          using the external LFX source.
 */
#if !defined(FE310_LFCLK_SEL) || defined(__DOXYGEN__)
#define FE310_LFCLK_SEL                     FE310_LFCLK_LFX
#endif

/**
 * @brief   HFR divider.
 * @note    The default value is calculated for a 14.4 MHz (+-50%) clock.
 */
#if !defined(FE310_PREDIV_VALUE) || defined(__DOXYGEN__)
#define FE310_PREDIV_VALUE                  5
#endif

/**
 * @brief   Clock source for the PLL.
 * @note    This setting has only effect if the PLL is selected as the
 *          system clock source.
 * @note    The default value is calculated for a 48MHz system clock from
 *          a 16MHz crystal using the PLL.
 */
#if !defined(FE310_PLLSRC) || defined(__DOXYGEN__)
#define FE310_PLLSRC                        FE310_PLLSRC_HFX
#endif

/**
 * @brief   PLL pre-divider value.
 * @note    The allowed range is 1...4.
 * @note    The default value is calculated for a 48MHz system clock from
 *          a 16MHz crystal using the PLL.
 */
#if !defined(FE310_PLLPREDIV_VALUE) || defined(__DOXYGEN__)
#define FE310_PLLPREDIV_VALUE               2
#endif

/**
 * @brief   PLL multiplier value.
 * @note    The allowed range is an even number in 2...128.
 * @note    The default value is calculated for a 48MHz system clock from
 *          a 16MHz crystal using the PLL.
 */
#if !defined(FE310_PLLMUL_VALUE) || defined(__DOXYGEN__)
#define FE310_PLLMUL_VALUE                  48
#endif

/**
 * @brief   PLL post-divider value.
 * @note    The allowed range is 2, 4, or 8.
 * @note    The default value is calculated for a 48MHz system clock from
 *          a 16MHz crystal using the PLL.
 */
#if !defined(FE310_PLLPOSTDIV_VALUE) || defined(__DOXYGEN__)
#define FE310_PLLPOSTDIV_VALUE              8
#endif

/**
 * @brief   LFR divider value.
 * @note    The allowed range is 1...32.
 * @note    The default value is calculated for a 30kHz (+-50%) clock.
 */
#if !defined(FE310_LFRDIV_VALUE) || defined(__DOXYGEN__)
#define FE310_LFRDIV_VALUE                  5
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*
 * Configuration-related checks.
 */
#if !defined(FE310_MCUCONF)
#error "Using a wrong mcuconf.h file, FE310_MCUCONF not defined"
#endif

/*
 * HFR related checks.
 */
#if !FE310_HFR_ENABLED
#if FE310_CORECLK_SEL == FE310_CORECLK_HFR
#error "HFR not enabled, required by FE310_CORECLK"
#endif

#if (FE310_CORECLK_SEL == FE310_CORECLK_PLL) &&                                           \
    (FE310_PLLSRC == FE310_PLLSRC_HFR)
#error "HFR not enabled, required by FE310_CORECLK and FE310_PLLSRC"
#endif

#endif /* !FE310_HFR_ENABLED */

/*
 * HFX related checks.
 */
#if FE310_HFX_ENABLED

#if FE310_HFXCLK == 0
#error "HFX frequency not defined"
#elif (FE310_HFXCLK < FE310_HFXCLK_MIN) || (FE310_HFXCLK > FE310_HFXCLK_MAX)
#error "FE310_HFXCLK outside acceptable range (FE310_HFXCLK_MIN...FE310_HFXCLK_MAX)"
#endif

#else /* !FE310_HFX_ENABLED */

#if FE310_CORECLK_SEL == FE310_CORECLK_HFX
#error "HFX not enabled, required by FE310_CORECLK"
#endif

#if (FE310_CORECLK_SEL == FE310_CORECLK_PLL) && (FE310_PLLSRC == FE310_PLLSRC_HFX)
#error "HFX not enabled, required by FE310_CORECLK and FE310_PLLSRC"
#endif

#endif /* !FE310_HFX_ENABLED */

/*
 * LFX related checks.
 */
#if FE310_LFX_ENABLED

#if (FE310_LFXCLK == 0)
#error "LFX frequency not defined"
#endif

#if (FE310_LFXCLK < FE310_LFXCLK_MIN) || (FE310_LFXCLK > FE310_LFXCLK_MAX)
#error "FE310_LFXCLK outside acceptable range (FE310_LFXCLK_MIN...FE310_LFXCLK_MAX)"
#endif

#endif /* !FE310_LFX_ENABLED */

/* PLL activation conditions.*/
#if (FE310_CORECLK_SEL == FE310_CORECLK_PLL) ||                                           \
    defined(__DOXYGEN__)
/**
 * @brief   PLL activation flag.
 */
#define FE310_ACTIVATE_PLL          TRUE
#else
#define FE310_ACTIVATE_PLL          FALSE
#endif

/* HFR prescaler setting check.*/
#if ((FE310_PREDIV_VALUE >= 1) || (FE310_PREDIV_VALUE <= 64))
#define FE310_PREDIV                PCRI_HFR_DIV(FE310_PREDIV_VALUE - 1)
#else
#error "invalid FE310_PREDIV value specified"
#endif

#define FE310_HFRDIVCLK             FE310_HFRCLK / FE310_PREDIV_VALUE

/**
 * @brief   PLL Pre-Divider field.
 */
#if ((FE310_PLLPREDIV_VALUE) >= 1 && (FE310_PLLPREDIV_VALUE <= 4)) ||       \
    defined(__DOXYGEN__)
#define FE310_PLLR                  PCRI_PLL_R(FE310_PLLPREDIV_VALUE - 1)
#else
#error "invalid FE310_PLLPREDIV value specified"
#endif

/**
 * @brief   PLLMUL field.
 */
#if ((FE310_PLLMUL_VALUE >= 2) && (FE310_PLLMUL_VALUE <= 128) && (FE310_PLLMUL_VALUE % 2 == 0)) ||            \
    defined(__DOXYGEN__)
#define FE310_PLLF                  PCRI_PLL_F((FE310_PLLMUL_VALUE / 2) - 1)
#else
#error "invalid FE310_PLLMUL_VALUE value specified"
#endif

/**
 * @brief   PLL Post-Divider field.
 */
#if (FE310_PLLPOSTDIV_VALUE == 2) ||       \
    defined(__DOXYGEN__)
#define FE310_PLLQ                  PCRI_PLL_Q(1)
#elif (FE310_PLLPOSTDIV_VALUE == 4)
#define FE310_PLLQ                  PCRI_PLL_Q(2)
#elif (FE310_PLLPOSTDIV_VALUE == 8)
#define FE310_PLLQ                  PCRI_PLL_Q(3)
#else
#error "invalid FE310_PLLPOSTDIV_VALUE value specified"
#endif

/**
 * @brief   PLL input clock frequency.
 */
#if (FE310_PLLSRC == FE310_PLLSRC_HFX) || defined(__DOXYGEN__)
#define FE310_PLLCLKIN              (FE310_HFXCLK / FE310_PLLPREDIV_VALUE)
#define FE310_PLLREFSEL             PCRI_PLL_REFSEL_HFX
#elif FE310_PLLSRC == FE310_PLLSRC_HFR
#define FE310_PLLCLKIN              (FE310_HFRDIVCLK / FE310_PLLPREDIV_VALUE)
#define FE310_PLLREFSEL             0
#else
#error "invalid FE310_PLLSRC value specified"
#endif

/* PLL input frequency range check.*/
#if (FE310_PLLCLKIN < FE310_PLLIN_MIN) || (FE310_PLLCLKIN > FE310_PLLIN_MAX)
#error "FE310_PLLCLKIN outside acceptable range (FE310_PLLIN_MIN...FE310_PLLIN_MAX)"
#endif

/**
 * @brief   PLL VCO clock frequency.
 */
#define FE310_PLLCLKVCO             (FE310_PLLCLKIN * FE310_PLLMUL_VALUE)

/* PLL VCO frequency range check.*/
#if (FE310_PLLCLKVCO < FE310_PLLVCO_MIN) || (FE310_PLLCLKVCO > FE310_PLLVCO_MAX)
#error "FE310_PLLCLKIN outside acceptable range (FE310_PLLVCO_MIN...FE310_PLLVCO_MAX)"
#endif

/**
 * @brief   PLL output clock frequency.
 */
#define FE310_PLLCLKOUT             (FE310_PLLCLKVCO / FE310_PLLPOSTDIV_VALUE)

/* PLL output frequency range check.*/
#if (FE310_PLLCLKOUT < FE310_PLLOUT_MIN) || (FE310_PLLCLKOUT > FE310_PLLOUT_MAX)
#error "FE310_PLLCLKOUT outside acceptable range (FE310_PLLOUT_MIN...FE310_PLLOUT_MAX)"
#endif

/**
 * @brief   System clock source.
 */
#if (FE310_CORECLK_SEL == FE310_CORECLK_PLL) || defined(__DOXYGEN__)
#define FE310_CORECLK                FE310_PLLCLKOUT
#elif (FE310_CORECLK_SEL == FE310_CORECLK_HFR)
#define FE310_CORECLK                FE310_HFRDIVCLK
#elif (FE310_CORECLK_SEL == FE310_CORECLK_HFX)
#define FE310_CORECLK                FE310_HFXCLK
#else
#error "invalid FE310_CORECLK value specified"
#endif

/**
 * @brief   LFR divider.
 */
#if ((FE310_LFRDIV_VALUE) >= 1 && (FE310_LFRDIV_VALUE <= 64)) ||       \
    defined(__DOXYGEN__)
#define FE310_LFRDIV                PCRI_LFR_DIV(FE310_LFRDIV_VALUE - 1)
#else
#error "invalid FE310_LFRDIV value specified"
#endif

#define FE310_LFRDIVCLK             FE310_LFRCLK / FE310_LFRDIV

/**
 * @brief   LF clock source.
 */
#if (FE310_LFCLK_SEL == FE310_LFCLK_LFR) || defined(__DOXYGEN__)
#define FE310_LFCLK                 FE310_LFRDIVCLK
#elif (FE310_LFCLK_SEL == FE310_LFCLK_LFX)
#define FE310_LFCLK                 FE310_LFXCLK
#else
#error "invalid FE310_LFCLK value specified"
#endif

/* Check on the system clock.*/
#if FE310_CORECLK > FE310_CORECLK_MAX
#error "FE310_CORECLK above maximum rated frequency (FE310_CORECLK_MAX)"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/* Various helpers.*/
#include "plic.h"

#ifdef __cplusplus
extern "C" {
#endif
  void hal_lld_init(void);
  void fe310_clock_init(void);
#ifdef __cplusplus
}
#endif

#endif /* HAL_LLD_H */

/** @} */
