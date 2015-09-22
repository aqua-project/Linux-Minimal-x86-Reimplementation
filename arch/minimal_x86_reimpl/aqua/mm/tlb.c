/*
 * arch/score/mm/tlb-score.c
 *
 * Score Processor version.
 *
 * Copyright (C) 2009 Sunplus Core Technology Co., Ltd.
 *  Lennox Wu <lennox.wu@sunplusct.com>
 *  Chen Liqin <liqin.chen@sunplusct.com>
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

#include <linux/highmem.h>
#include <linux/module.h>

#include <asm/irq.h>
#include <asm/mmu_context.h>
#include <asm/tlb.h>

void flush_tlb_all(void)
{
}

/*
 * If mm is currently active_mm, we can't really drop it. Instead,
 * we will get a new one for it.
 */
static inline void
drop_mmu_context(struct mm_struct *mm)
{
}

void flush_tlb_mm(struct mm_struct *mm)
{
}

void flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
	unsigned long end)
{
}


void flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
}

/*
 * This one is only used for pages with the global bit set so we don't care
 * much about the ASID.
 */
void flush_tlb_one(unsigned long page)
{
}

void __update_tlb(struct vm_area_struct *vma, unsigned long address, pte_t pte)
{
}

void tlb_init(void)
{
}
