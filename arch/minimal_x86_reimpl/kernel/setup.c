/*
 * arch/aqua/kernel/setup.c
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

#include <linux/bootmem.h>
#include <linux/initrd.h>
#include <linux/ioport.h>
#include <linux/memblock.h>
#include <linux/mm.h>
#include <linux/seq_file.h>
#include <linux/screen_info.h>

#include <asm-generic/sections.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/mmu.h>
#include <asm/setup.h>

struct thread_info *__current_thread_info;

struct screen_info screen_info;
unsigned long kernelsp;

void __init bootmem_init(void)
{
	unsigned long start_pfn, bootmap_size;
	unsigned long size = initrd_end - initrd_start;

	start_pfn = PFN_UP(__pa(&_end));

	min_low_pfn = PFN_UP(MEMORY_START);
	max_low_pfn = PFN_UP(MEMORY_START + MEMORY_SIZE);
	max_mapnr = max_low_pfn - min_low_pfn;

	/* Initialize the boot-time allocator with low memory only. */
	bootmap_size = init_bootmem_node(NODE_DATA(0), start_pfn,
					 min_low_pfn, max_low_pfn);
	memblock_add_node(PFN_PHYS(min_low_pfn),
			  PFN_PHYS(max_low_pfn - min_low_pfn), 0);

	free_bootmem(PFN_PHYS(start_pfn),
		     (max_low_pfn - start_pfn) << PAGE_SHIFT);
	memory_present(0, start_pfn, max_low_pfn);

	/* Reserve space for the bootmem bitmap. */
	reserve_bootmem(PFN_PHYS(start_pfn), bootmap_size, BOOTMEM_DEFAULT);

	if (size == 0) {
		printk(KERN_INFO "Initrd not found or empty");
		goto disable;
	}

	if (__pa(initrd_end) > PFN_PHYS(max_low_pfn)) {
		printk(KERN_ERR "Initrd extends beyond end of memory");
		goto disable;
	}

	/* Reserve space for the initrd bitmap. */
	reserve_bootmem(__pa(initrd_start), size, BOOTMEM_DEFAULT);
	initrd_below_start_ok = 1;

	pr_info("Initial ramdisk at: 0x%lx (%lu bytes)\n",
		 initrd_start, size);
	return;
disable:
	printk(KERN_CONT " - disabling initrd\n");
	initrd_start = 0;
	initrd_end = 0;
}

void __init setup_arch(char **cmdline_p)
{
        bootmem_init();
        pagetable_init();
}

static int show_cpuinfo(struct seq_file *m, void *v)
{
	return 0;
}

static void *c_start(struct seq_file *m, loff_t *pos)
{
	return NULL;
}

static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
	return NULL;
}

static void c_stop(struct seq_file *m, void *v)
{
}

const struct seq_operations cpuinfo_op = {
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};

__attribute__((__aligned__(PAGE_SIZE)))
uint32_t entrypgdir[1024] = {
  // Map VA's [0, 4MB) to PA's [0, 4MB)
  [0] = (0) | PTE_P | PTE_W | PTE_PS,
  // Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
  [KERNBASE>>PGDIR_SHIFT] = (0) | PTE_P | PTE_W | PTE_PS,
};
