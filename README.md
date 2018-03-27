# Minix
Exercise repository for the Minix operating system.

## Steps

### 1. Adding the system call
- Defining our system call number in `/usr/src/include/minix/callnr.h`: we chose 44.
- Adding the system call number to the the table in the process manager, located in `/usr/src/servers/pm/table.c`.
- The function prototypes of all system calls are located in `/usr/src/servers/pm/proto.h`, so we added ours there (`int do_utctime(void);`). Note that the return type of this function is an `int` because the return value of the function is the status code. The generated timestamp is of `time_t` type (which is a `long int`), but replying this timestamp is done through the system call message.
- The implementation of the system call we wrote in a new file, `/usr/src/servers/pm/utctime.c`, which we had to also add to the process manager's Makefile (in the same directory). The file is included in this repository. The program uses the getuptime2() call to calculate its UNIX timestamp from boottime and number of CPU cycles since then.
- To recompile everything we ran `make services && make install && reboot` in `/usr/src/releasetools`.

### Adding the library function
- We decided to add the library function `utctime()` to `<time.h>`, so we first added its prototype (`long utctime();`) to `/usr/src/include/time.h`.
- The implementation we wrote for this library function we put, again, in a new file `/usr/src/lib/libc/sys-minix/utctime.c`. The file was added to the Makefile again (`Makefile.inc` in this case).
- To recompile everything we ran `make build && reboot` in `/usr/src/releasetools`.

## Testing
We wrote a test program, `test.c` (code included in this repository), to test our library function. The output of the first version of the program was:
```
0
1522178673
1522178673
```
The first line refers to the return value or status code of the system call. 0 means OK.  
The second line is the direct result of our system call (by running `_syscall(PM_PROC_NR, UTCTIME, &m)`). This reflects a good UNIX timestamp.  
The second line is the return value of the library function (by running `utctime()` from `<time.h>`).  
  
Currently, the system call still returns a "normal" UNIX timestamp. Leap seconds are yet to be implemented.