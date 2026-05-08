# Kernel Panic Logger Testing


## Member 4 Task: Testing and Validation

### Test 1: Manual Panic Test

A temporary panic was inserted into the kernel boot sequence using:

panic("test panic from is booting");
### Expected Output

The kernel panic output should display:

- Panic reason
- Process ID
- Process name
- Kernel circular log buffer

### Result

The panic was triggered successfully and the crash information was displayed.

Screenshot:

- screenshots/panic_test_manual.png

---

## Test 2: Normal Boot After Removing Test Panic

After removing the temporary panic line, xv6 was rebuilt and booted normally.

### Expected Output

xv6 should boot normally and reach the shell prompt.

### Result

xv6 reached the shell prompt successfully.

Screenshot:

- screenshots/normal_boot_after_test.png
## Test 3: Syscall-Triggered Panic Test

A custom user-level test program was added to trigger a kernel panic through a syscall.

The user runs this command inside xv6:

bash
panic_test


The user program calls the custom syscall, and the syscall triggers:

c
panic("test panic from syscall");


### Expected Output

The kernel panic logger should display the crash context after running the syscall test.

Expected information:

- Panic reason
- Process ID
- Process name
- Kernel circular log buffer

The expected panic reason is:

text
test panic from syscall


---

### Result and Actual Output

The syscall-triggered panic test was executed successfully.

The panic logger displayed the required crash context.

Actual output included:

text
panic: test panic from syscall
panic logger: collecting crash information
===== CRASH CONTEXT =====
Panic reason: test panic from syscall
PID: 3
Process name: panic_test
=========================

--- Kernel Circular Log Buffer ---

xv6 kernel is booting
hart 2 starting
hart 1 starting
panic: test panic from syscall
panic logger: collecting crash information
===== CRASH CONTEXT =====
Panic reason: test panic from syscall
PID: 3
Process name: panic_test
=========================

--- End Kernel Log Buffer ---
panic logger: done


Screenshot:

- screenshots/panic_test_syscall.png
