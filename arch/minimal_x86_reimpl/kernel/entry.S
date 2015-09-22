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

#include <linux/err.h>
#include <linux/init.h>
#include <linux/linkage.h>

#include <asm/asmmacro.h>
#include <asm/thread_info.h>
#include <asm/unistd.h>

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
ENTRY(ret_from_exception)
	nop

ENTRY(ret_from_irq)
	nop

ENTRY(__ret_from_irq)
	nop

resume_userspace:
	nop
#endif

#ifdef CONFIG_PREEMPT
resume_kernel:
	nop
need_resched:
	nop
#endif

ENTRY(ret_from_kernel_thread)
	nop

ENTRY(ret_from_fork)
	nop

ENTRY(syscall_exit)
	nop

ENTRY(restore_all)					# restore full frame
	nop

work_pending:
	nop
work_resched:
	nop

work_notifysig:
	nop

ENTRY(syscall_exit_work)
	nop

/*
 * task_struct *resume(task_struct *prev, task_struct *next,
 *			struct thread_info *next_ti)
 */
ENTRY(resume)
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

ENTRY(sys_rt_sigreturn)
	nop
