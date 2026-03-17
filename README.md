# Linux OS Projects

> Academic projects for the Linux Operating System course at National Central University (NCU).
>
> Course: [Linux OS — Fall 2025](https://staff.csie.ncu.edu.tw/hsufh/COURSES/FALL2025/linuxos.html)

---

## Projects

### Project 1 — Virtual Memory Translation System Call

Implemented a custom Linux system call to translate virtual addresses to physical addresses by traversing kernel page tables.

**Key Topics:** Kernel development · Virtual memory · Page table traversal · ctypes

| | |
|---|---|
| Report | [Project1 Report](https://hackmd.io/S01ADCVPQpmNljruzel_og) |
| Description | [Project1_Description](https://hackmd.io/@Yan-Hao-Wang/Hy2YW9jple) |
| Source | [`project1`](./project1/) |

**Highlights:**
- Custom system call that walks kernel page tables (PGD → PUD → PMD → PTE)
- User-space C and Python programs to test lazy page allocation and heap growth
- Python `ctypes` bridge to invoke kernel-level functionality

---

### Project 2 — Kernel Thread Information System Call

Implemented `my_get_thread_kernel_info()`, a custom kernel system call that retrieves thread-level kernel data.

**Key Topics:** Kernel internals · task_struct · pthreads · copy_to_user

| | |
|---|---|
| Report | [Project2 Report](https://hackmd.io/FVMoGPudTxic6vRY3pya0w) |
| Description | [Project2 Description](https://staff.csie.ncu.edu.tw/hsufh/COURSES/FALL2025/linux_project_2.html) |
| Source | [`project2`](./project2/) |

**Highlights:**
- Retrieves PID, TGID, `task_struct` address, kernel stack address, and PGD address
- Multi-threaded test program (pthreads) to compare kernel info across threads
- Safe kernel/user-space data transfer via `copy_to_user()` / `copy_from_user()`

---

## Environment

| Item | Version |
|------|---------|
| OS | Ubuntu 20.04 |
| Kernel | Linux 5.x |
| Compiler | GCC |
| Language | C, Python 3 |

## Repository Structure

```
Linux_OS_Projects/
├── project1/                    # Virtual Memory Translation
│   ├── kernel/                  # Kernel-side system call implementation
│   ├── userspace/               # User-space test programs (C & Python)
│   └── README.md
├── project2/                    # Kernel Thread Information
│   ├── kernel/                  # Kernel-side system call implementation
│   ├── userspace/               # User-space test programs
│   └── README.md
└── README.md
```

## Reference

- [How to add a system call to the Linux kernel (Ubuntu)](https://hackmd.io/aist49C9R46-vaBIlP3LDA?view)
