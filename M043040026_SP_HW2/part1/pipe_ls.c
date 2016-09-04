#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#define buffersize 2048 
int main(void){
	pid_t pid;
	int stat=0;
	char *command[3]={"ls","-l",NULL};
	char buffer[buffersize]={0};
	int pipe_rd[2];
	
	if(pipe(pipe_rd) == -1){
	    perror("pipe");
	    exit(errno);
	}
	
	pid = fork();
	switch(pid){
	   case -1:
		perror("fork");
		exit(errno);
	   default:
		waitpid(pid,&stat,0);
		
		close(pipe_rd[1]);
		read(pipe_rd[0],buffer,buffersize);
		buffer[buffersize]='\0';
		close(pipe_rd[0]);
		printf("%s",buffer);
	
		break;
	   case 0:
		close(pipe_rd[0]);
		
		if((dup2(pipe_rd[1],1))==-1){
		    perror("dup2");
		    exit(errno);
		}

		
		execvp(command[0],command);
		exit(errno);
	}
	exit(0);
}
