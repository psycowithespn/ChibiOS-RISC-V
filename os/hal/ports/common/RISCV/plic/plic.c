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
 * @file    common/RISCV/plic/plic.c
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

OSAL_IRQ_HANDLER(PlicUnhandledInterrupt);

#if PLIC_LAST_IRQ >= 4
OSAL_IRQ_HANDLER(PlicInterrupt1)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt2)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt3)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt4)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 8
OSAL_IRQ_HANDLER(PlicInterrupt5)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt6)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt7)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt8)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 12
OSAL_IRQ_HANDLER(PlicInterrupt9)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt10)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt11)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt12)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 16
OSAL_IRQ_HANDLER(PlicInterrupt13)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt14)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt15)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt16)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 20
OSAL_IRQ_HANDLER(PlicInterrupt17)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt18)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt19)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt20)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 24
OSAL_IRQ_HANDLER(PlicInterrupt21)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt22)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt23)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt24)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 28
OSAL_IRQ_HANDLER(PlicInterrupt25)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt26)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt27)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt28)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 32
OSAL_IRQ_HANDLER(PlicInterrupt29)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt30)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt31)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt32)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 36
OSAL_IRQ_HANDLER(PlicInterrupt33)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt34)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt35)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt36)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 40
OSAL_IRQ_HANDLER(PlicInterrupt37)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt38)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt39)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt40)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 44
OSAL_IRQ_HANDLER(PlicInterrupt41)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt42)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt43)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt44)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 48
OSAL_IRQ_HANDLER(PlicInterrupt45)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt46)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt47)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt48)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

#if PLIC_LAST_IRQ >= 52
OSAL_IRQ_HANDLER(PlicInterrupt49)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt50)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt51)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
OSAL_IRQ_HANDLER(PlicInterrupt52)  __attribute__((weak, alias("PlicUnhandledInterrupt")));
#endif

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

static OSAL_IRQ_HANDLER((* const plicIntTable[PLIC_NUM_IRQS])) = {
  // Interrupt 0 means no interrupt. This is a dummy value used to allow
  // going from the claim register to indexing into this table with
  // just a shift operation, no add.
  PlicUnhandledInterrupt,

#if PLIC_LAST_IRQ >= 4
  PlicInterrupt1,
  PlicInterrupt2,
  PlicInterrupt3,
  PlicInterrupt4,
#endif

#if PLIC_LAST_IRQ >= 8
  PlicInterrupt5,
  PlicInterrupt6,
  PlicInterrupt7,
  PlicInterrupt8,
#endif

#if PLIC_LAST_IRQ >= 12
  PlicInterrupt9,
  PlicInterrupt10,
  PlicInterrupt11,
  PlicInterrupt12,
#endif

#if PLIC_LAST_IRQ >= 16
  PlicInterrupt13,
  PlicInterrupt14,
  PlicInterrupt15,
  PlicInterrupt16,
#endif

#if PLIC_LAST_IRQ >= 20
  PlicInterrupt17,
  PlicInterrupt18,
  PlicInterrupt19,
  PlicInterrupt20,
#endif

#if PLIC_LAST_IRQ >= 24
  PlicInterrupt21,
  PlicInterrupt22,
  PlicInterrupt23,
  PlicInterrupt24,
#endif

#if PLIC_LAST_IRQ >= 28
  PlicInterrupt25,
  PlicInterrupt26,
  PlicInterrupt27,
  PlicInterrupt28,
#endif

#if PLIC_LAST_IRQ >= 32
  PlicInterrupt29,
  PlicInterrupt30,
  PlicInterrupt31,
  PlicInterrupt32,
#endif

#if PLIC_LAST_IRQ >= 36
  PlicInterrupt33,
  PlicInterrupt34,
  PlicInterrupt35,
  PlicInterrupt36,
#endif

#if PLIC_LAST_IRQ >= 40
  PlicInterrupt37,
  PlicInterrupt38,
  PlicInterrupt39,
  PlicInterrupt40,
#endif

#if PLIC_LAST_IRQ >= 44
  PlicInterrupt41,
  PlicInterrupt42,
  PlicInterrupt43,
  PlicInterrupt44,
#endif

#if PLIC_LAST_IRQ >= 48
  PlicInterrupt45,
  PlicInterrupt46,
  PlicInterrupt47,
  PlicInterrupt48,
#endif

#if PLIC_LAST_IRQ >= 52
  PlicInterrupt49,
  PlicInterrupt50,
  PlicInterrupt51,
  PlicInterrupt52,
#endif
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/**
 * @brief   PLIC MEI interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(PlicUnhandledInterrupt) {

  OSAL_IRQ_PROLOGUE();

  osalSysHalt("Unhandled PLIC interrupt");

  OSAL_IRQ_EPILOGUE();
}

/**
 * @brief   PLIC MEI interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(VectorMEI) {

  OSAL_IRQ_PROLOGUE();

  uint32_t claimed;

  while ((claimed = *PLIC_CLAIM_COMPLETE) != 0)
  {
    plicIntTable[claimed]();
    *PLIC_CLAIM_COMPLETE = claimed;
  }

  OSAL_IRQ_EPILOGUE();
}

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
