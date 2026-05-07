#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"
#include "proc.h"
#include "crashcontext.h"

void
print_crash_context(char *msg)
{
  struct proc *p = myproc();

  printf("===== CRASH CONTEXT =====\n");

  printf("Panic reason: %s\n", msg);

  if(p != 0){
    printf("PID: %d\n", p->pid);
    printf("Process name: %s\n", p->name);
  } else {
    printf("PID: none\n");
    printf("Process name: kernel/boot\n");
  }

  printf("=========================\n");
}
