/*
 * my_virt_to_phys.c
 *
 * Custom Linux system call: translates a virtual address to a physical address
 * by walking the kernel page table (PGD -> P4D -> PUD -> PMD -> PTE).
 *
 * Usage: syscall(__NR_my_get_physical_address, pid, vaddr)
 */

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/uaccess.h>
#include <asm/pgtable.h>

SYSCALL_DEFINE2(my_get_physical_address, pid_t, pid, unsigned long, vaddr)
{
    struct task_struct *task;
    struct mm_struct   *mm;
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    unsigned long phys_addr = 0;

    /* Find the target task by PID */
    rcu_read_lock();
    task = find_task_by_vpid(pid);
    if (!task) {
        rcu_read_unlock();
        printk(KERN_ERR "my_get_physical_address: PID %d not found\n", pid);
        return -ESRCH;
    }
    get_task_struct(task);
    rcu_read_unlock();

    mm = get_task_mm(task);
    put_task_struct(task);
    if (!mm) {
        printk(KERN_ERR "my_get_physical_address: cannot get mm_struct\n");
        return -EINVAL;
    }

    /* Walk the page table */
    pgd = pgd_offset(mm, vaddr);
    if (pgd_none(*pgd) || pgd_bad(*pgd)) {
        printk(KERN_WARNING "Invalid PGD for vaddr=0x%lx\n", vaddr);
        goto out;
    }
    printk(KERN_INFO "PGD = 0x%lx\n", pgd_val(*pgd));

    p4d = p4d_offset(pgd, vaddr);
    if (p4d_none(*p4d) || p4d_bad(*p4d)) {
        printk(KERN_WARNING "Invalid P4D for vaddr=0x%lx\n", vaddr);
        goto out;
    }

    pud = pud_offset(p4d, vaddr);
    if (pud_none(*pud) || pud_bad(*pud)) {
        printk(KERN_WARNING "Invalid PUD for vaddr=0x%lx\n", vaddr);
        goto out;
    }
    printk(KERN_INFO "PUD = 0x%lx\n", pud_val(*pud));

    pmd = pmd_offset(pud, vaddr);
    if (pmd_none(*pmd) || pmd_bad(*pmd)) {
        printk(KERN_WARNING "Invalid PMD for vaddr=0x%lx\n", vaddr);
        goto out;
    }
    printk(KERN_INFO "PMD = 0x%lx\n", pmd_val(*pmd));

    pte = pte_offset_map(pmd, vaddr);
    if (!pte || !pte_present(*pte)) {
        printk(KERN_WARNING "PTE not present for vaddr=0x%lx\n", vaddr);
        if (pte)
            pte_unmap(pte);
        goto out;
    }
    printk(KERN_INFO "PTE = 0x%lx\n", pte_val(*pte));

    /* Physical address = PFN * PAGE_SIZE + page offset */
    phys_addr = (pte_pfn(*pte) << PAGE_SHIFT) | (vaddr & ~PAGE_MASK);
    pte_unmap(pte);

    printk(KERN_INFO "vaddr=0x%lx -> phys=0x%lx\n", vaddr, phys_addr);

out:
    mmput(mm);
    return phys_addr;
}
