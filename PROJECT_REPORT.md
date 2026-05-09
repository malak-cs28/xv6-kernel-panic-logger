# Kernel Panic Logger - Final Project Report

## 1. Project Title

Kernel Panic Logger - Add log buffers and crash context information for panic handling.

## 2. Project Overview

This project modifies the xv6 operating system to improve kernel panic handling.

In the original xv6 system, when a kernel panic happens, the system prints a simple panic message and stops execution. This behavior is useful, but it does not give enough debugging information about what happened before the crash or which process caused the crash.

Our project improves the panic handling mechanism by adding a Kernel Panic Logger.

The improved panic logger provides:

- Panic reason
- Crash context information
- Process ID
- Process name
- Kernel circular log buffer
- Clear panic output for debugging and testing

The goal of the project is to make xv6 panic output more useful for debugging while keeping the design simple, clear, and suitable for an operating systems course project.

## 3. Problem Statement

Kernel panic is a serious system error where the operating system cannot safely continue execution.

The default xv6 panic function is limited because it mainly prints the panic reason only.

This creates a problem during debugging because the developer may not know:

- Which process caused the panic
- What the process ID was
- What happened before the crash
- What kernel messages appeared recently
- Whether the panic happened during boot or during normal process execution

Because of this, understanding the cause of a crash becomes harder.

## 4. Project Objectives

The main objectives of this project are:

1. Understand how xv6 handles kernel panic.
2. Modify the panic function to show more useful information.
3. Build a circular kernel log buffer.
4. Store recent kernel messages.
5. Print crash context during panic.
6. Show the panic reason clearly.
7. Show the process ID if a process exists.
8. Show the process name if a process exists.
9. Handle boot panic when no process exists.
10. Test the implementation using forced panic scenarios.
11. Document the final implementation and testing results.

## 5. System and Tools Used

The project was implemented using:

- Operating System: Ubuntu
- Target Operating System: xv6-labs-2025
- Architecture: RISC-V
- Emulator: QEMU
- Version Control: Git and GitHub
- Repository: https://github.com/malak-cs28/xv6-kernel-panic-logger

## 6. Team Task Distribution

| Member | Task |
|---|---|
| Member 1 | Understand xv6 panic() and modify kernel/printf.c |
| Member 2 | Build the circular log buffer |
| Member 3 | Build crash context: PID, process name, panic reason |
| Member 4 | Testing: force panic, screenshots, prove it works |
| Member 5 | Documentation, presentation, Git organization, and final report |

## 7. Original xv6 Panic Behavior

In the original xv6 system, the panic function prints a panic message and stops the kernel.

The output is usually simple, for example:

    panic: test panic

This tells us that a panic happened, but it does not give enough information for debugging.

The original behavior does not clearly show:

- The process ID
- The process name
- The crash context
- Recent kernel logs

## 8. Improved Panic Logger Design

Our solution improves the panic handler by adding a panic logger.

When panic happens, the new panic logger performs these steps:

1. Print the panic reason.
2. Start collecting crash information.
3. Print crash context.
4. Print process ID.
5. Print process name.
6. Print the kernel circular log buffer.
7. Print an end marker for the log buffer.
8. Finish panic logging.

The output becomes easier to understand and more useful for debugging.

## 9. Crash Context Information

Crash context means the important information collected at the time of the crash.

In this project, crash context includes:

- Panic reason
- PID
- Process name

Example output:

    ===== CRASH CONTEXT =====
    Panic reason: init exiting
    PID: 1
    Process name: init
    =========================

If the panic happens during boot and no process exists, the output shows:

    PID: none
    Process name: kernel/boot

This makes the logger safer because it does not assume that a process always exists.

## 10. Kernel Circular Log Buffer

A circular log buffer is a fixed-size buffer that stores recent kernel messages.

When the buffer becomes full, new messages overwrite old messages.

This design is useful because:

- It avoids using unlimited memory.
- It keeps the most recent kernel messages.
- It helps debugging after a panic.
- It is simple and suitable for kernel-level logging.

During panic, the logger prints the buffer like this:

    --- Kernel Circular Log Buffer ---
    xv6 kernel is booting
    panic: test panic
    panic logger: collecting crash information
    --- End Kernel Log Buffer ---

## 11. Important Project Features

The final project includes the following features:

### 11.1 Panic Reason

The panic reason is printed clearly.

Example:

    panic: test panic
    Panic reason: test panic

### 11.2 Process ID

If a process exists, the logger prints its PID.

Example:

    PID: 1

### 11.3 Process Name

If a process exists, the logger prints its name.

Example:

    Process name: init

### 11.4 Boot Panic Handling

If the panic happens during boot before a process exists, the logger prints:

    PID: none
    Process name: kernel/boot

