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
  int shmid,i,shmblocks,blocks_count=0;
  key_t key;
  char *endptr;
  int data[5000],front=-1,flag=0;
  
  memset(data,0,5000);
  if(argc != 2){
    printf("Usage :./consumer [shmblocks]\n");
    exit(0);
  }


  if((key = ftok("testid",'i'))==-1){
    perror("ftok");
    exit(0);
  }


  shmblocks = strtol(argv[1],&endptr,10);
  printf("shmblocks=%d\n",shmblocks);

  if((shmid = shmget(key,shmblocks*sizeof(struct packet),0666))==-1){ 
    perror("shmget");
    exit(0);
  }
  packet_pointer = (struct packet *) shmat(shmid,(char *)NULL,0);

 
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

  shmdt(packet_pointer);
  
  return 0;
  
}

