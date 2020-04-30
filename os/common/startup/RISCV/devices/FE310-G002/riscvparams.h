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
 * @file    devices/FE310/riscvparams.h
 * @brief   FE310-G002 inclusion header.
 *
 * @addtogroup FE310-G002
 * @{
 */
/**@} */
#ifndef _RISCVPARAMS_H_
#define _RISCVPARAMS_H_

/**
 * @brief PLIC parameters
 */
#define RISCV_HAS_PLIC
#define PLIC_BASE           0x0C000000
#define PLIC_MAX_PRIO       7
#define PLIC_MAX_KERN_PRIO  5
#define PLIC_NUM_IRQS       53
#define PLIC_NUM_CONTEXTS   1

#endif /* _RISCVPARAMS_H_ */

