//
// formatted console output -- printf, panic.
//

#include <stdarg.h>

#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "proc.h"

volatile int panicking = 0; // printing a panic message
volatile int panicked = 0; // spinning forever at end of a panic

#define LOG_BUF_SIZE 1024

static char panic_log_buffer[LOG_BUF_SIZE];
static int panic_log_index = 0;
static int panic_log_full = 0;

static void
logputc(char c)
{
  panic_log_buffer[panic_log_index] = c;
  panic_log_index = (panic_log_index + 1) % LOG_BUF_SIZE;

  if(panic_log_index == 0)
    panic_log_full = 1;
}

static void
rawputc(int c)
{
  consputc(c);
}

static void
logged_consputc(int c)
{
  logputc(c);
  rawputc(c);
}

#define consputc(c) logged_consputc(c)

static void
rawprint(char *s)
{
  while(*s)
    rawputc(*s++);
}

static void
print_panic_logs(void)
{
  int i;

  rawprint("\n--- Kernel Circular Log Buffer ---\n");

  if(panic_log_full){
    for(i = panic_log_index; i < LOG_BUF_SIZE; i++)
      rawputc(panic_log_buffer[i]);

    for(i = 0; i < panic_log_index; i++)
      rawputc(panic_log_buffer[i]);
  } else {
    for(i = 0; i < panic_log_index; i++)
      rawputc(panic_log_buffer[i]);
  }

  rawprint("\n--- End Kernel Log Buffer ---\n");
}

// lock to avoid interleaving concurrent printf's.
static struct {
  struct spinlock lock;
} pr;

static char digits[] = "0123456789abcdef";

static void
printint(long long xx, int base, int sign){
  char buf[20];
  int i;
  unsigned long long x; if(sign && (sign = (xx < 0)))
    x = -xx;
  else
    x = xx;

  i = 0;
  do {
    buf[i++] = digits[x % base];
  } while((x /= base) != 0);

  if(sign)
    buf[i++] = '-';

  while(--i >= 0)
    consputc(buf[i]);
}

static void
printptr(uint64 x)
{
  int i;
  consputc('0');
  consputc('x');
  for (i = 0; i < (sizeof(uint64) * 2); i++, x <<= 4)
    consputc(digits[x >> (sizeof(uint64) * 8 - 4)]);
}

// Print to the console.
int
printf(char *fmt, ...)
{
  va_list ap;
  int i, cx, c0, c1, c2;
  char *s;

  if(panicking == 0)
    acquire(&pr.lock);

  va_start(ap, fmt);
  for(i = 0; (cx = fmt[i] & 0xff) != 0; i++){
    if(cx != '%'){
      consputc(cx);
      continue;
    }
    i++;
    c0 = fmt[i+0] & 0xff;
    c1 = c2 = 0;
    if(c0) c1 = fmt[i+1] & 0xff;
    if(c1) c2 = fmt[i+2] & 0xff;
    if(c0 == 'd'){
      printint(va_arg(ap, int), 10, 1);
    } else if(c0 == 'l' && c1 == 'd'){
      printint(va_arg(ap, uint64), 10, 1);
      i += 1;
    } else if(c0 == 'l' && c1 == 'l' && c2 == 'd'){
      printint(va_arg(ap, uint64), 10, 1);
      i += 2;
    } else if(c0 == 'u'){
      printint(va_arg(ap, uint32), 10, 0);
 } else if(c0 == 'l' && c1 == 'u'){
      printint(va_arg(ap, uint64), 10, 0);
      i += 1;
    } else if(c0 == 'l' && c1 == 'l' && c2 == 'u'){
      printint(va_arg(ap, uint64), 10, 0);
      i += 2;
    } else if(c0 == 'x'){
      printint(va_arg(ap, uint32), 16, 0);
    } else if(c0 == 'l' && c1 == 'x'){
      printint(va_arg(ap, uint64), 16, 0);
      i += 1;
    } else if(c0 == 'l' && c1 == 'l' && c2 == 'x'){
      printint(va_arg(ap, uint64), 16, 0);
      i += 2;
    } else if(c0 == 'p'){
      printptr(va_arg(ap, uint64));
    } else if(c0 == 'c'){
      consputc(va_arg(ap, uint));
    } else if(c0 == 's'){
      if((s = va_arg(ap, char*)) == 0)
        s = "(null)";
      for(; *s; s++)
        consputc(*s);
    } else if(c0 == '%'){
      consputc('%');
    } else if(c0 == 0){
      break;
    } else {
      // Print unknown % sequence to draw attention.
  consputc('%');
      consputc(c0);
    }

  }
  va_end(ap);

  if(panicking == 0)
    release(&pr.lock);

  return 0;
}

void
panic(char *s)
{
  panicking = 1;

  printf("panic: %s\n", s);
  printf("panic logger: collecting crash information\n");

  // print_crash_context(s);
  print_panic_logs();

  printf("panic logger: done\n");

  panicked = 1; // freeze uart output from other CPUs
  for(;;)
    ;
}
void
printfinit(void)
{
  initlock(&pr.lock, "pr");
}