### 11.5 Kernel Log Buffer

The logger prints recent kernel messages from the circular buffer.

### 11.6 Normal Boot Still Works

After removing test panic code, xv6 boots normally and reaches the shell.

Example:

    xv6 kernel is booting
    hart 1 starting
    hart 2 starting
    init: starting sh
    $

## 12. Files Involved

The implementation mainly involves the following parts of xv6:

| File | Purpose |
|---|---|
| kernel/printf.c | Panic output and panic logger integration |
| kernel/log.c or related log file | Circular log buffer implementation |
| kernel/crashcontext.c or related file | Crash context handling |
| kernel/proc.c | Process information |
| kernel/proc.h | Process structure |
| Makefile | Build integration |
| TESTING.md | Testing documentation |
| screenshots/ | Screenshots for proof |
| PROJECT_REPORT.md | Final report |
| PRESENTATION_NOTES.md | Presentation notes |
| README.md | Repository summary |

## 13. Testing and Validation

Testing was done by forcing different panic scenarios and checking the output.

### Test 1: Manual Test Panic

A manual panic was triggered to check if the panic logger works.

Expected result:

- Panic reason appears.
- Panic logger starts.
- Circular log buffer appears.
- Panic logger finishes.

Observed output:

    xv6 kernel is booting

    panic: test panic
    panic logger: collecting crash information

    --- Kernel Circular Log Buffer ---

    xv6 kernel is booting
    panic: test panic
    panic logger: collecting crash information

    --- End Kernel Log Buffer ---
    panic logger: done

This proves that the circular log buffer is printed during panic.

### Test 2: Normal Boot After Removing Test Panic

After removing the forced test panic, xv6 was run again.

Observed output:

    xv6 kernel is booting
    hart 1 starting
    hart 2 starting
    init: starting sh
    $

This proves that the system still boots normally.

### Test 3: Init Exiting Panic

Inside xv6, the following command was used:

    kill 1

Observed output:

    panic: init exiting

    ===== CRASH CONTEXT =====
    Panic reason: init exiting
    PID: 1
    Process name: init
    =========================

This proves that the logger can detect process context and print the PID and process name.

### Test 4: Boot Panic

A boot panic was triggered to test the case where no process exists yet.

Observed output:

    panic: test panic from is booting

    panic logger: collecting crash information
    ===== CRASH CONTEXT =====
    Panic reason: test panic from is booting
    PID: none
    Process name: kernel/boot
    =========================

This proves that the logger handles boot panic safely.

## 14. Screenshots Evidence

Screenshots were taken to prove that the implementation works.

The screenshots show:

1. Successful build using make clean and make qemu.
2. Manual panic output.
3. Kernel circular log buffer output.
4. Normal boot after removing test panic.
5. Init exiting panic using kill 1.
6. Boot panic showing PID none and process name kernel/boot.

These screenshots should be stored in the repository inside the screenshots folder.

## 15. Git Workflow

The team used Git and GitHub to organize the project.

Task 5 was completed using a separate branch:

    member5-documentation

The recommended Git commands are:

    git checkout main
    git pull origin main
    git checkout -b member5-documentation
    git add PROJECT_REPORT.md PRESENTATION_NOTES.md README.md
    git commit -m "Add final documentation and presentation notes"
    git push origin member5-documentation

After pushing, a pull request should be opened from:

    member5-documentation

to:

    main

## 16. Design Quality

The design is clear and maintainable because:

- Panic logging is focused on panic handling.
- Crash context is printed in a readable format.
- The circular buffer avoids unlimited memory usage.
- The output is easy to test and verify.
- The design handles both process panic and boot panic.
- The project keeps the original xv6 behavior while improving debugging output.

## 17. Limitations

The current implementation has some limitations:

- The log buffer has a limited size.
- Logs are not saved permanently after reboot.
- Logs are mainly printed only during panic.
- There are no timestamps in the log output.
- The system still stops after panic, which is expected kernel behavior.

## 18. Future Improvements

Possible future improvements include:

- Save panic logs to disk.
- Add timestamps to log messages.
- Add CPU or hart ID to the crash context.
- Add syscall-based panic testing.
- Add log levels such as INFO, WARNING, and ERROR.
- Add automated tests for panic scenarios.

## 19. Conclusion

This project improves xv6 panic handling by adding a Kernel Panic Logger.

The new logger prints the panic reason, crash context, process ID, process name, and recent kernel messages from a circular log buffer.

Testing proves that the implementation works during manual panic, init process panic, boot panic, and normal boot after removing test panic.

The project demonstrates important operating system concepts such as kernel panic handling, debugging, process context, kernel logging, circular buffers, and Git-based collaboration.
