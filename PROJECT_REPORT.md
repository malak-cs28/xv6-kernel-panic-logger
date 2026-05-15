# xv6 Kernel Panic Logger

## Operating Systems Project Report

---

# Team Information

## Project Title

**Kernel Panic Logger — Add Log Buffers and Crash Context Information for Panic Handling**

---

# Abstract

Kernel panic is one of the most critical failures in an operating system.  
When a kernel panic occurs, the operating system reaches a fatal state where safe execution can no longer continue.

The original xv6 operating system provides only a minimal panic mechanism that prints a simple panic message before stopping execution. While functional, this behavior lacks useful debugging information needed to analyze the cause of kernel crashes.

This project improves xv6 panic handling by implementing a lightweight **Kernel Panic Logger** capable of collecting and displaying crash context information and recent kernel logs before system shutdown.

The implemented system introduces:

- Enhanced panic reporting
- Crash context information
- Process identification
- Circular kernel log buffering
- Improved debugging visibility
- Panic testing support

The final result is a significantly more informative kernel panic mechanism inspired by real-world operating system debugging systems.

---

# Table of Contents

1. Introduction  
2. Problem Statement  
3. Project Objectives  
4. Background Concepts  
5. System Design  
6. Implementation Details  
7. Circular Log Buffer Design  
8. Crash Context Collection  
9. Panic Flow Architecture  
10. Testing and Validation  
11. Challenges Faced  
12. Results  
13. Educational Value  
14. Conclusion  
15. Repository  

---

# 1. Introduction

Operating systems are responsible for managing hardware resources, processes, memory, file systems, and system execution.

The kernel is the core component of the operating system and runs with full system privileges. Because of its critical role, any unrecoverable kernel error can cause the entire system to stop functioning.

This situation is known as a **Kernel Panic**.

In xv6, the default panic mechanism is implemented using:

```c
panic(char *s)
```

The original panic function simply prints a panic message and halts the CPU:

```text
panic: disk error
```

However, this output does not provide sufficient debugging information.

The objective of this project is to improve kernel debugging capabilities by extending panic handling with logging and crash analysis support.

---

# 2. Problem Statement

The default xv6 panic mechanism has several limitations:

- Only prints a simple panic message
- Does not show active process information
- Does not provide debugging context
- Does not preserve recent kernel activity
- Makes crash analysis difficult

As a result, identifying the cause of kernel failures becomes challenging.

The system lacks visibility into:

- Which process caused the crash
- What the kernel was doing before failure
- Recent kernel messages
- Runtime crash context

---

# 3. Project Objectives

The project aims to improve xv6 panic debugging by implementing:

- Enhanced panic output
- Panic reason reporting
- Crash context information
- Process ID reporting
- Process name reporting
- Circular kernel log buffering
- Boot panic handling
- Panic testing support

The project also aims to simulate simplified versions of debugging mechanisms used in modern operating systems.

---

# 4. Background Concepts

## 4.1 Kernel Panic

A kernel panic is a fatal operating system error that occurs when the kernel reaches a state where continued execution is unsafe.

Example:

```c
panic("disk error");
```

Once panic is triggered, the system halts execution.

---

## 4.2 Processes

A process represents a running program.

Examples in xv6 include:

- init
- sh
- panic_test

Each process has:

- PID (Process ID)
- Process name
- Execution state

---

## 4.3 System Calls

User programs cannot directly access kernel functions.

Instead, they communicate with the kernel using **system calls**.

Examples:

```c
read()
write()
fork()
```

The project introduces a testing syscall used to intentionally trigger panic events.

---

## 4.4 Circular Buffer

A circular buffer is a fixed-size memory structure that overwrites older data when the buffer becomes full.

Advantages:

- Constant memory usage
- Preserves recent logs
- Lightweight implementation
- Efficient kernel logging

---

# 5. System Design

The modified panic system works as follows:

```text
panic()
   ↓
print panic reason
   ↓
collect crash context
   ↓
print process information
   ↓
print kernel logs
   ↓
halt system
```

The logger intercepts kernel messages and stores them inside a circular log buffer.

During panic handling, the stored logs are printed before system shutdown.

---

# 6. Implementation Details

## 6.1 Panic Handler Modification

The original xv6 panic handler was extended to include:

- Panic reason printing
- Crash context collection
- Kernel log printing

Modified function:

```c
panic(char *s)
```

New behavior:

```text
panic()
↓
collect debugging information
↓
print logs
↓
halt
```

---

## 6.2 Crash Context Collection

Crash context information includes:

- Panic reason
- Current process ID
- Current process name

The current process is obtained using:

```c
myproc()
```

Example:

```c
struct proc *p = myproc();
```

Process information:

```c
p->pid
p->name
```

---

## 6.3 Circular Log Buffer

