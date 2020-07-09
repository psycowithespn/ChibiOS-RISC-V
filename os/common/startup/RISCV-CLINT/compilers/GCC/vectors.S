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
 * @file    RISCV/GCC/vectors.S
 * @brief   Interrupt vectors for RISC-V devices.
 *
 * @defgroup RISCV_GCC_VECTORS RISC-V Interrupt Vectors
 * @{
 */

#define _FROM_ASM_

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Code section.                                                             */
/*===========================================================================*/

#if !defined(__DOXYGEN__)

        .section    .vectors, "ax"
        .align      2
        .globl      Reset_Handler
Reset_Handler:
        j           _crt0_entry

        .text
        .align      6
        .globl      _trapEnter
_trapEnter:
        j           TrapEnter

        .globl      ExceptionTable
ExceptionTable:
        .word       Exception0
        .word       Exception1
        .word       Exception2
        .word       Exception3
        .word       Exception4
        .word       Exception5
        .word       Exception6
        .word       Exception7
        .word       Exception8
        .word       Exception9
        .word       Exception10
        .word       Exception11

        .globl      VectorTable
VectorTable:
        .word       Vector0
        .word       Vector1
        .word       Vector2
        .word       VectorMSI
        .word       Vector4
        .word       Vector5
        .word       Vector6
        .word       VectorMTI
        .word       Vector8
        .word       Vector9
        .word       Vector10
        .word       VectorMEI

        .weak       TrapEnter
TrapEnter:
        .weak       Exception0
Exception0:
        .weak       Exception1
Exception1:
        .weak       Exception2
Exception2:
        .weak       Exception3
Exception3:
        .weak       Exception4
Exception4:
        .weak       Exception5
Exception5:
        .weak       Exception6
Exception6:
        .weak       Exception7
Exception7:
        .weak       Exception8
Exception8:
        .weak       Exception9
Exception9:
        .weak       Exception10
Exception10:
        .weak       Exception11
Exception11:
        .weak       Vector0
Vector0:
        .weak       Vector1
Vector1:
        .weak       Vector2
Vector2:
        .weak       VectorMSI
VectorMSI:
        .weak       Vector4
Vector4:
        .weak       Vector5
Vector5:
        .weak       Vector6
Vector6:
        .weak       VectorMTI
VectorMTI:
        .weak       Vector8
Vector8:
        .weak       Vector9
Vector9:
        .weak       Vector10
Vector10:
        .weak       VectorMEI
VectorMEI:
        j          _unhandled_exception

        .weak       _unhandled_exception
_unhandled_exception:
        // Unstack the registers for debuggability.
        lw      a0, 0(sp)
        lw      a1, 4(sp)
        lw      a2, 8(sp)
        lw      a3, 12(sp)
        lw      a4, 16(sp)
        lw      a5, 20(sp)
        lw      a6, 24(sp)
        lw      a7, 28(sp)
        lw      t0, 32(sp)
        lw      t1, 36(sp)
        lw      t2, 40(sp)
        lw      t3, 44(sp)
        lw      t4, 48(sp)
        lw      t5, 52(sp)
        lw      t6, 56(sp)
        lw      ra, 60(sp)
.stay:
        j           .stay

#endif /* !defined(__DOXYGEN__) */

/** @} */
