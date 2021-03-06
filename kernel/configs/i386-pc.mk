#
# Compilation flags
#

INCLUDES := \
	-I. \
	-I$(PDIR)/arch/$$(ARCH_DIR)/platform/$$(PLATFORM_DIR)/include \
	-I$(PDIR)/arch/$$(ARCH_DIR)/include \
	-I$(PDIR)/include \
	-I$(PDIR)

CC := $(PDIR)/../build-tools/sysroot/bin/i686-elf-gcc
CFLAGS := $(INCLUDES) \
		-nostdlib -ffreestanding -m32 \
		-O3 -Wall -Wextra -Werror -funsigned-bitfields -fuse-ld=bfd \
		-Wno-unused -march=i386
AS := $(CC)
ASFLAGS := $(CFLAGS)
LD := $(PDIR)/../build-tools/sysroot/bin/i686-elf-ld.bfd
LDFLAGS := -nostdlib -melf_i386

#
# Configurations
#

ARCH=i386
ARCH_DIR=i386
ARCH_I386=y
ARCH_BITS=32

#
# Boot Definitions
#

X86_MULTIBOOT=y

#
# Platform - PC
#

PLATFORM_X86_PC=y
PLATFORM_DIR=pc
# Support 8259 PIC
PLATFORM_X86_MISC_PIC=y
# Support 8253/8254 PIT
PLATFORM_X86_MISC_PIT=y
# Support i8042 PS/2 Controller
PLATFORM_X86_MISC_I8042=y
# Support HPET
PLATFORM_X86_MISC_HPET=n
# Support ACPI
PLATFORM_X86_MISC_ACPI=y

#
# Devices
#

# Generic framebuffer (fbdev) support
DEV_FRAMEBUFFER=y
# Generic console (condev) support
DEV_CONSOLE=y
DEV_KEYBOARD=y
DEV_MOUSE=y
DEV_KEYBOARD_PS2=y
DEV_UART=y
DEV_PTY=y
DEV_MEMDEV=y
DEV_ATA=y
DEV_FDC=y

#
# Framebuffer
#

FBDEV_VESA=y

# Filesystems
FS_TMPFS=y
FS_DEVFS=y
FS_DEVPTS=y
FS_EXT2=y
FS_PROCFS=y
FS_MINIX=y

# Initramfs
INITRAMFS_CPIO=y
