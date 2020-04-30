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
 * @file    common/RISCV/plic.h
 * @brief   RISC-V PLIC support macros and structures.
 *
 * @addtogroup COMMON_RISCV_PLIC
 * @{
 */

#ifndef PLIC_H
#define PLIC_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

#define PLIC_MAX_NUM_IRQS           1024
#define PLIC_MAX_NUM_CONTEXTS       15872

// Prio includes nonexistent IRQ 0 for code consistency.
#define PLIC_PRIO       ((riscv_plic_iprio_t *)     (PLIC_BASE + 0x000000))
#define PLIC_PEND       ((riscv_plic_ipend_t *)     (PLIC_BASE + 0x001000))
#define PLIC_EN         ((riscv_plic_iens_t *)      (PLIC_BASE + 0x002000))
#define PLIC_CONTEXTS   ((riscv_plic_contexts_t *)  (PLIC_BASE + 0x200000))

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#ifndef RISCV_HAS_PLIC
#error "plic.h requires the device to have a PLIC"
#endif

/* Validation for PLIC_NUM_IRQS. It should be set to include the missing IRQ 0.*/
#if !defined(PLIC_NUM_IRQS) || (PLIC_NUM_IRQS > PLIC_MAX_NUM_IRQS)
#error "PLIC_NUM_IRQS is invalid or not defined"
#endif

#if !defined(PLIC_NUM_CONTEXTS) || (PLIC_NUM_CONTEXTS > PLIC_MAX_NUM_CONTEXTS)
#error "PLIC_NUM_CONTEXTS is invalid or not defined"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

typedef struct
{
    volatile uint32_t   PRIO[PLIC_MAX_NUM_IRQS];
} riscv_plic_iprio_t;

typedef struct
{
    volatile uint32_t   PEND[PLIC_MAX_NUM_IRQS / sizeof (uint32_t)];
} riscv_plic_ipend_t;

typedef struct
{
    volatile uint32_t   EN[PLIC_MAX_NUM_IRQS / sizeof (uint32_t)];
} riscv_plic_ien_t;

typedef struct
{
    riscv_plic_ien_t    CONTEXTS[PLIC_MAX_NUM_CONTEXTS];
} riscv_plic_iens_t;

typedef struct
{
    volatile uint32_t   PRIO_THRESH;
    volatile uint32_t   CLAIM_COMPLETE;
} riscv_plic_context_t;

typedef struct
{
    riscv_plic_context_t    CONTEXTS[PLIC_MAX_NUM_CONTEXTS];
} riscv_plic_contexts_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void plicInit(void);
  void plicEnableInterrupt(uint32_t n, uint32_t prio);
  void plicDisableInterrupt(uint32_t n);
#ifdef __cplusplus
}
#endif

#endif /* PLIC_H */

/** @} */
