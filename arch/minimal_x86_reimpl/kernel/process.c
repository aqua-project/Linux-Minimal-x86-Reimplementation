/*
 * arch/score/kernel/process.c
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

#include <linux/module.h>
#include <linux/reboot.h>
#include <linux/elfcore.h>
#include <linux/pm.h>
#include <linux/rcupdate.h>

void (*pm_power_off)(void);
EXPORT_SYMBOL(pm_power_off);

/* If or when software machine-restart is implemented, add code here. */
void machine_restart(char *command) {}

/* If or when software machine-halt is implemented, add code here. */
void machine_halt(void) {}

/* If or when software machine-power-off is implemented, add code here. */
void machine_power_off(void) {}

void ret_from_fork(void);
void ret_from_kernel_thread(void);

void start_thread(struct pt_regs *regs, unsigned long pc, unsigned long sp)
{
}

void exit_thread(void) {}

/*
 * When a process does an "exec", machine state like FPU and debug
 * registers need to be reset.  This is a hook function for that.
 * Currently we don't have any such state to reset, so this is empty.
 */
void flush_thread(void) {}

/*
 * set up the kernel stack and exception frames for a new process
 */
int copy_thread(unsigned long clone_flags, unsigned long usp,
		unsigned long arg, struct task_struct *p)
{
}

/* Fill in the fpu structure for a core dump. */
int dump_fpu(struct pt_regs *regs, elf_fpregset_t *r)
{
	return 1;
}

unsigned long thread_saved_pc(struct task_struct *tsk)
{
	return task_pt_regs(tsk)->cp0_epc;
}

unsigned long get_wchan(struct task_struct *task)
{
	return 0;
}

unsigned long arch_align_stack(unsigned long sp)
{
	return sp;
}
