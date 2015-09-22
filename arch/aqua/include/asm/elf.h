#ifndef _ASM_SCORE_ELF_H
#define _ASM_SCORE_ELF_H

#include <linux/ptrace.h>

#define EM_SCORE7	135

/* Relocation types. */
#define R_SCORE_NONE		0
#define R_SCORE_HI16		1
#define R_SCORE_LO16		2
#define R_SCORE_BCMP		3
#define R_SCORE_24		4
#define R_SCORE_PC19		5
#define R_SCORE16_11		6
#define R_SCORE16_PC8		7
#define R_SCORE_ABS32		8
#define R_SCORE_ABS16		9
#define R_SCORE_DUMMY2		10
#define R_SCORE_GP15		11
#define R_SCORE_GNU_VTINHERIT	12
#define R_SCORE_GNU_VTENTRY	13
#define R_SCORE_GOT15		14
#define R_SCORE_GOT_LO16	15
#define R_SCORE_CALL15		16
#define R_SCORE_GPREL32		17
#define R_SCORE_REL32		18
#define R_SCORE_DUMMY_HI16	19
#define R_SCORE_IMM30		20
#define R_SCORE_IMM32		21

/* ELF register definitions */
typedef unsigned long	elf_greg_t;

#define ELF_NGREG	(sizeof(struct pt_regs) / sizeof(elf_greg_t))
typedef elf_greg_t	elf_gregset_t[ELF_NGREG];

/* Score does not have fp regs. */
typedef double		elf_fpreg_t;
typedef elf_fpreg_t	elf_fpregset_t;

#define elf_check_arch(x)	((x)->e_machine == EM_SCORE7)

/*
 * These are used to set parameters in the core dumps.
 */
#define ELF_CLASS	ELFCLASS32

/*
 * These are used to set parameters in the core dumps.
 */
#define ELF_DATA	ELFDATA2LSB
#define ELF_ARCH	EM_SCORE7

struct task_struct;
struct pt_regs;

#define CORE_DUMP_USE_REGSET
#define ELF_EXEC_PAGESIZE	PAGE_SIZE

/* This yields a mask that user programs can use to figure out what
   instruction set this cpu supports.  This could be done in userspace,
   but it's not easy, and we've already done it here.  */

#define ELF_HWCAP	(0)

/* This yields a string that ld.so will use to load implementation
   specific libraries for optimization.  This is more specific in
   intent than poking at uname or /proc/cpuinfo.

   For the moment, we have only optimizations for the Intel generations,
   but that could change... */

#define ELF_PLATFORM	(NULL)

#define ELF_PLAT_INIT(_r, load_addr)	do {} while (0)

/* This is the location that an ET_DYN program is loaded if exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room for the brk.  */

#ifndef ELF_ET_DYN_BASE
#define ELF_ET_DYN_BASE		(TASK_SIZE / 3 * 2)
#endif

#endif /* _ASM_SCORE_ELF_H */
