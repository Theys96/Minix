#include "pm.h"
#include <minix/callnr.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"
#include "param.h"
#include <stdio.h>

int do_utctime() {

  clock_t t[2];
  getuptime2(&t[0], &t[1]);

  time_t unix_time = (time_t)(t[1] + t[0]/system_hz);

  mp->mp_reply.m2_l1 = 42;
  mp->mp_reply.reply_time = unix_time;  

  return(OK);
}