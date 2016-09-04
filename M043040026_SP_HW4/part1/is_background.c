/*
 * is_background.c :  check for & at end
 */

#include <stdio.h>
#include "shell.h"

int is_background(char ** myArgv) {
	int i=0;
  	if (*myArgv == NULL)
    	return 0;

  	/* Look for "&" in myArgv, and process it.
  	 *
	 *	- Return TRUE if found.
	 *	- Return FALSE if not found.
	 *
	 * Fill in code.
	 */
	while(myArgv[i]!=NULL){
	    if(*myArgv[i] == '&'){
	        return TRUE;
	    }
	    i++;
	}
	return FALSE;

}
