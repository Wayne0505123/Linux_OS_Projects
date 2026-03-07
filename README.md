# Linux OS Projects
### Project 1
**Linux Virtual Memory Translation System Call**  
- Implemented a custom Linux system call to translate virtual addresses to physical addresses by traversing kernel page tables.
- Developed user-space programs in C and Python to analyze lazy page allocation and heap growth behavior.
- Utilized `ctypes` and shared libraries to bridge Python with kernel-level functionality.
- Gained hands-on experience with Linux kernel development, virtual memory management, and system-level debugging.
 
[Project1 Description](https://hackmd.io/@Yan-Hao-Wang/Hy2YW9jple)  
[Project1](https://hackmd.io/S01ADCVPQpmNljruzel_og)  

### Project 2
**Linux Kernel Thread Information System Call**  
- Implemented a custom Linux kernel system call `my_get_thread_kernel_info()` to retrieve kernel-level information of a running thread.
- Extracted thread-related data from the Linux kernel, including PID, TGID, process descriptor address (`task_struct`), kernel-mode stack address, and PGD table address.
- Developed user-space programs to invoke the system call and display thread kernel information.
- Implemented a multi-threaded test program using POSIX threads (pthreads) to compare kernel information across multiple threads within the same process.
- Utilized `copy_to_user()` and `copy_from_user()` for safe data transfer between kernel space and user space.
- Strengthened understanding of Linux kernel internals, system call implementation, thread management, and kernel-user space interaction.
  
[Project2 Description](https://staff.csie.ncu.edu.tw/hsufh/COURSES/FALL2025/linux_project_2.html)  
[Project2](https://hackmd.io/FVMoGPudTxic6vRY3pya0w)
#
課程網站: https://staff.csie.ncu.edu.tw/hsufh/COURSES/FALL2025/linuxos.html  
參考網址: [add syscall to kernel in Ubuntu](https://hackmd.io/aist49C9R46-vaBIlP3LDA?view)  
