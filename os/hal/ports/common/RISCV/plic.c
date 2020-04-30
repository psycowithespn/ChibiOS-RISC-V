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
 * @file    common/RISCV/plic.c
 * @brief   RISC-V PLIC support code.
 *
 * @addtogroup COMMON_RISCV_PLIC
 * @{
 */

#include "hal.h"

// TODO: Assumes hart 0 only

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Performs initialization of the PLIC. This includes
 *          setting a safe default priority, disabling all enable lines,
 *          and clearing the priority threshold of all contexts.
 *
 */
void plicInit(void) {

  /* Zero priorities.*/
  size_t i;
  size_t j;
  for (i = 1; i < PLIC_NUM_IRQS; i++)
    PLIC_PRIO->PRIO[i] = 0;

  for (i = 0; i < PLIC_NUM_CONTEXTS; i++)
    for (j = 0; j < PLIC_NUM_IRQS / sizeof (uint32_t); j++)
      PLIC_EN->CONTEXTS[i].EN[j] = 0;

  // TODO: Should this live here?
  for (i = 0; i < PLIC_NUM_CONTEXTS; i++)
    PLIC_CONTEXTS->CONTEXTS[i].PRIO_THRESH = 0;
}

/**
 * @brief   Sets the priority of an interrupt handler and enables it.
 *
 * @param[in] n         the interrupt number
 * @param[in] prio      the interrupt priority
 */
void plicEnableInterrupt(uint32_t n, uint32_t prio) {

  PLIC_PRIO->PRIO[n] = prio;
  PLIC_EN->CONTEXTS[0].EN[n / sizeof (uint32_t)] |= 1 << (n % sizeof (uint32_t));
}

/**
 * @brief   Disables an interrupt handler.
 *
 * @param[in] n         the interrupt number
 */
void plicDisableInterrupt(uint32_t n) {

  PLIC_EN->CONTEXTS[0].EN[n / sizeof (uint32_t)] &= ~(1 << (n % sizeof (uint32_t)));
}

/** @} */
