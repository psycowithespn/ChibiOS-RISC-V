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
 * @file    hal_st_lld.h
 * @brief   RISC-V ST subsystem low level driver header.
 * @details This header is designed to be include-able without having to
 *          include other files from the HAL.
 *
 * @addtogroup ST
 * @{
 */

#ifndef HAL_ST_LLD_H
#define HAL_ST_LLD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

#define RISCV_MTIMECMP0 (*(volatile uint32_t *) 0x2004000)
#define RISCV_MTIMECMPH0 (*(volatile uint32_t *) 0x2004004)

#define RISCV_MTIME (*(volatile uint32_t *) 0x200BFF8)
#define RISCV_MTIMEH (*(volatile uint32_t *) 0x200BFFC)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if CH_CFG_ST_RESOLUTION != 64
#error "RISC-V requires CH_CFG_ST_RESOLUTION == 64"
#endif

#if CH_CFG_ST_FREQUENCY != 32768
#error "RISC-V requires CH_CFG_ST_FREQUENCY == 32768"
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

#ifdef __cplusplus
extern "C" {
#endif
  void st_lld_init(void);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Driver inline functions.                                                  */
/*===========================================================================*/

/**
 * @brief   Returns the time counter value.
 *
 * @return              The counter value.
 *
 * @notapi
 */
static inline systime_t st_lld_get_counter(void) {

  uint32_t high, low, temp;
  do
  {
    high = RISCV_MTIMEH;
    low = RISCV_MTIME;
    temp = RISCV_MTIMEH;
  } while (high != temp);

  return (((systime_t) high) << 32) | (systime_t) low;
}

/**
 * @brief   Starts the alarm.
 * @note    Makes sure that no spurious alarms are triggered after
 *          this call.
 *
 * @param[in] abstime   the time to be set for the first alarm
 *
 * @notapi
 */
static inline void st_lld_start_alarm(systime_t abstime) {

  RISCV_MTIMECMPH0 = 0xFFFFFFFF;
  RISCV_MTIMECMP0 = (uint32_t) abstime;
  RISCV_MTIMECMPH0 = (uint32_t) (abstime >> 32);

  int mtie = 0x80;
  RISCV_CSR_SET (mie, mtie);
}

/**
 * @brief   Stops the alarm interrupt.
 *
 * @notapi
 */
static inline void st_lld_stop_alarm(void) {

  int mtie = 0x80;
  RISCV_CSR_CLEAR (mie, mtie);
}

/**
 * @brief   Sets the alarm time.
 *
 * @param[in] abstime   the time to be set for the next alarm
 *
 * @notapi
 */
static inline void st_lld_set_alarm(systime_t abstime) {

  RISCV_MTIMECMPH0 = 0xFFFFFFFF;
  RISCV_MTIMECMP0 = (uint32_t) abstime;
  RISCV_MTIMECMPH0 = (uint32_t) (abstime >> 32);
}

/**
 * @brief   Returns the current alarm time.
 *
 * @return              The currently set alarm time.
 *
 * @notapi
 */
static inline systime_t st_lld_get_alarm(void) {

  return (((systime_t) RISCV_MTIMECMPH0) << 32) | (systime_t) RISCV_MTIMECMP0;
}

/**
 * @brief   Determines if the alarm is active.
 *
 * @return              The alarm status.
 * @retval false        if the alarm is not active.
 * @retval true         is the alarm is active
 *
 * @notapi
 */
static inline bool st_lld_is_alarm_active(void) {

  uint32_t value;
  RISCV_CSR_READ (value, MIP);
  return value & 0x80;
}

#endif /* HAL_ST_LLD_H */

/** @} */
