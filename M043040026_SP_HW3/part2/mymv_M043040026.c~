#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void rename_file(char *file1,char*file2);
void move_file(char *file1,char *dir_path);

int main( int argc, char* argv[] ) {
  struct stat buf;
  char file1_path[80];
  char file2_path[80];
  char get_answer[10];
  
  
  if(argc !=3){
    printf("Usage : ./mymv [file1] [directory/file2]\n");
    return 0;
  }
  if(strcmp(argv[1],argv[2])==0){
    printf("Two file_names are the same\n");
    printf("Usage : ./mymv [file1] [directory/file2]\n");
  }

  getcwd(file1_path,sizeof(file1_path));
  sprintf(file1_path,"%s/%s",file1_path,argv[1]);
  printf("%s\n",file1_path);

  if(stat(file1_path,&buf)==-1){
  perror("first argument file isn't exist");
  exit(0);
  }

  getcwd(file2_path,sizeof(file2_path));
  sprintf(file2_path,"%s/%s",file2_path,argv[2]);
  printf("%s\n",file2_path);
  
  if(stat(file2_path,&buf)==-1){
    rename_file(file1_path,file2_path);
  }
  else if (S_ISDIR(buf.st_mode)){
    sprintf(file2_path,"%s/%s",file2_path,argv[1]);
    if(stat(file2_path,&buf)==-1){
      move_file(argv[1],file2_path);
      exit(0);
    }
    if(S_ISREG(buf.st_mode) || S_ISDIR(buf.st_mode)){
      printf("mymv: overwrite '%s'[Y/N]?",file2_path);
      gets(get_answer);
    
      if(strcmp(get_answer,"Y")==0){
        unlink(file2_path);
        move_file(argv[1],file2_path);
      }
      if(strcmp(get_answer,"N")==0){
        printf("\nmymv: the '%s' doesn't changed\n",argv[1]);
      }
    }
  }
  else if (S_ISREG(buf.st_mode)){
    printf("mymv: overwrite '%s'[Y/N]?",argv[2]);
    gets(get_answer);
    
    if(strcmp(get_answer,"Y")==0){
      unlink(file2_path);
      rename_file(file1_path,file2_path);
    }
    else if(strcmp(get_answer,"N")==0){
      printf("\nmymv: the '%s' doesn't changed\n",argv[1]);
    }
  }
  
  
  


  //rename();
  return 0;
}


void rename_file(char *file1,char*file2){
  rename(file1,file2);
  return; 
}
void move_file(char *file1,char *dir_path){
  rename(file1,dir_path);
  return; 
}
