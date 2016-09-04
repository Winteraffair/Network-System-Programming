/*
 *	sms_server.c :
 *	1. All global variables are defined in sms.h
 *	2. main, which does the following
 *		a) Initialize the circular list
 *		b) Fire off threads for collect_garb and listen_port
 *		c) Run the menu
 */

#include "sms.h"
Servlet *door=NULL;
Pending *pending_stack=NULL;
sem_t garbage_time;
Stats * history=NULL;
pthread_attr_t attr;

Menu_item menu_list[]={ {"1",list_conn},
		   {"2",list_stats},
		   {"3",zero_stats},
		   {"4",zap_stale},
		   {NULL,NULL}
		 };
void main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in server;
	int len = sizeof(server);
	pthread_t thread_id; 
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
	  perror("socket");
	  exit(1);	
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(sockfd,(struct sockaddr *)&server,len)==-1){
	  perror("bind");
	  exit(1);	
	}
	//pthread_detach
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	//listen port thread
	if(pthread_create(&thread_id,&attr,listen_port,(void *)&sockfd)){
	  perror("pthread");
	  exit(1);
	}
	
	if(sem_init(&garbage_time,0,0)==-1){
	  perror("sem_init");
	  exit(1);	
	}
	//collect garbage thread
	if(pthread_create(&thread_id,NULL,collect_garb,(void *)&sockfd)){
	  perror("pthread");
	  exit(1);
	}
	//while(1){}
	menu(menu_list);
	
}
