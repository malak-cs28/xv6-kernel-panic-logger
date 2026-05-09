# Kernel Panic Logger - Presentation Notes

## Slide 1: Title

Kernel Panic Logger

Add log buffers and crash context information for panic handling in xv6.

## Slide 2: Project Idea

Our project improves panic handling in xv6.

In the original xv6 system, when a kernel panic happens, the system prints a simple panic message and stops execution.

We improved this behavior by adding a Kernel Panic Logger that prints useful debugging information when a panic happens.

## Slide 3: The Problem

The default xv6 panic output is limited.

It does not clearly show:

- Which process caused the panic
- The process ID
- The process name
- Recent kernel messages
- Useful crash context

This makes debugging harder because the developer only sees the panic message without enough details.

## Slide 4: Project Goal

The goal of the project is to make kernel panic output more useful for debugging.

We added:

- Panic reason
- Crash context
- PID
- Process name
- Kernel circular log buffer

This helps the developer understand what happened before the crash.

## Slide 5: Original xv6 Panic Behavior

Before modification, panic output was simple.

Example:

    panic: test panic

This shows that a panic happened, but it does not show enough information about the process or recent kernel activity.

## Slide 6: Improved Panic Logger Output

After our modification, the panic output became more detailed.

Example:

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

This output is easier to understand and more useful for debugging.

## Slide 7: Circular Log Buffer

A circular log buffer is a fixed-size buffer.

It stores recent kernel messages.

When the buffer becomes full, new messages overwrite old messages.

This is useful because:

- The kernel cannot use unlimited memory.
- Recent messages are usually the most important.
- It helps show what happened before the panic.
- It keeps the design simple.

## Slide 8: Crash Context

Crash context means the important information collected at the time of the crash.

In our project, crash context includes:

- Panic reason
- PID
- Process name

Example:

    ===== CRASH CONTEXT =====
    Panic reason: init exiting
    PID: 1
    Process name: init
    =========================

This helps us know which process was involved in the crash.

## Slide 9: Boot Panic Case

Sometimes panic happens during boot before any process exists.

In this case, our logger prints:

    PID: none
    Process name: kernel/boot

This makes the implementation safer because it does not assume that a process always exists.

## Slide 10: Testing

We tested the project using different scenarios:

1. Manual test panic
2. Normal boot after removing test panic
3. Init exiting panic using kill 1
4. Boot panic test

These tests prove that the panic logger works in different cases.

## Slide 11: Manual Panic Test Result

In the manual panic test, the output showed:

- Panic reason
- Panic logger message
- Kernel circular log buffer
- Panic logger completion message

Example:

    panic: test panic
    panic logger: collecting crash information
    --- Kernel Circular Log Buffer ---
    xv6 kernel is booting
    panic: test panic
    --- End Kernel Log Buffer ---
    panic logger: done

This proves that the logger prints recent kernel messages during panic.

## Slide 12: Normal Boot Test Result

After removing the forced test panic, xv6 booted normally.

Example:

    xv6 kernel is booting
    hart 1 starting
    hart 2 starting
    init: starting sh
    $

This proves that the project did not break normal xv6 execution.

## Slide 13: Init Exiting Panic Test Result

We tested process-related panic by using:

    kill 1

The output showed:

    panic: init exiting

    ===== CRASH CONTEXT =====
    Panic reason: init exiting
    PID: 1
    Process name: init
    =========================

This proves that the logger can print process information.

## Slide 14: Git and Documentation

We used Git and GitHub for version control.

Repository:

https://github.com/malak-cs28/xv6-kernel-panic-logger

Documentation files:

- PROJECT_REPORT.md
- PRESENTATION_NOTES.md
- TESTING.md
- README.md
- screenshots/

Task 5 was done on a separate branch:

    member5-documentation

## Slide 15: Limitations

The current project has some limitations:

- Logs are not saved after reboot.
- Log buffer size is limited.
- No timestamp is added to logs.
- Logs are mainly printed during panic.
- The system still stops after panic, which is normal kernel behavior.

## Slide 16: Future Improvements

Possible future improvements:

- Save panic logs to disk.
- Add timestamps.
- Add CPU or hart ID.
- Add syscall-based panic testing.
- Add log levels such as INFO, WARNING, and ERROR.
- Add automated tests for panic scenarios.

## Slide 17: Conclusion

The project improves xv6 panic debugging.

It makes kernel crashes easier to understand by showing:

- Why the panic happened
- Which process was involved
- What recent kernel messages appeared before the crash

This project demonstrates important operating system concepts such as panic handling, process context, kernel logging, debugging, and Git collaboration.
