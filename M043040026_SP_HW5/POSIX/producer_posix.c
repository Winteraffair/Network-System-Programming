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
  int fd ,shmid,i,j,k,shmblocks,blocks_count=0;
  caddr_t addr;
  char *endptr;

  if(argc != 2){
    printf("Usage :./proudcer [shmblocks]\n");
    exit(0);
  }
  printf("sizeofstruct : %lu\n",sizeof(struct packet));

  if((fd=open("testid",O_RDWR | O_CREAT,0666))==-1){
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

  printf("Writing End ! \n");
  sleep(5);
  munmap(addr ,shmblocks*sizeof(struct packet));
  //shm_unlink(addr);
  return 0;
  
}

