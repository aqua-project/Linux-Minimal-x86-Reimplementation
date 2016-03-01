#ifndef _ASM_MINIMAL_X86_REIMPL_IO_H
#define _ASM_MINIMAL_X86_REIMPL_IO_H

#define __raw_readb __raw_readb
static inline u8 __raw_readb(const volatile void __iomem *addr)
{
	u8 value;
	asm volatile("inb %w1, %b0"
		     : "=a"(value) : "Nd"(addr));
	return value;
}

#define __raw_readw __raw_readw
static inline u16 __raw_readw(const volatile void __iomem *addr)
{
	u16 value;
	asm volatile("inw %w1, %w0"
		     : "=a"(value) : "Nd"(addr));
	return value;
}

#define __raw_readl __raw_readl
static inline u32 __raw_readl(const volatile void __iomem *addr)
{
	u32 value;
	asm volatile("inl %w1, %0"
		     : "=a"(value) : "Nd"(addr));
	return value;
}

#define __raw_writeb __raw_writeb
static inline void __raw_writeb(u8 value, volatile void __iomem *addr)
{
	asm volatile("outb %b0, %w1"
		     : : "a"(value), "Nd"(addr));
}

#define __raw_writew __raw_writew
static inline void __raw_writew(u16 value, volatile void __iomem *addr)
{
	asm volatile("outw %w0, %w1"
		     : : "a"(value), "Nd"(addr));
}

#define __raw_writel __raw_writel
static inline void __raw_writel(u32 value, volatile void __iomem *addr)
{
	asm volatile("outl %0, %w1"
		     : : "a"(value), "Nd"(addr));
}

#include <asm-generic/io.h>

#define virt_to_bus	virt_to_phys
#define bus_to_virt	phys_to_virt
#endif /* _ASM_MINIMAL_X86_REIMPL_IO_H */
