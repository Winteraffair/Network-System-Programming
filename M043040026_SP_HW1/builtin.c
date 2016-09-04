/*
 * builtin.c : check for shell built-in commands
 * structure of file is
 * 1. definition of builtin functions
 * 2. lookup-table
 * 3. definition of is_builtin and do_builtin
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"




/****************************************************************************/
/* builtin function definitions                                             */
/****************************************************************************/

/* "echo" command.  Does not print final <CR> if "-n" encountered. */
static void bi_echo(char **argv) {
  	/* Fill in code.*/
	int i=0,k=1;
	int j = atoi(argv[2]);
	//int j = *argv[2] -'0';
	while(argv[i]!=NULL){
	    i++;
	}
	if(strcmp(argv[1],"-n")==0){
	    if((j+2) <= (i-1)){
	        printf("%s ",argv[j+2]);
	    }
	    else{
		printf("You didn't type a word at %d place\n",j);
	    }
	}
	else{
	    while(argv[k]!=NULL){
	        printf("%s ",argv[k]);
		k++;
	    }
	}
	printf("\n");
	
	
}
/* Fill in code. */

static void endprocess(){
	exit(0);
}


/****************************************************************************/
/* lookup table                                                             */
/****************************************************************************/

static struct cmd {
	char * keyword;				/* When this field is argv[0] ... */
	void (* do_it)(char **);	/* ... this function is executed. */
} inbuilts[] = {

	/* Fill in code. */
	{"exit",endprocess},
	{"logout",endprocess},
	{"bye",endprocess},
	{"quit",endprocess},
	{ "echo", bi_echo },		/* When "echo" is typed, bi_echo() executes.  */
	{ NULL, NULL }				/* NULL terminated. */
};




/****************************************************************************/
/* is_builtin and do_builtin                                                */
/****************************************************************************/

static struct cmd * this; 		/* close coupling between is_builtin & do_builtin */

/* Check to see if command is in the inbuilts table above.
Hold handle to it if it is. */
int is_builtin(char *cmd) {
  	struct cmd *tableCommand;

  	for (tableCommand = inbuilts ; tableCommand->keyword != NULL; tableCommand++)
    	if (strcmp(tableCommand->keyword,cmd) == 0) {
			this = tableCommand;
			return 1;
		}
  	return 0;
}


/* Execute the function corresponding to the builtin cmd found by is_builtin. */
int do_builtin(char **argv) {
  	this->do_it(argv);
}
