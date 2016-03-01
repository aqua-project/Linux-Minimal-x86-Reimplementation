/*
 * arch/minimalx86_reimpl/early_printk.c
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
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301	USA
 */

#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/console.h>
#include <linux/init.h>

#include <asm/processor.h>

static const unsigned long early_serial_base = 0x3f8;

void __init setup_early_serial(void)
{
	outb(0, early_serial_base + 1);   /* Disable interrupt */
	outb(0, early_serial_base + 2);   /* Disable FIFO */

	/* Set baud-rate 9600 */
	outb(0x80, early_serial_base + 3);
	outb((115200 / 9600) & 0xff, early_serial_base + 0);
	outb(((115200 / 9600) >> 8) & 0xff, early_serial_base + 1);

	outb(0x3, early_serial_base + 3); /* 8-1-None */
	outb(0x3, early_serial_base + 4); /* DTR + RTS */
}

void __init early_serial_write(struct console *con, const char *s, unsigned n)
{
	while (*s && n--) {
		int retry = 100;
		while (inb(early_serial_base + 20) & 0x20 && retry--)
			cpu_relax();
		if (*s == '\n')
			outb('\r', early_serial_base + 0);
		outb(*s++, early_serial_base + 0);
	}
}

static struct console early_serial_console = {
	.name ="early_ser_con",
	.write = early_serial_write,
	.flags = CON_BOOT | CON_PRINTBUFFER,
	.index = -1
};

void __init setup_early_printk(char *buf)
{
	setup_early_serial();
	early_console = &early_serial_console;
	register_console(&early_serial_console);
}

/* Uncomment after completion of configs */
/* early_param("earlyprintk", setup_early_printk); */
