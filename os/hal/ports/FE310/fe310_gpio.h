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
 * @file    fe310_gpio.h
 * @brief   FE310 GPIO units common header.
 *
 * @addtogroup FE310_GPIO
 * @{
 */

#ifndef FE310_GPIO_H
#define FE310_GPIO_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    GPIO ports definitions
 * @{
 */
#define GPIO0                           ((fe310_gpio_t *)0x10012000)
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
 * @brief   FE310 GPIO registers block.
 */
typedef struct {

  volatile uint32_t   INPUT_VAL;
  volatile uint32_t   INPUT_EN;
  volatile uint32_t   OUTPUT_EN;
  volatile uint32_t   OUTPUT_VAL;
  volatile uint32_t   PULLUP_EN;
  volatile uint32_t   DRIVE_STR;
  volatile uint32_t   RISE_IE;
  volatile uint32_t   RISE_IP;
  volatile uint32_t   FALL_IE;
  volatile uint32_t   FALL_IP;
  volatile uint32_t   HIGH_IE;
  volatile uint32_t   HIGH_IP;
  volatile uint32_t   LOW_IE;
  volatile uint32_t   LOW_IP;
  volatile uint32_t   IOF_EN;
  volatile uint32_t   IOF_SEL;
  volatile uint32_t   OUT_XOR;
} fe310_gpio_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* FE310_GPIO_H */

/** @} */
