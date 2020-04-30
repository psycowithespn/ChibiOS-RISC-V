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

#include "ch.h"
#include "hal.h"
#include "rt_test_root.h"
#include "oslib_test_root.h"

extern thread_reference_t blinkerRef;
thread_reference_t blinkerRef = NULL;

static const ioline_t LINE_LED = PAL_LINE(IOPORT1, 5);

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * an LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;

  chRegSetThreadName("blinker");
  while (true) {
    palToggleLine (LINE_LED);
    chThdSleepMilliseconds (500);
  }
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Activates the serial driver 0 using the driver default configuration.
   * GPIO 16(RX) and 17(TX) are routed to UART0.
   */
  sdStart(&SD0, NULL);
  palSetPadMode(GPIO0, 16, PAL_MODE_ALTERNATE(0));
  palSetPadMode(GPIO0, 17, PAL_MODE_ALTERNATE(0));

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 1, Thread1, NULL);

  palSetLineMode (LINE_LED, PAL_MODE_OUTPUT_PUSHPULL);

  test_execute((BaseSequentialStream *)&SD0, &rt_test_suite);
  test_execute((BaseSequentialStream *)&SD0, &oslib_test_suite);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
