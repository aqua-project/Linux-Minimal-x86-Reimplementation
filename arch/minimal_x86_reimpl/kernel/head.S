/*
 * arch/aqua/kernel/head.S
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
#include <linux/init.h>
#include <linux/linkage.h>
#include <asm/page.h>
#include <asm/mmu.h>
#include <asm/thread_info.h>

#include <asm/asm-offsets.h>

	.extern start_kernel
	.global init_thread_union
	.global	kernelsp
.p2align 2
.text
.globl multiboot_header
multiboot_header:
  #define magic 0x1badb002
  #define flags 0
  .long magic
  .long flags
  .long (-magic-flags)


.globl _start
_start = pa(entry)

__INIT
ENTRY(entry)
    # Turn on page size extension for 4Mbyte pages
    movl    %cr4, %eax
    orl     $(CR4_PSE), %eax
    movl    %eax, %cr4
    # Set page directory
    movl    $(pa(entrypgdir)), %eax
    movl    %eax, %cr3
    # Turn on paging.
    movl    %cr0, %eax
    orl     $(CR0_PG|CR0_WP), %eax
    movl    %eax, %cr0

    # Set up the stack pointer.
    movl    $init_thread_union, %esp
    addl    $(THREAD_SIZE), %esp
    movl    $__current_thread_info, %eax
    movl    $init_thread_union, 0(%eax)

    movl    $start_kernel, %eax
    jmp     %eax


__PAGE_ALIGNED_BSS
        .align PAGE_SIZE
ENTRY(empty_zero_page)
	.fill 4096,1,0
ENTRY(swapper_pg_dir)
	.fill 1024,4,0
