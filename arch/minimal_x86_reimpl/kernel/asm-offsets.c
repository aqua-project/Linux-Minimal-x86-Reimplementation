/*
 * arch/score/kernel/asm-offsets.c
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

#include <linux/kbuild.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/ptrace.h>

int main(void)
{

	OFFSET(PT_EBX, pt_regs, bx);
	OFFSET(PT_ECX, pt_regs, cx);
	OFFSET(PT_EDX, pt_regs, dx);
	OFFSET(PT_ESI, pt_regs, si);
	OFFSET(PT_EDI, pt_regs, di);
	OFFSET(PT_EBP, pt_regs, bp);
	OFFSET(PT_EAX, pt_regs, ax);
	OFFSET(PT_DS, pt_regs, ds);
	OFFSET(PT_ES, pt_regs, es);
	OFFSET(PT_FS, pt_regs, fs);
	OFFSET(PT_GS, pt_regs, gs);
	OFFSET(PT_ORIG_EAX, pt_regs, orig_ax);
	OFFSET(PT_EIP, pt_regs, ip);
	OFFSET(PT_CS, pt_regs, cs);
	OFFSET(PT_EFLAGS, pt_regs, flags);
	OFFSET(PT_OLDSP, pt_regs, sp);
	OFFSET(PT_OLDSS, pt_regs, ss);

	OFFSET(TI_FLAGS, thread_info, flags);

	return 0;
}
