/*
 * test.c — User-space test program for my_get_physical_address syscall
 *
 * Compile: gcc -o test test.c
 * Run:     ./test
 *
 * NOTE: Change SYSCALL_NUM to match your kernel's syscall table entry.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYSCALL_NUM 548   /* change to your registered syscall number */

int main(void)
{
    pid_t pid = getpid();
    int   arr[5] = {1, 2, 3, 4, 5};
    int  *heap   = malloc(sizeof(int) * 5);

    printf("=== Virtual to Physical Address Translation ===\n");
    printf("PID: %d\n\n", pid);

    /* Stack variable */
    unsigned long vaddr_stack = (unsigned long)arr;
    long phys_stack = syscall(SYSCALL_NUM, pid, vaddr_stack);
    printf("[Stack]  vaddr = 0x%lx  ->  phys = 0x%lx\n", vaddr_stack, phys_stack);

    /* Heap variable */
    unsigned long vaddr_heap = (unsigned long)heap;
    long phys_heap = syscall(SYSCALL_NUM, pid, vaddr_heap);
    printf("[Heap]   vaddr = 0x%lx  ->  phys = 0x%lx\n", vaddr_heap, phys_heap);

    /* Touch the heap page to trigger lazy allocation */
    heap[0] = 42;
    long phys_heap_after = syscall(SYSCALL_NUM, pid, vaddr_heap);
    printf("[Heap after touch]  phys = 0x%lx\n", phys_heap_after);

    /* Demonstrate heap growth */
    printf("\n--- Heap Growth Test ---\n");
    for (int i = 0; i < 5; i++) {
        int *p = malloc(4096);
        *p = i;   /* touch to allocate page */
        long phys = syscall(SYSCALL_NUM, pid, (unsigned long)p);
        printf("malloc[%d]: vaddr=0x%lx  phys=0x%lx\n", i, (unsigned long)p, phys);
    }

    free(heap);
    return 0;
}
