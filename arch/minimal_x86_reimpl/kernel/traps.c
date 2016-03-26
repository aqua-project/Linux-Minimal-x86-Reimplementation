/*
 * arch/score/kernel/traps.c
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
#include <linux/sched.h>

#include <asm/cacheflush.h>
#include <asm/irq.h>
#include <asm/irq_regs.h>
#include <asm/traps.h>

struct gate_desc idt_table[NR_VECTORS];

void show_stack(struct task_struct *task, unsigned long *sp)
{
}

void show_regs(struct pt_regs *regs)
{
}

static void show_registers(struct pt_regs *regs)
{
}

void __die(const char *str, struct pt_regs *regs, const char *file,
	const char *func, unsigned long line)
{
}

void __die_if_kernel(const char *str, struct pt_regs *regs,
		const char *file, const char *func, unsigned long line)
{
}

void __init trap_init(void)
{
	set_trap_gate(X86_TRAP_DE,  divide_error);
	set_trap_gate(X86_TRAP_DB,  debug);
	set_trap_gate(X86_TRAP_NMI, nmi);
	set_trap_gate(X86_TRAP_BP,  int3);
	set_trap_gate(X86_TRAP_OF, overflow);
	set_trap_gate(X86_TRAP_BR, bounds);
	set_trap_gate(X86_TRAP_UD, invalid_op);
	set_trap_gate(X86_TRAP_NM, device_not_available);
	//  set_trap_gate(X86_TRAP_DF, double_fault);
	set_trap_gate(X86_TRAP_OLD_MF, coprocessor_segment_overrun);
	set_trap_gate(X86_TRAP_TS, invalid_TSS);
	set_trap_gate(X86_TRAP_NP, segment_not_present);
	set_trap_gate(X86_TRAP_SS, stack_segment);
	set_trap_gate(X86_TRAP_GP, general_protection);
	set_trap_gate(X86_TRAP_PF, page_fault);
	set_trap_gate(X86_TRAP_SPURIOUS, spurious_interrupt_bug);
	set_trap_gate(X86_TRAP_MF, coprocessor_error);
	set_trap_gate(X86_TRAP_AC, alignment_check);
	set_trap_gate(X86_TRAP_MC, machine_check);
	set_trap_gate(X86_TRAP_XF, simd_coprocessor_error);

	set_trap_gate(SYSCALL_VECTOR, system_call);

	lidt();
}

static void lidt(void){
	volatile unsigned short pd[3];

	pd[0] = sizeof(idt_table);
	pd[1] = (unsigned short)((int)idt_table & 0xffff);
	pd[2] = (unsigned short)((int)idt_table >> 16);

	asm volatile("lidt (%0)" : : "r" (pd));
}

void set_gate(int gate, void *addr, unsigned short segment,
	      unsigned short flags){
	struct gate_desc *gd = &(idt_table[gate]);
	gd->offset0 = (unsigned short)((int)addr & 0xffff);
	gd->offset1 = (unsigned short)((int)addr >> 16);
	gd->segment = (unsigned short)segment; //kernel code segment
	gd->flags   = (unsigned short)flags;
}

void set_trap_gate(int gate, void *addr){
	set_gate(gate, addr, 0x60, 0x8f00);
}

void set_system_gate(int gate, void *addr){
	set_gate(gate, addr, 0x60, 0xef00);
}
