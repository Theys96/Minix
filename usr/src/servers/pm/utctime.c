#include "pm.h"
#include <minix/callnr.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"
#include "param.h"
#include <stdio.h>

// List of leap seconds, source: https://en.wikipedia.org/wiki/Leap_second
#define CURYEAR 2018
int leapsecs[49][2] = {
  {0, 0},  // 1970
  {0, 0},  // 1971
  {1, 1},  // 1972
  {0, 1},  // 1973
  {0, 1},  // 1974
  {0, 1},  // 1975
  {0, 1},  // 1976
  {0, 1},  // 1977
  {0, 1},  // 1978
  {0, 1},  // 1979
  {0, 0},  // 1980
  {1, 0},  // 1981
  {1, 0},  // 1982
  {1, 0},  // 1983
  {0, 0},  // 1984
  {1, 0},  // 1985
  {0, 0},  // 1986
  {0, 1},  // 1987
  {0, 0},  // 1988
  {0, 1},  // 1989
  {0, 1},  // 1990
  {0, 0},  // 1991
  {1, 0},  // 1992
  {1, 0},  // 1993
  {1, 0},  // 1994
  {0, 1},  // 1995
  {0, 0},  // 1996
  {1, 0},  // 1997
  {0, 1},  // 1998
  {0, 0},  // 1999
  {0, 0},  // 2000
  {0, 0},  // 2001
  {0, 0},  // 2002
  {0, 0},  // 2003
  {0, 0},  // 2004
  {0, 1},  // 2005
  {0, 0},  // 2006
  {0, 0},  // 2007
  {0, 1},  // 2008
  {0, 0},  // 2009
  {0, 0},  // 2010
  {0, 0},  // 2011
  {1, 0},  // 2012
  {0, 0},  // 2013
  {0, 0},  // 2014
  {1, 0},  // 2015
  {0, 1},  // 2016
  {0, 0},  // 2017
  {0, 0},  // 2018
};

int isleap(int year) {
    if ((year % 400) == 0) return 1;
    if ((year % 100) == 0) return 0;
    return ((year % 4) == 0);
}

long unix2utc(long timestamp) {
  int year = 1970;
  int n = 0;
  long t = 15638399; // June 30th, 1970 at 23:59:59
  
  while (year <= CURYEAR) {
    if (timestamp > t)
      timestamp -= leapsecs[n][0];
    else
      break;

    t += 15897600 ; // Go from june 30th to december 31th
    if (timestamp > t)
      timestamp -= leapsecs[n][1];
    else
      break;
    
    year++;
    t += isleap(year) ? 15724800 : 15638400; // Go from december 31th to june 30th
    n++;
  }
  
  return timestamp;
}

int do_utctime() {

  clock_t t[2];
  getuptime2(&t[0], &t[1]);

  time_t unix_time = (time_t)(t[1] + t[0]/system_hz);
  unix_time = (time_t)unix2utc(unix_time);
  
  mp->mp_reply.reply_time = unix_time;  

  return(OK);
}