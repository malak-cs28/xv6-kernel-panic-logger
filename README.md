# xv6 Kernel Panic Logger

## Project Title

Kernel Panic Logger - Add log buffers and crash context information for panic handling.

## Project Description

This project improves panic handling in the xv6 operating system.

The default xv6 panic function prints a simple panic message and stops execution. Our project improves this by adding a Kernel Panic Logger that prints more useful debugging information when a kernel panic happens.

## Main Features

- Improved panic output
- Panic reason printing
- Crash context information
- Process ID display
- Process name display
- Kernel circular log buffer
- Boot panic handling
- Testing screenshots
- Git-based team workflow

## Why This Project Is Useful

Kernel panic is a serious error where the operating system cannot safely continue execution.

The original panic output in xv6 is simple and does not give enough debugging details.

This project makes panic debugging easier by showing:

- The reason for the panic
- The process ID
- The process name
- Recent kernel messages before the crash

## Example Panic Output

    panic: test panic
    panic logger: collecting crash information

    ===== CRASH CONTEXT =====
    Panic reason: test panic
    PID: none
    Process name: kernel/boot
    =========================

    --- Kernel Circular Log Buffer ---
    xv6 kernel is booting
    panic: test panic
    panic logger: collecting crash information
    --- End Kernel Log Buffer ---

    panic logger: done

## Normal Boot Output

After removing the forced test panic, xv6 boots normally:

    xv6 kernel is booting
    hart 1 starting
    hart 2 starting
    init: starting sh
    $

## Team Task Distribution

| Member | Task |
|---|---|
| Member 1 | Understand xv6 panic() and modify kernel/printf.c |
| Member 2 | Build the circular log buffer |
| Member 3 | Build crash context: PID, process name, panic reason |
| Member 4 | Testing: force panic, screenshots, prove it works |
| Member 5 | Documentation, presentation, Git organization, and final report |

## Build and Run

To build and run xv6:

    make clean
    make qemu

## Testing

Testing included:

1. Manual panic test
2. Normal boot test
3. Init exiting panic test using kill 1
4. Boot panic test

## Documentation Files

This repository includes:

- PROJECT_REPORT.md
- PRESENTATION_NOTES.md
- TESTING.md
- screenshots/

## Repository

https://github.com/malak-cs28/xv6-kernel-panic-logger
