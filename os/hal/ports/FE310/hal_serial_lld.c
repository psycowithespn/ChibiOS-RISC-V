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
 * @file    hal_serial_lld.c
 * @brief   FE310 serial subsystem low level driver source.
 *
 * @addtogroup SERIAL
 * @{
 */

#include "hal.h"

#if (HAL_USE_SERIAL == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief UART0 serial driver identifier.*/
#if (FE310_SERIAL_USE_UART0 == TRUE) || defined(__DOXYGEN__)
SerialDriver SD0;
#endif

/** @brief UART1 serial driver identifier.*/
#if (FE310_SERIAL_USE_UART1 == TRUE) || defined(__DOXYGEN__)
SerialDriver SD1;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver default configuration.
 */
static const SerialConfig default_config = {
  SERIAL_DEFAULT_BITRATE
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Common IRQ handler.
 *
 * @param[in] sdp       communication channel associated to the UART
 */
static void serve_interrupt(SerialDriver *sdp) {
  fe310_uart_t *u = sdp->uart;
  uint32_t ie = u->IE;
  uint32_t ip = u->IP;

  /* Data available.*/
  osalSysLockFromISR();
  if ((ie & UART_IE_RXWM) && (ip & UART_IP_RXWM)) {
    uint32_t data;
    while (!((data = u->RXDATA) & UART_RXDATA_EMPTY)) {
      sdIncomingDataI(sdp, (uint8_t) data);
    }
  }
  osalSysUnlockFromISR();

  /* Transmission buffer empty.*/
  if ((ie & UART_IE_TXWM) && (ip & UART_IP_TXWM)) {
    msg_t b;
    osalSysLockFromISR();
    // The first byte is special. If it is missing, disable the interrupt.
    b = oqGetI(&sdp->oqueue);
    if (b < MSG_OK) {
      // TX End is an unknown with this peripheral.
      // Nasty hack to just send TX end with empty.
      chnAddFlagsI(sdp, CHN_OUTPUT_EMPTY);
      chnAddFlagsI(sdp, CHN_TRANSMISSION_END);
      u->IE &= ~UART_IE_TXWM;
    }
    else
    {
      u->TXDATA = (uint8_t) b;
      while (!(u->TXDATA & UART_TXDATA_FULL)) {
        b = oqGetI(&sdp->oqueue);
        if (b < MSG_OK)
          break;
        u->TXDATA = (uint8_t) b;
      }
    }
    osalSysUnlockFromISR();
  }
}

#if FE310_SERIAL_USE_UART0 == TRUE
static void notify0(io_queue_t *qp) {

  (void) qp;
  UART0->IE |= UART_IE_TXWM;
}
#endif

#if FE310_SERIAL_USE_UART1 == TRUE
static void notify1(io_queue_t *qp) {

  (void) qp;
  UART1->IE |= UART_IE_TXWM;
}
#endif

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if FE310_SERIAL_USE_UART0 || defined(__DOXYGEN__)
/**
 * @brief   USART0 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(Interrupt3) {

  OSAL_IRQ_PROLOGUE();

  serve_interrupt(&SD0);

  OSAL_IRQ_EPILOGUE();
}
#endif

#if FE310_SERIAL_USE_UART1 || defined(__DOXYGEN__)
/**
 * @brief   USART1 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(Interrupt4) {

  OSAL_IRQ_PROLOGUE();

  serve_interrupt(&SD1);

  OSAL_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level serial driver initialization.
 *
 * @notapi
 */
void sd_lld_init(void) {

#if FE310_SERIAL_USE_UART0 == TRUE
  sdObjectInit(&SD0, NULL, notify0);
  SD0.uart = UART0;
#endif

#if FE310_SERIAL_USE_UART1 == TRUE
  sdObjectInit(&SD1, NULL, notify1);
  SD1.uart = UART1;
#endif
}

/**
 * @brief   Low level serial driver configuration and (re)start.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 * @param[in] config    the architecture-dependent serial driver configuration.
 *                      If this parameter is set to @p NULL then a default
 *                      configuration is used.
 *
 * @notapi
 */
void sd_lld_start(SerialDriver *sdp, const SerialConfig *config) {

  fe310_uart_t *u = sdp->uart;

  if (config == NULL) {
    config = &default_config;
  }

  if (sdp->state == SD_STOP) {
    if (0) {

    }
#if FE310_SERIAL_USE_UART0 == TRUE
    else if (sdp == &SD0)
    {
      plicEnableInterrupt(3, 1);
    }
#endif

#if FE310_SERIAL_USE_UART1 == TRUE
    else if (sdp == &SD1)
    {
      plicEnableInterrupt(4, 1);
    }
#endif
  }

  /* Configures the peripheral.*/
  /* Baud rate setting.*/
  u->DIV = UART_DIV_DIV ((FE310_CORECLK / config->speed) - 1);

  /* Enable transmitting with a watermark meaning empty.*/
  /* TODO: stop bits.*/
  u->TXCTRL = UART_TXCTRL_TXEN | UART_TXCTRL_NSTOP_1 | UART_TXCTRL_TXCNT(1);

  /* Enable receiving with a watermark meaning data is present.*/
  u->RXCTRL = UART_RXCTRL_RXEN | UART_RXCTRL_RXCNT(1);

  /* Enable receive interrupt only.*/
  u->IE = UART_IE_RXWM;
}

/**
 * @brief   Low level serial driver stop.
 * @details De-initializes the USART, stops the associated clock, resets the
 *          interrupt vector.
 *
 * @param[in] sdp       pointer to a @p SerialDriver object
 *
 * @notapi
 */
void sd_lld_stop(SerialDriver *sdp) {

  fe310_uart_t *u = sdp->uart;

  if (sdp->state == SD_READY) {
    /* Disable interrupts.*/
    u->IE = 0;

    /* Stop all actions.*/
    u->TXCTRL = 0;
    u->RXCTRL = 0;

    /* Reconfigure PLIC.*/
    if (0) {

    }
#if FE310_SERIAL_USE_UART0 == TRUE
    else if (sdp == &SD0)
    {
      plicDisableInterrupt(3);
    }
#endif

#if FE310_SERIAL_USE_UART1 == TRUE
    else if (sdp == &SD1)
    {
      plicDisableInterrupt(4);
    }
#endif
  }
}

#endif /* HAL_USE_SERIAL == TRUE */

/** @} */
