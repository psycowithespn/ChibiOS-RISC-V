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
 * @file    hal_pal_lld.c
 * @brief   FE310 PAL subsystem low level driver source.
 *
 * @addtogroup PAL
 * @{
 */

#include "hal.h"

#if (HAL_USE_PAL == TRUE) || defined(__DOXYGEN__)

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
 * @brief   STM32 I/O ports configuration.
 *
 * @notapi
 */
void _pal_lld_init(void) {

}

/**
 * @brief   Pads mode setup.
 * @details This function programs a pads group belonging to the same port
 *          with the specified mode.
 *
 * @param[in] port      the port identifier
 * @param[in] mask      the group mask
 * @param[in] mode      the mode
 *
 * @notapi
 */
void _pal_lld_setgroupmode(ioportid_t port,
                           ioportmask_t mask,
                           iomode_t mode) {

  uint32_t moder   = (mode & PAL_FE310_MODE_MASK) >> 0;
  uint32_t ospeedr = (mode & PAL_FE310_OSPEED_MASK) >> 3;
  uint32_t pupdr   = (mode & PAL_FE310_PUPDR_MASK) >> 5;
  uint32_t altr    = (mode & PAL_FE310_ALTERNATE_MASK) >> 7;
  uint32_t bit     = 0;
  while (true) {
    if ((mask & 1) != 0) {
      uint32_t m1 = 1 << bit;

      if (pupdr)
        port->PULLUP_EN |= m1;
      else
        port->PULLUP_EN &= ~m1;

      if (moder == PAL_FE310_MODE_ALTERNATE) {
        /* If going in alternate mode then the alternate number is set
           before switching mode in order to avoid glitches.*/
        port->INPUT_EN &= ~m1;
        port->OUTPUT_EN &= ~m1;
        if (altr)
          port->IOF_SEL |= m1;
        else
          port->IOF_SEL &= ~m1;
        port->IOF_EN |= m1;
      }
      else {
        if (moder == PAL_FE310_MODE_NONE) {
          port->INPUT_EN &= ~m1;
          port->OUTPUT_EN &= ~m1;
        }
        else {
          // Both input and output have both input_en and output_en set.
          port->INPUT_EN |= m1;
          port->OUTPUT_EN |= m1;
        }
        /* If going into a non-alternate mode then the mode is switched
           before setting the alternate mode in order to avoid glitches.*/
        port->IOF_EN &= ~m1;
        port->IOF_SEL &= ~m1;
      }

      if (ospeedr)
        port->DRIVE_STR |= m1;
      else
        port->DRIVE_STR &= ~m1;
    }
    mask >>= 1;
    if (!mask)
      return;
    bit++;
  }
}

#endif /* HAL_USE_PAL == TRUE */

/** @} */
