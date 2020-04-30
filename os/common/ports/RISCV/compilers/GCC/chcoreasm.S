/*
    ChibiOS - Copyright (C) 2020 Patrick Seidel.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    compilers/GCC/chcoreasm.S
 * @brief   RISC-V architecture port low level code.
 *
 * @addtogroup RISCV_GCC_CORE
 * @{
 */

#if !defined(FALSE) || defined(__DOXYGEN__)
#define FALSE   0
#endif

#if !defined(TRUE) || defined(__DOXYGEN__)
#define TRUE    1
#endif

#define _FROM_ASM_
#include "chlicense.h"
#include "chconf.h"
#include "chcore.h"

#if !defined(__DOXYGEN__)

/*
 * RTOS-specific context offset.
 */
#if defined(_CHIBIOS_RT_CONF_)
#define CONTEXT_OFFSET  12
#elif defined(_CHIBIOS_NIL_CONF_)
#define CONTEXT_OFFSET  0
#else
#error "invalid chconf.h"
#endif

                .text
                .globl  TrapEnter
TrapEnter:
                addi    sp, sp, -80

                sw      a0, 0(sp)
                sw      a1, 4(sp)
                sw      a2, 8(sp)
                sw      a3, 12(sp)
                sw      a4, 16(sp)
                sw      a5, 20(sp)
                sw      a6, 24(sp)
                sw      a7, 28(sp)
                sw      t0, 32(sp)
                sw      t1, 36(sp)
                sw      t2, 40(sp)
                sw      t3, 44(sp)
                sw      t4, 48(sp)
                sw      t5, 52(sp)
                sw      t6, 56(sp)
                sw      ra, 60(sp)
                // Delay population of PC.

                // Determine if this is an exception or an interrupt.
                // Load the corresponding table.
                csrr    a1, mcause
                slli    a0, a1, 2
                la      a2, ExceptionTable
                bgeu    a0, a1, _trapExecuteM
                la      a2, VectorTable

_trapExecuteM:
                add     a2, a0, a2
                lw      a0, 0(a2)
                jalr    ra, a0
                beq     a0, zero, _port_exit_from_isr

_trapSwitchM:
                // A reschedule is necessary.
                // Save the PC now.
                csrr    a0, mepc
                sw      a0, 64(sp)

                // Prevent re-enabling interrupts by clearing MPIE.
                li      a0, 0x80
                csrc    mstatus, a0

                // Set MEPC to a function that will perform the switch after the interrupt.
                la      a0, _port_switch_from_isr
                csrw    mepc, a0

                mret

/*--------------------------------------------------------------------------*
 * Performs a context switch between two threads.
 * a0 = ntp, a1 = otp
 *--------------------------------------------------------------------------*/
                .globl  _port_switch
_port_switch:
                // This uses a trick of not updating the stack pointer.
                // This saves 2 instructions, but misses out on
                // some compressed instructions while doing so.
                // On the FE310, this improves the benchmarks even
                // with the inflated code size.
                sw      ra, -52(sp)
                sw      s0, -48(sp)
                sw      s1, -44(sp)
                sw      s2, -40(sp)
                sw      s3, -36(sp)
                sw      s4, -32(sp)
                sw      s5, -28(sp)
                sw      s6, -24(sp)
                sw      s7, -20(sp)
                sw      s8, -16(sp)
                sw      s9, -12(sp)
                sw      s10, -8(sp)
                sw      s11, -4(sp)

                sw      sp, CONTEXT_OFFSET(a1)
                lw      sp, CONTEXT_OFFSET(a0)

                lw      ra, -52(sp)
                lw      s0, -48(sp)
                lw      s1, -44(sp)
                lw      s2, -40(sp)
                lw      s3, -36(sp)
                lw      s4, -32(sp)
                lw      s5, -28(sp)
                lw      s6, -24(sp)
                lw      s7, -20(sp)
                lw      s8, -16(sp)
                lw      s9, -12(sp)
                lw      s10, -8(sp)
                lw      s11, -4(sp)

                ret

/*--------------------------------------------------------------------------*
 * Start a thread by invoking its work function.
 *
 * Threads execution starts here, the code leaves the system critical zone
 * and then jumps into the thread function passed in register S0. The
 * register S1 contains the thread parameter. The function chThdExit() is
 * called on thread function return.
 *--------------------------------------------------------------------------*/
                .globl  _port_thread_start
_port_thread_start:
#if CH_DBG_SYSTEM_STATE_CHECK
                jal     ra, _dbg_check_unlock
#endif
#if CH_DBG_STATISTICS
                jal     ra, _stats_stop_measure_crit_thd
#endif

                csrsi   mstatus, 0x8
                mv      a0, s1
                jalr    ra, s0
                li      a0, 0              /* MSG_OK */
                jal     ra, chThdExit
_zombies:       j       _zombies

/*--------------------------------------------------------------------------*
 * Post-IRQ switch code.
 *
 * Exception handlers return here for context switching.
 *--------------------------------------------------------------------------*/

_port_switch_from_isr:
#if CH_DBG_STATISTICS
                jal     ra, _stats_start_measure_crit_thd
#endif
#if CH_DBG_SYSTEM_STATE_CHECK
                jal     ra, _dbg_check_lock
#endif
                jal     ra, chSchDoReschedule
#if CH_DBG_SYSTEM_STATE_CHECK
                jal     ra, _dbg_check_unlock
#endif
#if CH_DBG_STATISTICS
                jal     ra, _stats_stop_measure_crit_thd
#endif

                // Load the preempted pc into mepc.
                lw      a0, 64(sp)
                csrw    mepc, a0

_port_exit_from_isr:
                // Defer-enable interrupts using mpie with mret.
                // Also orce mpp to M-Mode (empirically determined to be 3).
                li      a0, 0x1880
                csrs    mstatus, a0

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

                addi    sp, sp, 80
                mret

/*--------------------------------------------------------------------------*
 * External interrupt handling code.
 *
 * This is the core external (peripheral) interrupt handler with
 * claim / complete functionality.
 *--------------------------------------------------------------------------*/

.equ            PLIC_CLAIM_COMPLETE, 0x0C200004

                .globl VectorMEI
VectorMEI:
                // Create stack space.
                addi    sp, sp, -16

                // Save RA.
                sw      ra, 0(sp)

                // Claim an interrupt.
                li      a1, PLIC_CLAIM_COMPLETE
                lw      a2, 0(a1)

                // Default to completed with no preemption required.
                li      a0, 0

                // Zero is valid and means no interrupt claimed, just return.
                beq     zero, a2, _VectorMEIRet

_handleInterrupt:
                // Index into the interrupt table.
                la      a3, InterruptTable
                slli    a4, a2, 2
                add     a5, a3, a4
                lw      a6, 0(a5)

                // Save the claim address and id.
                sw      a1, 4(sp)
                sw      a2, 8(sp)

                // Jump into the interurpt handler.
                jalr    ra, a6

                // Load the claim address and id.
                lw      a1, 4(sp)
                lw      a2, 8(sp)

                // Mark the interrupt as complete and return.
                // The handler populated the return variable already.
                sw      a2, 0(a1)

_VectorMEIRet:
                // Load RA.
                lw      ra, 0(sp)

                // Free stack space
                addi    sp, sp, 16
                ret


#endif /* !defined(__DOXYGEN__) */

/** @} */
