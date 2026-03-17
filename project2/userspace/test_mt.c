/*
 * test_mt.c — Multi-threaded test for my_get_thread_kernel_info syscall
 *
 * Demonstrates that threads in the same process share TGID and PGD,
 * but each has a unique PID and kernel stack.
 *
 * Compile: gcc -o test_mt test_mt.c -lpthread
 * Run:     ./test_mt
 *
 * NOTE: Change SYSCALL_NUM to match your kernel's syscall table entry.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

#define SYSCALL_NUM  549   /* change to your registered syscall number */
#define NUM_THREADS  4

struct thread_kernel_info {
    int            pid;
    int            tgid;
    unsigned long  task_struct_addr;
    unsigned long  kernel_stack_addr;
    unsigned long  pgd_addr;
};

void *thread_func(void *arg)
{
    int id = *(int *)arg;
    struct thread_kernel_info info;

    long ret = syscall(SYSCALL_NUM, &info);
    if (ret < 0) {
        perror("syscall failed");
        return NULL;
    }

    printf("\n--- Thread #%d ---\n", id);
    printf("  PID              : %d\n",   info.pid);
    printf("  TGID             : %d\n",   info.tgid);
    printf("  task_struct addr : 0x%lx\n", info.task_struct_addr);
    printf("  kernel stack addr: 0x%lx\n", info.kernel_stack_addr);
    printf("  PGD addr         : 0x%lx\n", info.pgd_addr);

    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    printf("=== Multi-threaded Kernel Thread Info Test ===\n");
    printf("Main process PID: %d\n", getpid());
    printf("Expected: all threads share TGID=%d and the same PGD\n\n", getpid());

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_func, &ids[i]) != 0) {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("\n=== Observations ===\n");
    printf("- Each thread has a unique PID (kernel thread ID)\n");
    printf("- All threads share the same TGID (= main process PID)\n");
    printf("- Each thread has its own kernel stack address\n");
    printf("- All threads share the same PGD (same address space)\n");

    return 0;
}
