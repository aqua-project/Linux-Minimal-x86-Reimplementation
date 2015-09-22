#
# arch/score/Makefile
#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#

KBUILD_DEFCONFIG := spct6600_defconfig
CROSS_COMPILE :=

#
# CPU-dependent compiler/assembler options for optimization.
#
#cflags-y += -G0 -pipe -mel -mnhwloop -D__SCOREEL__ \
#	-D__linux__ -ffunction-sections -ffreestanding
cflags-y += -fno-builtin -m32

#
# Board-dependent options and extra files
#
KBUILD_AFLAGS += $(cflags-y)
KBUILD_CFLAGS += $(cflags-y)
KBUILD_AFLAGS_MODULE +=
KBUILD_CFLAGS_MODULE +=
LDFLAGS += -m elf_i386
LDFLAGS_vmlinux	+= -static -nostdlib

head-y := arch/aqua/kernel/head.o
libs-y += arch/aqua/lib/
core-y += arch/aqua/kernel/ arch/aqua/mm/

boot := arch/aqua/boot

vmlinux.bin: vmlinux
	$(Q)$(MAKE) $(build)=$(boot) $(boot)/$@

archclean:
	@$(MAKE) $(clean)=$(boot)

define archhelp
	echo '  vmlinux.bin          - Raw binary boot image'
	echo
	echo '  These will be default as appropriate for a configured platform.'
endef
