/*
 * shell.c  : test harness for parse routine
 */

#define LONGLINE 255

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "shell.h"

int main(int argc, char* argv[]) {
	char line[LONGLINE];
  	char **myArgv;
	sigset_t set1;


        /*sigemptyset(&set1);
        sigaddset(&set1,SIGINT);
        sigaddset(&set1,SIGQUIT);*/

        sighold(SIGINT);
        sighold(SIGQUIT);

  	fputs("myshell -> ",stdout);
  	while (fgets(line,LONGLINE,stdin)) {
        
    	/* Create argv array based on commandline. */
    	if ((myArgv = parse(line))!= NULL) {

      		/* If command is recognized as a builtin, do it. */
      		if (is_builtin(myArgv[0])) {
        		do_builtin(myArgv);

			/* Non-builtin command. */
			} else {
				run_command(myArgv);
			}

			/* Free argv array. */
			free_argv(myArgv);
		}
	
    	fputs("myshell -> ",stdout);
	}
  	exit(0);
}
