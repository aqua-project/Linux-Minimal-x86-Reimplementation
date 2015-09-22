/*
 * arch/score/kernel/module.c
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

#include <linux/moduleloader.h>
#include <linux/module.h>
#include <linux/vmalloc.h>

int apply_relocate(Elf_Shdr *sechdrs, const char *strtab,
		unsigned int symindex, unsigned int relindex,
		struct module *me)
{
	return 0;
}

/* Given an address, look for it in the module exception tables. */
const struct exception_table_entry *search_module_dbetables(unsigned long addr)
{
	return NULL;
}
