# Makefile for Project 1 kernel patch
#
# NOTE: This system call is implemented as a kernel patch, not a loadable module.
# To build, copy my_virt_to_phys.c into the kernel source tree and rebuild.
#
# Steps:
#   1. Copy my_virt_to_phys.c to kernel/sys/ in the kernel source
#   2. Add `obj-y += my_virt_to_phys.o` to kernel/sys/Makefile
#   3. Register the syscall in include/linux/syscalls.h and arch/x86/entry/syscalls/syscall_64.tbl
#   4. make -j$(nproc)
#   5. make modules_install && make install

KERNEL_SRC ?= /usr/src/linux-source

.PHONY: help
help:
	@echo "This is a kernel patch — see steps above to build."
	@echo "Kernel source path: $(KERNEL_SRC)"
