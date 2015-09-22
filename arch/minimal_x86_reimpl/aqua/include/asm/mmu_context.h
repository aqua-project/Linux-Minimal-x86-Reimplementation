#ifndef _ASM_SCORE_MMU_CONTEXT_H
#define _ASM_SCORE_MMU_CONTEXT_H

#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm-generic/mm_hooks.h>

#include <asm/cacheflush.h>
#include <asm/tlbflush.h>
#include <asm/scoreregs.h>

/*
 * For the fast tlb miss handlers, we keep a per cpu array of pointers
 * to the current pgd for each processor. Also, the proc. id is stuffed
 * into the context register.
 */
extern unsigned long asid_cache;
extern unsigned long pgd_current;


static inline void enter_lazy_tlb(struct mm_struct *mm,
				struct task_struct *tsk)
{}

static inline void
get_new_mmu_context(struct mm_struct *mm)
{
}

/*
 * Initialize the context related info for a new mm_struct
 * instance.
 */
static inline int
init_new_context(struct task_struct *tsk, struct mm_struct *mm)
{
	return 0;
}

static inline void switch_mm(struct mm_struct *prev, struct mm_struct *next,
			struct task_struct *tsk)
{
}

/*
 * Destroy context related info for an mm_struct that is about
 * to be put to rest.
 */
static inline void destroy_context(struct mm_struct *mm)
{}

static inline void
deactivate_mm(struct task_struct *task, struct mm_struct *mm)
{}

/*
 * After we have set current->mm to a new value, this activates
 * the context for the new mm so we see the new mappings.
 */
static inline void
activate_mm(struct mm_struct *prev, struct mm_struct *next)
{
}

#endif /* _ASM_SCORE_MMU_CONTEXT_H */
