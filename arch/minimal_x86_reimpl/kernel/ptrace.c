/*
 * arch/score/kernel/ptrace.c
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

#include <linux/elf.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/ptrace.h>
#include <linux/regset.h>

#include <asm/uaccess.h>

/*
 * retrieve the contents of SCORE userspace general registers
 */
static int genregs_get(struct task_struct *target,
		       const struct user_regset *regset,
		       unsigned int pos, unsigned int count,
		       void *kbuf, void __user *ubuf)
{
	return 0;
}

/*
 * update the contents of the SCORE userspace general registers
 */
static int genregs_set(struct task_struct *target,
		       const struct user_regset *regset,
		       unsigned int pos, unsigned int count,
		       const void *kbuf, const void __user *ubuf)
{
	return 0;
}

/*
 * Define the register sets available on the score7 under Linux
 */
enum score7_regset {
	REGSET_GENERAL,
};

static const struct user_regset score7_regsets[] = {
	[REGSET_GENERAL] = {
		.core_note_type	= NT_PRSTATUS,
		.n		= ELF_NGREG,
		.size		= sizeof(long),
		.align		= sizeof(long),
		.get		= genregs_get,
		.set		= genregs_set,
	},
};

static const struct user_regset_view user_score_native_view = {
	.name		= "score7",
	.e_machine	= EM_SCORE7,
	.regsets	= score7_regsets,
	.n		= ARRAY_SIZE(score7_regsets),
};

const struct user_regset_view *task_user_regset_view(struct task_struct *task)
{
	return &user_score_native_view;
}


void user_enable_single_step(struct task_struct *child)
{
}

void user_disable_single_step(struct task_struct *child)
{
}

void ptrace_disable(struct task_struct *child)
{
}

long
arch_ptrace(struct task_struct *child, long request,
	    unsigned long addr, unsigned long data)
{
}

/*
 * Notification of system call entry/exit
 * - triggered by current->work.syscall_trace
 */
asmlinkage void do_syscall_trace(struct pt_regs *regs, int entryexit)
{
}
