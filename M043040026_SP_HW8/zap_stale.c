/*
 *	zap_stale does the following
 *	for each stale client found
 *		1) Set abort flag
 *		2) Kill the thread
 *		3) Call disconnect
 */

#include "sms.h"

void zap_stale(void) {	/* call disconnect when needed */
	extern Servlet *door;
	Servlet *count = door;
	int stale_num=0,num=0;
	time_t tm;
	char buf[SHORTMESS];
	
	printf("How many seconds counts as stale ?  ");
	scanf("%d",&stale_num);
	
	if(count == NULL){
		printf("There is no connection now ! \n");
		return;	
	}
	while((count = get_stale(stale_num)) != NULL){
		num++;
		//1) Set abort flag
		count->aborted = 1;
		//2) Kill the thread
		pthread_cancel(count->thread);
		//3) Call disconnect
		memset(buf,'\0',SHORTMESS);
		strcpy(buf,"Sorry time is up\n");
		if(send(count->fd,buf,sizeof(buf),0)==-1){
	          perror("send");
	          exit(1);	
	        }   
		disconnect(count);
		break;
	}

	
	//printf("%d stale connections have been deleted\n",num);
	if(num == 1){
		printf("a stale connection has been deleted\n");
	}
	else
		printf("NO stale connection\n");
	return;
	
}
