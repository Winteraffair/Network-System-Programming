/*
 * redirect_out.c   :   check for >
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"
#define STD_OUTPUT 1
#define STD_INPUT  0

/*
 * Look for ">" in myArgv, then redirect output to the file.
 * Returns 0 on success, sets errno and returns -1 on error.
 */
int redirect_out(char ** myArgv) {
	int i = 0,check=0;
  	int fd;

  	/* search forward for >
  	 * Fill in code. */
	while(myArgv[i]!=NULL && check == 0){
	   if(strcmp(myArgv[i],">") == 0){
		check=1;
	   }
	   else{
	        i++;
	   }
	}
	if(check == 0){
	    return -1;
	}

  	
  	if (myArgv[i]) {	/* found ">" in vector. */

    	/* 1) Open file.
    	 * 2) Redirect to use it for output.
    	 * 3) Cleanup / close unneeded file descriptors.
    	 * 4) Remove the ">" and the filename from myArgv.
		 *
    	 * Fill in code. */
	fd = open(myArgv[i+1],O_RDWR);
	if(fd == -1){
	    perror("open");
	    return -1; 
	}
	
	if(dup2(fd,1) == -1){
	    perror("dup2");
	    return -1; 
	};
	
	close(fd);
	
	

	myArgv[i]=NULL;
	myArgv[i+1]=NULL;
  	}
  	return 0;
}
