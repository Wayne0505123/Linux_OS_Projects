# Project 2 — Kernel Thread Information System Call

## Overview

Implemented a custom Linux kernel system call `my_get_thread_kernel_info()` that retrieves kernel-level information of a running thread, including process descriptors, stack addresses, and page table locations.

## Implementation

### Kernel Side (`kernel/`)

- Added `my_get_thread_kernel_info()` system call to the Linux kernel
- Accesses `task_struct` to extract thread-level kernel data
- Uses `copy_to_user()` to safely transfer data to user space

### User Space (`userspace/`)

- Single-threaded program to invoke the system call and display results
- Multi-threaded program using **POSIX threads (pthreads)** to compare kernel info across multiple threads within the same process

## Retrieved Information

| Field | Description |
|-------|-------------|
| PID | Process ID |
| TGID | Thread Group ID |
| `task_struct` address | Kernel process descriptor location |
| Kernel stack address | Location of the kernel-mode stack |
| PGD address | Page Global Directory address |

## Key Concepts

| Concept | Description |
|---------|-------------|
| task_struct | Kernel data structure representing a process/thread |
| copy_to_user() | Safe data transfer from kernel space to user space |
| pthreads | POSIX thread library for multi-threading |
| TGID vs PID | Threads share TGID, each has unique PID in kernel |

## Usage

```bash
# Build kernel module / patch kernel
cd kernel/
make

# Run single-threaded test
cd userspace/
gcc -o test test.c
./test

# Run multi-threaded test
gcc -o test_mt test_mt.c -lpthread
./test_mt
```

## Report

Full implementation details: [HackMD Report](https://hackmd.io/FVMoGPudTxic6vRY3pya0w)
