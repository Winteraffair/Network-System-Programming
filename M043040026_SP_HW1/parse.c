/*
 * parse.c : use whitespace to tokenise a line
 * Initialise a vector big enough
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

/* Parse a commandline string into an argv array. */
char ** parse(char *line) {

  	static char delim[] = " \t\n"; /* SPACE or TAB or NL */
  	int count = 0;
  	char * token;
  	char **newArgv=NULL;
	
	
  	/* Nothing entered. */
  	if (line == NULL) {
    	return NULL;
  	}

  	/* Init strtok with commandline, then get first token.
     * Return NULL if no tokens in line.
	 *
	 * Fill in code.
     */ 
	token = strtok(line,delim);	
	if(token == NULL){
	    return NULL;
	}
	/*printf("%s\n",token);
	token = strtok(NULL,delim);*/

  	/* Create array with room for first token.
  	 *
	 * Fill in code.
	 */
	

	newArgv = (char **)realloc(newArgv,(count+1)*sizeof(char *));
	newArgv[count]=(char *)malloc((strlen(token)+1) * sizeof(char));
	strcpy(newArgv[count],token);
	printf("[%d]:%s\n",count,newArgv[count]);
	count++;
	
	
	
	
	/**newArgv = token;
	printf("%s\n",*newArgv);*/
	
  	/* While there are more tokens...
	 *
	 *  - Get next token.
	 *	- Resize array.
	 *  - Give token its own memory, then install it.
	 * 
  	 * Fill in code.
	 */
	token = strtok(NULL,delim);
	while(token != NULL){
	    newArgv = (char **)realloc(newArgv,(count+1)*sizeof(char 		    *));
	    newArgv[count]=(char *)malloc((strlen(token)+1) 		    *sizeof(char));
	    strcpy(newArgv[count],token);
	    printf("[%d]:%s\n",count,newArgv[count]);
	    count++;
	    token = strtok(NULL,delim);
	}

  	/* Null terminate the array and return it.
	 *
  	 * Fill in code.
	 */
	newArgv = (char **)realloc(newArgv,(count+1)*sizeof(char 		*));
	
	newArgv[count]=NULL;
	
  	return newArgv;
}


/*
 * Free memory associated with argv array passed in.
 * Argv array is assumed created with parse() above.
 */
void free_argv(char **oldArgv) {

	int i = 0;

	/* Free each string hanging off the array.
	 * Free the oldArgv array itself.
	 *
	 * Fill in code.
	 */
	//string free
	while(oldArgv[i] != NULL){
	   free(oldArgv[i]);
	   i++;
	}
	//oldArgv free
	free(oldArgv);
}
