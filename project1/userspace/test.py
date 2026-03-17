"""
test.py — Python test for my_get_physical_address syscall using ctypes

Run: python3 test.py

NOTE: Change SYSCALL_NUM to match your kernel's syscall table entry.
"""

import ctypes
import os

SYSCALL_NUM = 548   # change to your registered syscall number

libc = ctypes.CDLL("libc.so.6", use_errno=True)

def virt_to_phys(pid: int, vaddr: int) -> int:
    """Call my_get_physical_address(pid, vaddr) and return physical address."""
    result = libc.syscall(SYSCALL_NUM, ctypes.c_int(pid), ctypes.c_ulong(vaddr))
    return result

def main():
    pid = os.getpid()
    print(f"=== Virtual to Physical Address Translation (Python) ===")
    print(f"PID: {pid}\n")

    # Stack-like: Python integer object on heap
    x = ctypes.c_int(100)
    vaddr = ctypes.addressof(x)
    phys  = virt_to_phys(pid, vaddr)
    print(f"[ctypes int]  vaddr = 0x{vaddr:016x}  ->  phys = 0x{phys:016x}")

    # Allocate a buffer
    buf = ctypes.create_string_buffer(4096)
    buf[0] = b'\x01'   # touch to ensure page allocation
    vaddr_buf = ctypes.addressof(buf)
    phys_buf  = virt_to_phys(pid, vaddr_buf)
    print(f"[buffer]      vaddr = 0x{vaddr_buf:016x}  ->  phys = 0x{phys_buf:016x}")

    # Lazy allocation demo: allocate before and after touching
    buf2 = ctypes.create_string_buffer(4096)
    vaddr2 = ctypes.addressof(buf2)
    phys_before = virt_to_phys(pid, vaddr2)
    print(f"\n[lazy before touch]  phys = 0x{phys_before:016x}")
    buf2[0] = b'\xff'
    phys_after = virt_to_phys(pid, vaddr2)
    print(f"[lazy after  touch]  phys = 0x{phys_after:016x}")

if __name__ == "__main__":
    main()
