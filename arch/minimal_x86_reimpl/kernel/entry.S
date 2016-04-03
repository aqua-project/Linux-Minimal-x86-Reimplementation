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


.macro CALL_HANDLER handler
	SAVE_ALL
	movl %esp, %eax
	pushl PT_ORIG_EAX(%eax)     # error code
	pushl %eax                  # pt_regs pointer
	movl $-1, PT_ORIG_EAX(%eax) # no syscall
	call \handler
	popl %eax                   # pop arguments
	popl %eax
	jmp ret_from_exception
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
	CALL_HANDLER do_divide_error

ENTRY(debug)
	CALL_HANDLER do_debug

ENTRY(nmi)
	CALL_HANDLER do_nmi

ENTRY(int3)
	CALL_HANDLER do_int3

ENTRY(overflow)
	CALL_HANDLER do_overflow

ENTRY(bounds)
	CALL_HANDLER do_bounds

ENTRY(invalid_op)
	CALL_HANDLER do_invalid_op

ENTRY(device_not_available)
	CALL_HANDLER do_device_not_available

ENTRY(double_fault)
	CALL_HANDLER do_double_fault

ENTRY(coprocessor_segment_overrun)
	CALL_HANDLER do_coprocessor_segment_overrun

ENTRY(invalid_TSS)
	CALL_HANDLER do_invalid_TSS

ENTRY(segment_not_present)
	CALL_HANDLER do_segment_not_present

ENTRY(stack_segment)
	CALL_HANDLER do_stack_segment

ENTRY(general_protection)
	CALL_HANDLER do_general_protection

ENTRY(page_fault)
	CALL_HANDLER do_page_fault

ENTRY(spurious_interrupt_bug)
	CALL_HANDLER do_spurious_interrupt_bug

ENTRY(coprocessor_error)
	CALL_HANDLER do_coprocessor_error

ENTRY(alignment_check)
	CALL_HANDLER do_alignment_check

ENTRY(machine_check)
	CALL_HANDLER do_machine_check

ENTRY(simd_coprocessor_error)
	CALL_HANDLER do_simd_coprocessor_error

ENTRY(system_call)
	pushl %eax
	SAVE_ALL
	pushl %eax
	cmpl $(__NR_syscalls), %eax
	jae syscall_badsys
	call *sys_call_table(,%eax,4)
syscall_after_call:
	addl $4, %esp
	movl %eax, PT_EAX(%esp)
syscall_exit:
	cli
	GET_THREAD_INFO(%ebp)
	movl TI_FLAGS(%ebp), %ecx
	andl $_TIF_WORK_MASK, %ecx
	jnz work_pending
restore_all:
	RESTORE_REGS
	addl $4, %esp # remove error code
	iret

syscall_badsys:
	movl $-ENOSYS, %eax
	jmp syscall_after_call

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
	jnz work_pending
	jmp restore_all

ENTRY(ret_from_kernel_thread)
	nop

ENTRY(ret_from_fork)
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
	addl $8, %esp	# remove arguments
	jmp resume_userspace
