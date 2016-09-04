#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(void){
	
	printf("%s\n",getcwd(NULL,0));
	exit(errno);
}
