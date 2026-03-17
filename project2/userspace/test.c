/*
 * test.c — Single-threaded test for my_get_thread_kernel_info syscall
 *
 * Compile: gcc -o test test.c
 * Run:     ./test
 *
 * NOTE: Change SYSCALL_NUM to match your kernel's syscall table entry.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYSCALL_NUM 549   /* change to your registered syscall number */

struct thread_kernel_info {
    int            pid;
    int            tgid;
    unsigned long  task_struct_addr;
    unsigned long  kernel_stack_addr;
    unsigned long  pgd_addr;
};

int main(void)
{
    struct thread_kernel_info info;

    long ret = syscall(SYSCALL_NUM, &info);
    if (ret < 0) {
        perror("syscall failed");
        return 1;
    }

    printf("=== Kernel Thread Information ===\n");
    printf("PID              : %d\n",   info.pid);
    printf("TGID             : %d\n",   info.tgid);
    printf("task_struct addr : 0x%lx\n", info.task_struct_addr);
    printf("kernel stack addr: 0x%lx\n", info.kernel_stack_addr);
    printf("PGD addr         : 0x%lx\n", info.pgd_addr);

    return 0;
}
