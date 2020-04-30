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

        .globl      InterruptTable
InterruptTable:
        .word       Interrupt0
        .word       Interrupt1
        .word       Interrupt2
        .word       Interrupt3
        .word       Interrupt4
        .word       Interrupt5
        .word       Interrupt6
        .word       Interrupt7
        .word       Interrupt8
        .word       Interrupt9
        .word       Interrupt10
        .word       Interrupt11
        .word       Interrupt12
        .word       Interrupt13
        .word       Interrupt14
        .word       Interrupt15
        .word       Interrupt16
        .word       Interrupt17
        .word       Interrupt18
        .word       Interrupt19
        .word       Interrupt20
        .word       Interrupt21
        .word       Interrupt22
        .word       Interrupt23
        .word       Interrupt24
        .word       Interrupt25
        .word       Interrupt26
        .word       Interrupt27
        .word       Interrupt28
        .word       Interrupt29
        .word       Interrupt30
        .word       Interrupt31
        .word       Interrupt32
        .word       Interrupt33
        .word       Interrupt34
        .word       Interrupt35
        .word       Interrupt36
        .word       Interrupt37
        .word       Interrupt38
        .word       Interrupt39
        .word       Interrupt40
        .word       Interrupt41
        .word       Interrupt42
        .word       Interrupt43
        .word       Interrupt44
        .word       Interrupt45
        .word       Interrupt46
        .word       Interrupt47
        .word       Interrupt48
        .word       Interrupt49
        .word       Interrupt50
        .word       Interrupt51
        .word       Interrupt52

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
        .weak       Interrupt0
Interrupt0:
        .weak       Interrupt1
Interrupt1:
        .weak       Interrupt2
Interrupt2:
        .weak       Interrupt3
Interrupt3:
        .weak       Interrupt4
Interrupt4:
        .weak       Interrupt5
Interrupt5:
        .weak       Interrupt6
Interrupt6:
        .weak       Interrupt7
Interrupt7:
        .weak       Interrupt8
Interrupt8:
        .weak       Interrupt9
Interrupt9:
        .weak       Interrupt10
Interrupt10:
        .weak       Interrupt11
Interrupt11:
        .weak       Interrupt12
Interrupt12:
        .weak       Interrupt13
Interrupt13:
        .weak       Interrupt14
Interrupt14:
        .weak       Interrupt15
Interrupt15:
        .weak       Interrupt16
Interrupt16:
        .weak       Interrupt17
Interrupt17:
        .weak       Interrupt18
Interrupt18:
        .weak       Interrupt19
Interrupt19:
        .weak       Interrupt20
Interrupt20:
        .weak       Interrupt21
Interrupt21:
        .weak       Interrupt22
Interrupt22:
        .weak       Interrupt23
Interrupt23:
        .weak       Interrupt24
Interrupt24:
        .weak       Interrupt25
Interrupt25:
        .weak       Interrupt26
Interrupt26:
        .weak       Interrupt27
Interrupt27:
        .weak       Interrupt28
Interrupt28:
        .weak       Interrupt29
Interrupt29:
        .weak       Interrupt30
Interrupt30:
        .weak       Interrupt31
Interrupt31:
        .weak       Interrupt32
Interrupt32:
        .weak       Interrupt33
Interrupt33:
        .weak       Interrupt34
Interrupt34:
        .weak       Interrupt35
Interrupt35:
        .weak       Interrupt36
Interrupt36:
        .weak       Interrupt37
Interrupt37:
        .weak       Interrupt38
Interrupt38:
        .weak       Interrupt39
Interrupt39:
        .weak       Interrupt40
Interrupt40:
        .weak       Interrupt41
Interrupt41:
        .weak       Interrupt42
Interrupt42:
        .weak       Interrupt43
Interrupt43:
        .weak       Interrupt44
Interrupt44:
        .weak       Interrupt45
Interrupt45:
        .weak       Interrupt46
Interrupt46:
        .weak       Interrupt47
Interrupt47:
        .weak       Interrupt48
Interrupt48:
        .weak       Interrupt49
Interrupt49:
        .weak       Interrupt50
Interrupt50:
        .weak       Interrupt51
Interrupt51:
        .weak       Interrupt52
Interrupt52:
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
