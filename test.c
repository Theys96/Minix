#include <lib.h>
#include <stdio.h>
#include <time.h>

int main() {
  message m;
  printf("%d\n", _syscall(PM_PROC_NR, UTCTIME, &m));
  printf("%ld\n", m.m2_l1); 
  printf("%ld\n", utctime());
  printf("%ld\n", (long)time(0));
  return 0;
}
