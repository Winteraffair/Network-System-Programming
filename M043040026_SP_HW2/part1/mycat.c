#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


int main(int argc , char **argv){
	FILE *file;
	char *line=NULL;
	size_t len=0;
	size_t read;
	
	if(argc == 2){
	    file = fopen(argv[1],"r");
	    if(file == NULL){
	        perror("fopen");
		exit(1);
	    }
	    while((read = getline(&line,&len,file)) != -1){
		printf("%s",line);
	    }	
	    fclose(file);
	    
	}
	else{
	    printf("Usage: mycat filename\n");
	}
	
	
	
	exit(0);
}