A fixed-size circular buffer was implemented:

```c
static char panic_log_buffer[LOG_BUF_SIZE];
```

Example size:

```c
#define LOG_BUF_SIZE 1024
```

The logger continuously stores printed kernel characters.

When the buffer becomes full:

- Older logs are overwritten
- New logs continue to be stored

This ensures constant memory usage.

---

## 6.4 Character Logging

Kernel characters are stored using:

```c
logputc(char c)
```

This function:

- Stores characters in the log buffer
- Prints characters to the console

Every printed kernel character passes through the logger.

---

## 6.5 Kernel Log Printing

The following function prints stored logs during panic handling:

```c
print_panic_logs()
```

The logger displays recent kernel messages before shutdown.

---

## 6.6 Boot Panic Handling

Special handling was added for early boot panics where no user process exists.

Example output:

```text
PID: none
Process name: kernel/boot
```

This prevents invalid process access during early kernel initialization.

---

## 6.7 Panic Testing Syscall

A syscall-based panic test was implemented.

User program:

```text
panic_test
```

Kernel behavior:

```c
panic("test panic from syscall");
```

This allows panic testing directly from user space.

---

# 7. Circular Log Buffer Design

The circular buffer stores the latest kernel logs using a rotating write position.

Buffer behavior:

```text
New logs → overwrite oldest logs
```

Advantages:

- Prevents unlimited memory growth
- Keeps recent debugging history
- Lightweight implementation
- Efficient for kernel environments

---

# 8. Crash Context Collection

Crash context provides information about the system state during panic.

Collected information includes:

| Information | Description |
|---|---|
| Panic Reason | Cause of the crash |
| PID | Current process ID |
| Process Name | Current running process |

Example:

```text
===== CRASH CONTEXT =====
Panic reason: test panic
PID: 4
Process name: panic_test
=========================
```

---

# 9. Panic Flow Architecture

## Original xv6 Panic Flow

```text
panic()
↓
print message
↓
halt
```

---

## Modified Panic Flow

```text
panic()
↓
print panic reason
↓
collect crash context
↓
print process information
↓
print circular logs
↓
halt
```

The modified flow provides significantly more debugging visibility.

---

# 10. Testing and Validation

The following tests were performed:

## 10.1 Manual Panic Test

Forced kernel panic using:

```c
panic("test panic");
```

Verified:

- Panic reason printing
- Crash context output
- Log buffer output

---

## 10.2 Syscall Panic Test

Triggered panic using user-space syscall.

Verified:

- User-to-kernel syscall functionality
- Process name reporting
- PID reporting

---

## 10.3 Boot Panic Test

Forced panic during boot stage.

Verified:

- Boot panic handling
- Kernel/boot process detection

---

## 10.4 Normal Boot Test

Removed forced panic and verified normal xv6 startup:

```text
xv6 kernel is booting
hart 1 starting
hart 2 starting
init: starting sh
$
```

---

## 10.5 Init Exiting Test

Executed:

```bash
kill 1
```

Verified kernel panic handling behavior.

---

# 11. Challenges Faced

Several challenges were encountered during implementation.

## Boot-Time Process Handling

During early boot stages:

```c
myproc()
```

may return null because no process exists yet.

This required special handling for boot panic scenarios.

---

## Circular Buffer Overwrite Logic

Implementing proper wrap-around behavior required careful index management.

---

## Kernel Logging Integration

The logger needed to intercept kernel printing without breaking normal console output.

---

## Merge Conflicts

Multiple team members modified overlapping kernel files, especially:

```text
kernel/printf.c
```

This resulted in Git merge conflicts that required manual resolution.

---

# 12. Results

The final implementation successfully provides:

- Enhanced panic diagnostics
- Crash context reporting
- Circular kernel logging
- Improved debugging visibility
- Boot panic support
- Stable normal boot operation

Example panic output:

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

# 13. Educational Value

This project demonstrates several important operating system concepts:

- Kernel panic handling
- Low-level debugging
- Crash diagnostics
- Circular buffer implementation
- Kernel logging systems
- Process management
- System calls
- Kernel development workflow
- Git collaboration in systems projects

The project also introduces debugging concepts inspired by real operating systems such as Linux.

---

# 14. Conclusion

The xv6 Kernel Panic Logger significantly improves the original panic handling mechanism by adding debugging visibility and crash analysis support.

Instead of printing only a simple panic message, the modified system now provides:

- Panic reason reporting
- Process identification
- Crash context information
- Recent kernel logs

The implementation demonstrates practical operating system debugging techniques while maintaining lightweight kernel behavior.

The project successfully transforms xv6 panic handling into a more informative and educational debugging system.

---

# 15. Repository

Project Repository:

https://github.com/malak-cs28/xv6-kernel-panic-logger
