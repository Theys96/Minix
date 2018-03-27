#include <lib.h>   // To do system calls
#include <time.h>  // This is the library this function belongs to

long utctime() {
  message m;
  _syscall(PM_PROC_NR, UTCTIME, &m);
  return m.m2_l1;
}