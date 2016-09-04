/*
 *	listen_port :
 *	The body of the thread which listens on a particular
 *	port number (it's sole argument).
 *	Whenever a new connection is requested it calls
 *	make_servelet_list and then fires off a new thread running.
 *	It must set two fields in the Servlet structure :
 *		1) fd
 *		2) start
 */

#include "sms.h"

void make_servelet_list(int,pthread_t,int);

void *listen_port(void *info) { /* body of port listener */
	extern pthread_attr_t attr;
	int sockfd = *(int *)info;
	int sockfd_client,len = sizeof(struct sockaddr_in);
	struct sockaddr_in client;
	pthread_t thread_id;
	if(listen(sockfd,20)==-1){
	  perror("listen");
	  exit(1);	
	}
	while(sockfd_client = accept(sockfd,(struct sockaddr *)&client,&len)){
	  if(pthread_create(&thread_id,&attr,serve_client,(void *)&sockfd_client)){
	    perror("pthread");
	    exit(1);
	  }

	  make_servelet_list(sockfd_client,thread_id,client.sin_addr.s_addr);
	}
	
	return NULL;
}

void make_servelet_list(int fd,pthread_t thread_id,int cust_ip) {
	extern Servlet *door;
	Servlet *start;
	if(door == NULL){
	  door = malloc(sizeof(Servlet));
	  door->fd = fd;
	  door->thread = thread_id;
	  door->cust_ip = (int)cust_ip;
	  door->prev = NULL;
	  door->next = NULL;
	  time(&(door->start));
	  door->aborted = 0;
	  memset(door->dest,'\0',MAXDEST);
	  memset(door->message,'\0',SHORTMESS);
	}
	else{
	  start = door;
	  while(start->next != NULL){
	  	start = start->next;
	  }
	  start->next = malloc(sizeof(Servlet));
	  start->next->prev = start;
	  start = start->next;
	  start->fd = fd;
	  start->thread = thread_id;
	  start->cust_ip = (int)cust_ip;
	  time(&(start->start));
	  start->aborted = 0;
	  start->next = NULL;
	  memset(start->dest,'\0',MAXDEST);
	  memset(start->message,'\0',SHORTMESS);

	}
	
}
