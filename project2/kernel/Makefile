# Makefile for Project 2 kernel patch
#
# NOTE: This system call is implemented as a kernel patch, not a loadable module.
#
# Steps:
#   1. Copy my_thread_info.c to kernel/sys/ in the kernel source
#   2. Add `obj-y += my_thread_info.o` to kernel/sys/Makefile
#   3. Add the syscall declaration to include/linux/syscalls.h
#   4. Register in arch/x86/entry/syscalls/syscall_64.tbl
#   5. make -j$(nproc)
#   6. make modules_install && make install

KERNEL_SRC ?= /usr/src/linux-source

.PHONY: help
help:
	@echo "This is a kernel patch — see steps above to build."
	@echo "Kernel source path: $(KERNEL_SRC)"
