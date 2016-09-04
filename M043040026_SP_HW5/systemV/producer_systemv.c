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
  struct packet *packet_pointer,packet_write;
  int shmid,i,j,k,shmblocks,blocks_count=0;
  key_t key;
  char *endptr;

  if(argc != 2){
    printf("Usage :./proudcer [shmblocks]\n");
    exit(0);
  }

  printf("size of struct:%lu\n",sizeof(struct packet));
  system("touch testid");
  if((key = ftok("testid",'i'))==-1){
    perror("ftok");
    exit(0);
  }
  printf("shmblocks=%ld\n",strtol(argv[1],&endptr,10));
  shmblocks = strtol(argv[1],&endptr,10);

  if((shmid = shmget(key,shmblocks*sizeof(struct packet),IPC_CREAT|0666))==-1){ 
    perror("shmget");
    exit(0);
  }
  packet_pointer = (struct packet *) shmat(shmid,(char *)NULL,0);
  sleep(5);

  for(i=0;i<shmblocks;i++){packet_pointer[i].id=-1;}
  printf("Start Writing ! \n");
  for(i=0 ; i<5000;i++){
    packet_write.id = i;
    memcpy(&packet_pointer[blocks_count],&packet_write,sizeof(struct packet));
    //if(blocks_count==0 || blocks_count==(shmblocks/2) ){
    usleep(200);
    //}
    blocks_count++;
    if(blocks_count == shmblocks){
      blocks_count = 0;
    }
  }
  sleep(5);
  printf("Writing END! \n");
  shmdt(packet_pointer);
  shmctl(shmid,IPC_RMID,(struct shmid_da *)NULL);
  return 0;
  
}

