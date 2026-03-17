/*
 * my_thread_info.c
 *
 * Custom Linux system call: my_get_thread_kernel_info()
 * Returns kernel-level information of the calling thread.
 *
 * Usage: syscall(__NR_my_get_thread_kernel_info, &info)
 */

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/mm.h>

/* Must match the struct in userspace */
struct thread_kernel_info {
    pid_t          pid;
    pid_t          tgid;
    unsigned long  task_struct_addr;
    unsigned long  kernel_stack_addr;
    unsigned long  pgd_addr;
};

SYSCALL_DEFINE1(my_get_thread_kernel_info,
                struct thread_kernel_info __user *, user_info)
{
    struct thread_kernel_info info;
    struct task_struct *task = current;

    if (!user_info)
        return -EINVAL;

    info.pid              = task->pid;
    info.tgid             = task->tgid;
    info.task_struct_addr = (unsigned long)task;
    info.kernel_stack_addr = (unsigned long)task->stack;
    info.pgd_addr         = (task->mm) ? (unsigned long)task->mm->pgd : 0;

    printk(KERN_INFO "[my_get_thread_kernel_info] PID=%d TGID=%d "
           "task=0x%lx stack=0x%lx pgd=0x%lx\n",
           info.pid, info.tgid,
           info.task_struct_addr,
           info.kernel_stack_addr,
           info.pgd_addr);

    if (copy_to_user(user_info, &info, sizeof(info)))
        return -EFAULT;

    return 0;
}
