/*
 *  timer.c : contains two timing functions to measure process time
 */

#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#include <time.h>
#include <stdlib.h>

/* Storage for baseline times. */
static clock_t start_time,start_cstime,start_cutime;

/* Save a baseline of user and system CPU times, plus wallclock time. */
void set_timer(void) {
	struct tms tmbuf;
	/* Fill in code. */
        start_time = times(&tmbuf);
        start_cstime = tmbuf.tms_cstime;
        start_cutime = tmbuf.tms_cutime;
}


/* Get second set of times, and take delta to get wallclock time.  Display. */
void stop_timer(void) {
	struct tms tmbuf;
	clock_t end_time;
	double ticks;
         
	ticks = sysconf(_SC_CLK_TCK);

	/* Get delta times and print them out.
	 *
	 * Fill in code. */
        end_time = times(&tmbuf);
        
        printf("Sys:%.3f User:%.3f Real:%.3f\n", (double)(tmbuf.tms_cstime-start_cstime)/ticks , (double)(tmbuf.tms_cutime-start_cutime)/ticks ,(double)(end_time-start_time)/ticks);
        //printf("real : %.6f \n",(float)(end_time-start_time)/ticks);
}

