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

#ifndef MCUCONF_H
#define MCUCONF_H

#define FE310_MCUCONF

#define FE310_G002

#define FE310_HFXCLK    16000000
#define FE310_LFXCLK    32768

#define FE310_HFR_ENABLED                   FALSE
#define FE310_LFR_ENABLED                   FALSE
#define FE310_HFX_ENABLED                   TRUE
#define FE310_LFX_ENABLED                   TRUE
#define FE310_CORECLK_SEL                   FE310_CORECLK_PLL
#define FE310_LFCLK_SEL                     FE310_LFCLK_LFX
#define FE310_PREDIV_VALUE                  5
#define FE310_PLLSRC                        FE310_PLLSRC_HFX
#define FE310_PLLPREDIV_VALUE               2
#define FE310_PLLMUL_VALUE                  80
#define FE310_PLLPOSTDIV_VALUE              2
#define FE310_LFRDIV_VALUE                  5

#define FE310_SERIAL_USE_UART0 TRUE
#define FE310_SERIAL_USE_UART1 TRUE

#endif /* MCUCONF_H */
