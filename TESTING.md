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
