#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>
struct packet{
  int id;
  short dataShort[5];
  long dataLong[5];
  double dataDouble[5];
  char dataByte[6];
}__attribute__((packed));;

int main(int argc , char *argv[]){
  struct packet *packet_pointer,packet_reader;
  int fd,shmid,i,shmblocks,blocks_count=0;
  char *endptr;
  caddr_t addr;
  int data[5000],front=-1,flag=0;
  
  memset(data,0,5000);
  if(argc != 2){
    printf("Usage :./consumer [shmblocks]\n");
    exit(0);
  }


  
  if((fd=open("testid",O_RDWR,0666))==-1){
    perror("open");
    exit(0);
  }
  shmblocks = strtol(argv[1],&endptr,10);
  printf("shmblocks=%d\n",shmblocks);
  if(ftruncate(fd,(off_t)(shmblocks*sizeof(struct packet)))==-1){
   perror("ftruncate");
    exit(0); 
  }
  if((addr = mmap(NULL,shmblocks*sizeof(struct packet),PROT_READ|PROT_WRITE,MAP_SHARED,fd,(off_t)0))==MAP_FAILED){ 
    perror("mmap");
    exit(0);
  }

  packet_pointer=(struct packet *)addr;

 
  for(i=0;i<shmblocks;i++){packet_pointer[i].id=-1;}
  printf("Start Listening ! \n");
  while(flag == 0){
    for(i=0;i<shmblocks;i++){
      if(packet_pointer[i].id>=0){
        if(packet_pointer[i].id==4999){flag=1;}
        memcpy(&packet_reader,&packet_pointer[i],sizeof(struct packet));
        data[packet_reader.id]=1;
      } 
    }
  }
  front = 0;
  for(i=0;i<5000;i++){
    if(data[i]==1){
      front++;
    } 
  }  
  printf("Lost data :%d\n",5000-front);
  
  
  return 0;
  
}

