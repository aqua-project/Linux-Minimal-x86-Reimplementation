#ifndef _ASM_SCORE_TRAPS_H
#define _ASM_SCORE_TRAPS_H

/* Interrupts/Exceptions */
enum {
	X86_TRAP_DE = 0,	/*  0, Divide-by-zero */
	X86_TRAP_DB,		/*  1, Debug */
	X86_TRAP_NMI,		/*  2, Non-maskable Interrupt */
	X86_TRAP_BP,		/*  3, Breakpoint */
	X86_TRAP_OF,		/*  4, Overflow */
	X86_TRAP_BR,		/*  5, Bound Range Exceeded */
	X86_TRAP_UD,		/*  6, Invalid Opcode */
	X86_TRAP_NM,		/*  7, Device Not Available */
	X86_TRAP_DF,		/*  8, Double Fault */
	X86_TRAP_OLD_MF,	/*  9, Coprocessor Segment Overrun */
	X86_TRAP_TS,		/* 10, Invalid TSS */
	X86_TRAP_NP,		/* 11, Segment Not Present */
	X86_TRAP_SS,		/* 12, Stack Segment Fault */
	X86_TRAP_GP,		/* 13, General Protection Fault */
	X86_TRAP_PF,		/* 14, Page Fault */
	X86_TRAP_SPURIOUS,	/* 15, Spurious Interrupt */
	X86_TRAP_MF,		/* 16, x87 Floating-Point Exception */
	X86_TRAP_AC,		/* 17, Alignment Check */
	X86_TRAP_MC,		/* 18, Machine Check */
	X86_TRAP_XF,		/* 19, SIMD Floating-Point Exception */
	X86_TRAP_IRET = 32,	/* 32, IRET Exception */
};

#define NR_VECTORS 256
#define SYSCALL_VECTOR 128

asmlinkage void divide_error(void);
asmlinkage void debug(void);
asmlinkage void nmi(void);
asmlinkage void int3(void);
asmlinkage void overflow(void);
asmlinkage void bounds(void);
asmlinkage void invalid_op(void);
asmlinkage void device_not_available(void);
asmlinkage void coprocessor_segment_overrun(void);
asmlinkage void invalid_TSS(void);
asmlinkage void segment_not_present(void);
asmlinkage void stack_segment(void);
asmlinkage void general_protection(void);
asmlinkage void page_fault(void);
asmlinkage void async_page_fault(void);
asmlinkage void spurious_interrupt_bug(void);
asmlinkage void coprocessor_error(void);
asmlinkage void alignment_check(void);
asmlinkage void machine_check(void);
asmlinkage void simd_coprocessor_error(void);

asmlinkage int system_call(void);

struct gate_desc{
  unsigned short offset0;
  unsigned short segment;
  unsigned short flags;
  unsigned short offset1;
} __attribute__((packed));

static void lidt(void);
void set_gate(int gate, void *addr, unsigned short segment,
              unsigned short flags);
void set_trap_gate(int gate, void *addr);
void set_system_gate(int gate, void *addr);

#endif /* _ASM_SCORE_TRAPS_H */
