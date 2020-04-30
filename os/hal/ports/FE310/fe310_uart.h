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
 * @file    fe310_uart.h
 * @brief   FE310 UART units common header.
 *
 * @addtogroup FE310_UART
 * @{
 */

#ifndef FE310_UART_H
#define FE310_UART_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    UART definitions
 * @{
 */
#define UART0                           ((fe310_uart_t *)0x10013000)
#define UART1                           ((fe310_uart_t *)0x10023000)
/** @} */

/**
 * @name    TXDATA register definitions
 * @{
 */
#define UART_TXDATA_DATA_SHIFT          0
#define UART_TXDATA_DATA_MASK           0xFF
#define UART_TXDATA_DATA(n)             (((n) & UART_TXDATA_DATA_MASK) << UART_TXDATA_DATA_SHIFT)

#define UART_TXDATA_FULL                (1 << 31)
/** @} */

/**
 * @name    RXDATA register definitions
 * @{
 */
#define UART_RXDATA_DATA_SHIFT          0
#define UART_RXDATA_DATA_MASK           0xFF
#define UART_RXDATA_DATA(n)             (((n) & UART_RXDATA_DATA_MASK) << UART_RXDATA_DATA_SHIFT)

#define UART_RXDATA_EMPTY               (1 << 31)
/** @} */

/**
 * @name    TXCTRL register definitions
 * @{
 */
#define UART_TXCTRL_TXEN                (1 << 0)

#define UART_TXCTRL_NSTOP_MASK          (1 << 1)
#define UART_TXCTRL_NSTOP_1             (0)
#define UART_TXCTRL_NSTOP_2             (1 << 1)

#define UART_TXCTRL_TXCNT_SHIFT         16
#define UART_TXCTRL_TXCNT_MASK          0x7
#define UART_TXCTRL_TXCNT(n)            (((n) & UART_TXCTRL_TXCNT_MASK) << UART_TXCTRL_TXCNT_SHIFT)
/** @} */

/**
 * @name    RXCTRL register definitions
 * @{
 */
#define UART_RXCTRL_RXEN                (1 << 0)

#define UART_RXCTRL_RXCNT_SHIFT         16
#define UART_RXCTRL_RXCNT_MASK          0x7
#define UART_RXCTRL_RXCNT(n)            (((n) & UART_RXCTRL_RXCNT_MASK) << UART_RXCTRL_RXCNT_SHIFT)
/** @} */

/**
 * @name    IE register definitions
 * @{
 */
#define UART_IE_TXWM                    (1 << 0)
#define UART_IE_RXWM                    (1 << 1)
/** @} */

/**
 * @name    IP register definitions
 * @{
 */
#define UART_IP_TXWM                    (1 << 0)
#define UART_IP_RXWM                    (1 << 1)
/** @} */

/**
 * @name    DIV register definitions
 * @{
 */
#define UART_DIV_DIV_SHIFT              0
#define UART_DIV_DIV_MASK               0xFFFF
#define UART_DIV_DIV(n)                 (((n) & UART_DIV_DIV_MASK) << UART_DIV_DIV_SHIFT)
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
 * @brief   FE310 UART registers block.
 */
typedef struct {

  volatile uint32_t   TXDATA;
  volatile uint32_t   RXDATA;
  volatile uint32_t   TXCTRL;
  volatile uint32_t   RXCTRL;
  volatile uint32_t   IE;
  volatile uint32_t   IP;
  volatile uint32_t   DIV;
} fe310_uart_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* FE310_UART_H */

/** @} */
