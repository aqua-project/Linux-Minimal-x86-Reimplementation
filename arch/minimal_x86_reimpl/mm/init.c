/*
 * arch/score/mm/init.c
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

#include <linux/errno.h>
#include <linux/bootmem.h>
#include <linux/kernel.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/pagemap.h>
#include <linux/kcore.h>
#include <linux/sched.h>
#include <linux/initrd.h>

#include <asm/sections.h>
#include <asm/tlb.h>

void __init init_page(pgd_t pgd[], unsigned long va, unsigned long pa, pgprot_t prot)
{
	pmd_t *pmd;
	pte_t *pte;

	pmd = pmd_offset(pud_offset(pgd, va), va);
	if (pmd_none(*pmd)) {
		pte_t *page_table = (pte_t*) alloc_bootmem(PAGE_SIZE);
		memset(page_table, 0, PAGE_SIZE);
		set_pmd(pmd, __pmd(__pa(page_table) | pgprot_val(PAGE_USER)));
	}
	pte = pte_offset_kernel(pmd, va);
	set_pte(pte, __pte(pa | pgprot_val(prot)));
}

void __init init_pages(pgd_t pgd[], unsigned long start_base, unsigned long end, unsigned long pa_base, pgprot_t prot)
{
	BUG_ON(!PAGE_ALIGNED(start_base));
	BUG_ON(!PAGE_ALIGNED(end));

	while (start_base <= end) {
		init_page(pgd, start_base, pa_base, prot);
		start_base += PAGE_SIZE;
		pa_base += PAGE_SIZE;
	}
}

void __init pagetable_init(void)
{
	init_pages(swapper_pg_dir, PAGE_OFFSET, __va(max_low_pfn << PAGE_SHIFT), 0, PAGE_KERNEL);
}

#ifdef CONFIG_BLK_DEV_INITRD
void free_initrd_mem(unsigned long start, unsigned long end)
{
	free_reserved_area((void *)start, (void *)end, POISON_FREE_INITMEM,
			   "initrd");
}
#endif

void __init_refok free_initmem(void)
{
	free_initmem_default(POISON_FREE_INITMEM);
}

unsigned long pgd_current;

void __init mem_init(void)
{
	high_memory = (void *) __va(max_low_pfn << PAGE_SHIFT) + 1;
	free_all_bootmem();
	mem_init_print_info(NULL);
}
