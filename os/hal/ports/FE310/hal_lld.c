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
 * @file    FE310F0xx/hal_lld.c
 * @brief   FE310F0xx HAL subsystem low level driver source.
 *
 * @addtogroup HAL
 * @{
 */

#include "hal.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level HAL driver initialization.
 *
 * @notapi
 */
void hal_lld_init(void) {

  /* IRQ subsystem initialization.*/
  plicInit ();
}

/**
 * @brief   FE310 clocks and PLL initialization.
 * @note    All the involved constants come from the file @p board.h.
 * @note    This function should be invoked just after the system reset.
 *
 * @special
 */
void fe310_clock_init(void) {

#if !FE310_NO_INIT
  /* HFR setup, it enforces the reset situation in order to handle possible
     problems with JTAG probes and re-initializations.*/
  // TODO: Read trim from OTP.
  PCRI->HFROSCCFG = (PCRI->HFROSCCFG & ~(PCRI_HFR_TRIM_MASK << PCRI_HFR_TRIM_SHIFT)) | FE310_PREDIV;
  PCRI->HFROSCCFG |= PCRI_HFR_EN;           /* Make sure HFR is ON.         */
  while (!(PCRI->HFROSCCFG & PCRI_HFR_RDY))
    ;                                       /* Wait until HFR is stable.    */

  /* HFR is selected as new source.*/
  PCRI->PLLCFG &= ~PCRI_PLL_SEL_PLL;        /* Select HFR instead of PLL.   */
  PCRI->PLLCFG |= PCRI_PLL_BYPASS;          /* Bypass PLL to allow config.  */

#if FE310_HFX_ENABLED
  /* HFX activation.*/
  PCRI->HFXOSCCFG |= PCRI_HFX_EN;
  while (!(PCRI->HFXOSCCFG & PCRI_HFX_RDY))
    ;                                       /* Waits until HFX is stable.   */
#else
  /* HFX disable.*/
  PCRI->HFXOSCCFG &= ~PCRI_HFX_EN;
#endif

#if FE310_ACTIVATE_PLL
  /* PLL configuration and activation.*/
  PCRI->PLLCFG = FE310_PLLR | FE310_PLLF | FE310_PLLQ | FE310_PLLREFSEL;
  // TODO: Sleep before checking lock.
  while (!(PCRI->PLLCFG & PCRI_PLL_LOCK))
    ;                                       /* Waits until PLL is stable.   */
#endif

  /* Switching to the configured clock source if it is different from HFR.*/
#if (FE310_CORECLK_SEL == FE310_CORECLK_HFX)
  /* Requires hardware pin to be pulled low.*/
#elif (FE310_CORECLK_SEL == FE310_CORECLK_PLL)
  /* Switches clock source.*/
  PCRI->PLLCFG |= PCRI_PLL_SEL_PLL;
#endif

#if !FE310_HFR_ENABLED
  /* HFR disable.*/
  PCRI->HFROSCCFG &= ~PCRI_HFR_EN;
#endif

#if (FE310_LFCLK_SEL == FE310_LFCLK_LFR)
  PCRI->LFXOSCCFG &= ~PCRI_LFX_SEL_LFX;
#else
  PCRI->LFXOSCCFG |= PCRI_LFX_SEL_LFX;
#endif

#if FE310_LFR_ENABLED
  /* LFR configuration.*/
  PCRI->LFROSCCFG = PCRI->LFROSCCFG & ~(PCRI_LFR_DIV_MASK << PCRI_LFR_DIV_SHIFT) | FE310_LFRDIV
  /* LFR activation.*/
  PCRI->LFROSCCFG |= PCRI_LFR_EN;
  while ((PCRI->LFROSCCFG & PCRI_LFR_RDY) == 0)
    ;                                       /* Waits until LFR is stable.   */
#endif

#if !FE310_LFR_ENABLED
  /* LFR disable.*/
  PCRI->LFROSCCFG &= ~PCRI_LFR_EN;
#endif

#endif /* !FE310_NO_INIT */
}

/** @} */
