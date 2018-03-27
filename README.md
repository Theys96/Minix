# Minix
Exercise repository for the Minix operating system.

## Steps

### 1. Adding the system call
- Defining our system call number in `/usr/src/include/minix/callnr.h`: we chose 44.
- Adding the system call number to the the table in the process manager, located in `/usr/src/servers/pm/table.c`.
- The function prototypes of all system calls are located in `/usr/src/servers/pm/proto.h`, so we added ours there (`int do_utctime(void);`). Note that the return type of this function is an `int` because the return value of the function is the status code. The generated timestamp is of `time_t` type (which is a `long int`), but replying this timestamp is done through the system call message.
- The implementation of the system call we wrote in a new file, `/usr/src/servers/pm/utctime.c`, which we had to also add to the process manager's Makefile (in the same directory). The file is included in this repository.