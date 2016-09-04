#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
//#include <unistd.h>

void list_directory( char *dir_path ,int option);

int main( int argc, char* argv[] ) {
  char **save_path=NULL;
  int i=0;
  int path_count=0;
  int option=0;
  int *path_ptr=&path_count;
  char dir_path[80];
  

  getcwd(dir_path,sizeof(dir_path));
  //printf("%s\n",dir_path);

  

  
  if(argc > 3 || argc <= 0){
    printf("Usage : ./mysl [options] [directory]\n");
    return 0;
  }
  switch(argc){
    case 1:
        list_directory(dir_path,0);
        break;
    case 2:
         save_path = (char **)realloc(save_path,sizeof(char*)*100);
         save_path[path_count] = (char *)malloc(sizeof(char)*(strlen(dir_path)+1));
         strcpy(save_path[path_count],dir_path);
         path_count++;
  
         recursive_search(dir_path,save_path,path_ptr);
         //save_path = (char **)realloc(save_path,sizeof(char*)*(path_count+1));
         save_path[path_count]=NULL;

         if(strcmp(argv[1],"-F")==0){
           list_directory(dir_path,1);
         }
         else if(strcmp(argv[1],"-R")==0){
           while(save_path[i] != NULL){
             list_directory(save_path[i],0);
             i++;
           }
         }
         else if(strcmp(argv[1],"-FR")==0){
           while(save_path[i] != NULL){
             list_directory(save_path[i],1);
             i++;
           }
         } 
         else{
             list_directory(argv[1],0);
         }
         break;
    case 3:
         save_path = (char **)realloc(save_path,sizeof(char*)*100);
         save_path[path_count] = (char *)malloc(sizeof(char)*(strlen(argv[2])+1));
         strcpy(save_path[path_count],argv[2]);
         path_count++;
  
         recursive_search(argv[2],save_path,path_ptr);
         //save_path = (char **)realloc(save_path,sizeof(char*)*(path_count+1));
         save_path[path_count]=NULL;
    
         if(strcmp(argv[1],"-F")==0){
           list_directory(argv[2],1);
         }
         else if(strcmp(argv[1],"-R")==0){
           while(save_path[i] != NULL){
             list_directory(save_path[i],0);
             i++;
           }
         }
         else if(strcmp(argv[1],"-FR")==0){
           while(save_path[i] != NULL){
             list_directory(save_path[i],1);
             i++;
           }
         }
         break;
  }
  
  
 
  
 

  return 0;
}

void recursive_search(char *dir_path,char** save_path,int *path_ptr){
  DIR *dp;
  struct dirent *dir;
  struct stat buf;
  dp=opendir(dir_path);
  char *file_path=NULL;
  int directory_count=0;
  
  
  
  if(dp != NULL){
    while(dir = readdir(dp)){
      if(strcmp(dir->d_name,"..")!=0 && strcmp(dir->d_name,".")!=0){
        
        if(dir->d_type==4){ 
          
          directory_count = *path_ptr+1;
          file_path=(char*)realloc(file_path,strlen(dir_path)+strlen(dir->d_name)+2);
          sprintf(file_path,"%s/%s",dir_path,dir->d_name);
          //save_path = (char **)realloc(save_path,sizeof(char*)*(directory_count));
          save_path[*path_ptr] = (char *)malloc(sizeof(char)*(strlen(file_path)+1));
          strcpy(save_path[*path_ptr],file_path);
          *path_ptr=*path_ptr+1;
          recursive_search(file_path,save_path,path_ptr);
        }
      }        
    }
   
  }
  else{
    perror("Can't open the directory path");
    exit(0);
  }
  close(dp);
  return;
}
void list_directory( char *dir_path ,int option ) {
  DIR *dp;
  struct dirent *dir;
  struct stat buf;
  dp=opendir(dir_path);
  char *file_path=NULL;
  
  printf("\n%s :\n",dir_path);
  if(dp != NULL){
    while(dir = readdir(dp)){
      if(strcmp(dir->d_name,"..")!=0 && strcmp(dir->d_name,".")!=0){
        printf("%s",dir->d_name);
        if(dir->d_type==4){
          if(option ==1){printf("\\");}
          printf("\n");
        }
        if(dir->d_type==8){
          file_path=(char*)realloc(file_path,strlen(dir_path)+strlen(dir->d_name)+2);
          sprintf(file_path,"%s/%s",dir_path,dir->d_name);
          if(stat(file_path,&buf)==-1){perror("Couldn't stat file");}
          else{
            if((buf.st_mode & S_IROTH) && !(buf.st_mode & S_IWOTH) && (buf.st_mode & S_IXOTH) ){
              if(option ==1){printf("*");}
            }
          }
        printf("\n");
        }
      }
    }
  }
  else{
    perror("Can't open the directory path");
    exit(0);
  }
  close(dp);
  
}
