# Project 1 — Virtual Memory Translation System Call

## Overview

Implemented a custom Linux system call that translates a virtual address to its corresponding physical address by traversing the kernel's multi-level page tables.

## Implementation

### Kernel Side (`kernel/`)

- Added a new system call to the Linux kernel
- Traverses the page table hierarchy: **PGD → PUD → PMD → PTE**
- Extracts the physical page frame number (PFN) and computes the physical address

### User Space (`userspace/`)

- **C program**: directly invokes the system call via `syscall()`
- **Python program**: uses `ctypes` and a shared library to invoke the system call from Python
- Tests for lazy page allocation and heap growth behavior

## Key Concepts

| Concept | Description |
|---------|-------------|
| Page Table Walk | PGD → PUD → PMD → PTE traversal |
| Lazy Allocation | Pages are allocated on first access, not on `malloc()` |
| Physical Address | PFN × PAGE_SIZE + offset |
| ctypes | Python library for calling C functions / system calls |

## Usage

```bash
# Build kernel module / patch kernel
cd kernel/
make

# Run user-space test (C)
cd userspace/
gcc -o test test.c
./test

# Run user-space test (Python)
python3 test.py
```

## Report

Full implementation details: [HackMD Report](https://hackmd.io/S01ADCVPQpmNljruzel_og)
