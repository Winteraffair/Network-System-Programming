/*
 * run_command.c :    do the fork, exec stuff, call other functions
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"
#include <string.h>

void run_command(char **myArgv) {
  	pid_t pid;
  	int stat;
  	int run_in_background;
	char *command=NULL;
        char *oneblock= " "; 
	int i=0;
	command = (char *)realloc(command , sizeof(char)*200);
  	/*
   	* Check for background processing.
   	* Do this before fork() as the "&" is removed from the argv array
   	* as a side effect.
   	*/
  	run_in_background = is_background(myArgv);

  	switch(pid = fork()) {

    	/* Error. */
    	case -1 :
      		perror("fork");
      		exit(errno);

    	/* Parent. */
    	default :
      		if (!run_in_background) {
        		waitpid(pid,&stat,0);	/* Wait for child to terminate. */

        		/*if (WIFEXITED(stat) && WEXITSTATUS(stat)) {
          			fprintf(stderr, "Child %d exited with error status %d: %s\n",
	      				pid, WEXITSTATUS(stat), (char*)strerror(WEXITSTATUS(stat)));

        		} else if (WIFSIGNALED(stat) && WTERMSIG(stat)) {
	  				fprintf (stderr, "Child %d exited due to signal %d: %s\n",
	      				pid, WTERMSIG(stat), (char*)strsignal(WTERMSIG(stat)));
        		}*/
      		}
      		return;

    	/* Child. */
    	case 0 :
		if(run_in_background == TRUE){
	 	while(myArgv[i] != NULL){
		    strcat(command,myArgv[i]);
		    strcat(command,oneblock);
		    i++;
		}
		    system(command);
		    perror("system");
		    free(command);	
	        }

	        else{
		    /* Redirect input and update argv. */
		    redirect_in(myArgv);
      		    /* Redirect output and update argv. */
		    redirect_out(myArgv);
		  
		    if(pipe_present(myArgv) >= 1){
      		       pipe_and_exec(myArgv);
		    }
		    execvp(myArgv[0],myArgv);
	        }
      		
      		exit(errno);
	}
}
