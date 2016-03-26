/*
 * arch/score/kernel/entry.S
 *
 * Score Processor version.
 *
 * Copyright (C) 2009 Sunplus Core Technology Co., Ltd.
 *  Chen Liqin <liqin.chen@sunplusct.com>
 *  Lennox Wu <lennox.wu@sunplusct.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see the file COPYING, or write
 * to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifdef CONFIG_PREEMPT
	.error "CONFIG_PREEMPT is not supported yet"
#endif

#include <linux/err.h>
#include <linux/init.h>
#include <linux/linkage.h>
#include <asm/asm-offsets.h>
#include <asm/asmmacro.h>
#include <asm/thread_info.h>
#include <asm/unistd.h>
#include <asm/segment.h>

.macro SAVE_ALL
	cld
	pushl %gs
	pushl %fs
	pushl %es
	pushl %ds
	pushl %eax
	pushl %ebp
	pushl %edi
	pushl %esi
	pushl %edx
	pushl %ecx
	pushl %ebx
.endm

.macro RESTORE_REGS
	cld
	popl %ebx
	popl %ecx
	popl %edx
	popl %esi
	popl %edi
	popl %ebp
	popl %eax
	popl %ds
	popl %es
	popl %fs
	popl %gs
.endm

/*
__INIT
ENTRY(debug_exception_vector)
	nop

ENTRY(general_exception_vector)			# should move to addr 0x200
	nop

ENTRY(interrupt_exception_vector)		# should move to addr 0x210
	nop

	.section ".text", "ax"
	.align	2;
general_exception:
	nop

interrupt_exception:
	nop


#ifndef CONFIG_PREEMPT
#define resume_kernel	restore_all
#else
#define __ret_from_irq	ret_from_exception
#endif

	.align	2
#ifndef CONFIG_PREEMPT

ENTRY(__ret_from_irq)
	nop

#endif

#ifdef CONFIG_PREEMPT
resume_kernel:
	nop
need_resched:
	nop
#endif
*/

ENTRY(ret_from_exception)
ENTRY(ret_from_irq)
	/* check the priviledge before exception */
	movl PT_CS(%esp), %eax
	andl $SEGMENT_RPL_MASK, %eax
	cmpl $USER_RPL, %eax
	jb restore_all

resume_userspace:
	cli
	/* check pending work to do before iret */
	GET_THREAD_INFO(%ebp)
	movl TI_FLAGS(%ebp), %ecx
	andl $_TIF_WORK_MASK, %ecx
	jne work_pending

restore_all:
	RESTORE_REGS
	iret

ENTRY(ret_from_kernel_thread)
	nop

ENTRY(ret_from_fork)
	nop

ENTRY(syscall_exit)
	nop

work_pending:
	testb $_TIF_NEED_RESCHED, %cl
	jz work_notifysig
work_resched:
	call schedule
	cli
	movl TI_FLAGS(%ebp), %ecx
	andl $_TIF_WORK_MASK, %ecx
	jz restore_all
	testb $_TIF_NEED_RESCHED, %cl
	jnz work_resched

work_notifysig:
	movl %esp, %eax
	sti
	movb PT_CS(%esp), %bl
	andb $SEGMENT_RPL_MASK, %bl
	cmpb $USER_RPL, %bl
	jb restore_all
	pushl %ecx
	pushl %eax
	call do_notify_resume
	popl %eax
	popl %eax
	jmp resume_userspace

/*
 * task_struct *resume(task_struct *prev, task_struct *next,
 *			struct thread_info *next_ti)
*/

ENTRY(resume)
	nop

/*
ENTRY(syscall_exit_work)
	nop

ENTRY(handle_sys)
	nop

syscall_return:
	nop

syscall_return_work:
	nop

syscall_trace_entry:
	nop

illegal_syscall:
	nop

*/

ENTRY(sys_rt_sigreturn)
	nop


ENTRY(divide_error)
	nop

ENTRY(debug)
	nop

ENTRY(nmi)
	nop

ENTRY(int3)
	nop

ENTRY(overflow)
	nop

ENTRY(bounds)
	nop

ENTRY(invalid_op)
	nop

ENTRY(device_not_available)
	nop

ENTRY(double_fault)
	nop

ENTRY(coprocessor_segment_overrun)
	nop

ENTRY(invalid_TSS)
	nop

ENTRY(segment_not_present)
	nop

ENTRY(stack_segment)
	nop

ENTRY(general_protection)
	nop

ENTRY(page_fault)
	SAVE_ALL
	movl %esp, %eax
	pushl PT_ORIG_EAX(%eax)     # error code
	pushl %eax                  # pt_regs pointer
	movl $-1, PT_ORIG_EAX(%eax) # no syscall
	call do_page_fault
	popl %eax                   # pop arguments
	popl %eax
	jmp ret_from_exception

ENTRY(spurious_interrupt_bug)
	nop

ENTRY(coprocessor_error)
	nop

ENTRY(alignment_check)
	nop

ENTRY(machine_check)
	nop

ENTRY(simd_coprocessor_error)
	nop

ENTRY(system_call)
	nop
