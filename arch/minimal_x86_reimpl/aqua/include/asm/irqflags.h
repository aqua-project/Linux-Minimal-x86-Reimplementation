#ifndef _ASM_SCORE_IRQFLAGS_H
#define _ASM_SCORE_IRQFLAGS_H

#ifndef __ASSEMBLY__

#include <linux/types.h>

static inline unsigned long arch_local_save_flags(void)
{
    return 0;
}

static inline unsigned long arch_local_irq_save(void)
{
    return 0;
}

static inline void arch_local_irq_restore(unsigned long flags)
{
}

static inline void arch_local_irq_enable(void)
{
}

static inline void arch_local_irq_disable(void)
{
}

static inline bool arch_irqs_disabled_flags(unsigned long flags)
{
	return !(flags & 1);
}

static inline bool arch_irqs_disabled(void)
{
	return arch_irqs_disabled_flags(arch_local_save_flags());
}

#endif /* __ASSEMBLY__ */

#endif /* _ASM_SCORE_IRQFLAGS_H */
