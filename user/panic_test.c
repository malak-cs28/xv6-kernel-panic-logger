#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("Triggering panic test syscall...\n");
  panic_test();
  exit(0);
}
