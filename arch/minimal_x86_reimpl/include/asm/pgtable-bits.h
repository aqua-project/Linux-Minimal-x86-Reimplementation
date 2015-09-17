#ifndef _ASM_MX86RI_PGTABLE_BITS_H
#define _ASM_MX86RI_PGTABLE_BITS_H

#define _PAGE_PRESENT  0x001
#define _PAGE_WRITABLE 0x002
#define _PAGE_USER     0x004
#define _PAGE_PWT      0x008   /* Write-Through */
#define _PAGE_PCD      0x010   /* No Cache */
#define _PAGE_ACCESSED 0x020
#define _PAGE_DIRTY    0x040
#define _PAGE_PSE      0x080   /* Large _Page */
#define _PAGE_GLOBAL   0x100

/* Set of bits not changed in pte_modify */
#define _PAGE_CHG_MASK	0xfff

#endif /* _ASM_MX86RI_PGTABLE_BITS_H */
