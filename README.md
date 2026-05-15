# xv6 Kernel Panic Logger

## Overview

The **xv6 Kernel Panic Logger** improves the default panic handling mechanism in the xv6 operating system by adding detailed crash diagnostics and kernel debugging information.

In the original xv6 implementation, the `panic()` function only prints a simple panic message and halts the system. This project extends panic handling by introducing a lightweight logging and crash reporting system that helps developers understand what happened before the kernel crash occurred.

---

# Project Objectives

The main objective of this project is to make kernel crashes easier to debug by adding:

- Panic reason reporting
- Process information during crashes
- Crash context collection
- Circular kernel log buffering
- Structured panic output
- Improved debugging visibility

---

# Features

## Enhanced Panic Output

The panic handler was modified to display structured debugging information instead of only printing a single panic message.

---

## Panic Reason Reporting

The logger prints the exact panic message passed to:

```c
panic(char *s)
```

Example:

```c
panic("disk error");
```

Output:

```text
Panic reason: disk error
```

---

## Crash Context Information

The system collects runtime crash information including:

- Current process ID (PID)
- Current process name
- Panic reason
- Boot-time panic handling

This information helps identify which process was active when the crash occurred.

---

## Circular Kernel Log Buffer

A lightweight circular log buffer was implemented to continuously store recent kernel messages.

When the buffer becomes full, older messages are overwritten automatically while preserving the newest logs.

This allows the system to display the latest kernel activity before the crash.

Example logs:

```text
xv6 kernel is booting
hart 1 starting
init: starting sh
```

---

## Boot Panic Handling

The logger supports panic handling during early boot stages where no user process exists yet.

Example:

```text
PID: none
Process name: kernel/boot
```

---

## Panic Testing Support

The project includes testing methods for validating panic handling functionality using forced kernel panics and boot-time crash scenarios.

---

# Example Panic Output

```text
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
```

---

# Normal Boot Output

After removing the forced test panic, xv6 boots normally:

```text
xv6 kernel is booting
hart 1 starting
hart 2 starting
init: starting sh
$
```

---

# System Design

The modified panic flow works as follows:

```text
panic()
   ↓
print panic reason
   ↓
collect crash context
   ↓
print process information
   ↓
print circular kernel logs
   ↓
halt system
```

---

# Technical Components

## Modified Files

Key xv6 components modified during implementation:

```text
kernel/printf.c
kernel/proc.c
kernel/defs.h
kernel/sysproc.c
user/
```

---

## Core Functions

### Panic Handler

```c
panic(char *s)
```

Handles fatal kernel errors.

---

### Crash Context Printer

```c
print_crash_context()
```

Prints process information and panic details.

---

### Kernel Log Buffer Printer

```c
print_panic_logs()
```

Displays recent kernel logs stored in the circular buffer.

---

### Log Character Writer

```c
logputc(char c)
```

Stores printed kernel characters into the circular log buffer.

---

# Build Instructions

## Clean Previous Build

```bash
make clean
```

## Build and Run xv6

```bash
make qemu
```

---

# Testing

The following tests were performed:

- Manual kernel panic test
- Forced syscall panic test
- Boot panic test
- Normal boot verification
- Init process failure test using:

```bash
kill 1
```

---

# Documentation

Project documentation files:

```text
PROJECT_REPORT.md
PRESENTATION_NOTES.md
TESTING.md
```

---

# Repository Structure

```text
xv6-kernel-panic-logger/
│
├── kernel/
├── user/
├── screenshots/
├── PROJECT_REPORT.md
├── PRESENTATION_NOTES.md
├── TESTING.md
└── README.md
```

---

# Educational Value

This project demonstrates several important operating system concepts including:

- Kernel panic handling
- Operating system debugging
- Crash diagnostics
- Circular buffer implementation
- Kernel logging systems
- Process management
- System calls
- Low-level kernel development

The implemented design is inspired by real operating system crash debugging systems used in modern kernels such as Linux.

---

# Repository

Repository Link:

https://github.com/malak-cs28/xv6-kernel-panic-logger
