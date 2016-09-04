/*
 *	serve_client :
 *	The body of the thread of which one is started for each client.
 *	It receives as its argument a pointer to Servlet of which  precisely
 *	two fields : the start time and socket descriptor are non-null.
 *	The main duty of this thread is to conduct a dialog with the client.
 *	Correct termination is the string "---" in a line by itself.
 *	Incorrect termination and over verbose clients must the suitably handled.
 */

#include "sms.h"

void *serve_client(void *info) { /* body of servlet thread */
	int sockfd = *(int *)info;
	char buf[SHORTMESS],message[SHORTMESS];
	extern Servlet *door;
	Servlet *client=door;
	//search Servlet_list
	while(client->fd != sockfd){
	  client = client->next;
	}
	//recv dest
	memset(buf,'\0',SHORTMESS);
	strcpy(buf,"Destination :");
	if(send(sockfd,buf,sizeof(buf),0)==-1){
	  perror("send");
	  exit(1);	
	}

	memset(buf,'\0',SHORTMESS);
	while(recv(sockfd,buf,sizeof(buf),0) > 0){
	  if(buf[MAXDEST] != '\0'){
	    memset(buf,'\0',SHORTMESS);
	    strcpy(buf,"Your Dest is too long !\nDestination :");
	    if(send(sockfd,buf,sizeof(buf),0)==-1){
	      perror("send");
	      exit(1);	
	    }    
	  }
	  else{
	    strcpy(client->dest,buf);
	    break;
	  }
	  memset(buf,'\0',SHORTMESS);
	}

	//recv message
	memset(buf,'\0',SHORTMESS);
	strcpy(buf,"Now write your message(finish with ---):\n-->");
	if(send(sockfd,buf,sizeof(buf),0)==-1){
	  perror("send");
	  exit(1);	
	}

	memset(buf,'\0',SHORTMESS);
	memset(message,'\0',SHORTMESS);
	while(recv(sockfd,buf,sizeof(buf),0) > 0){
	  if((strlen(buf) + strlen(message)) > (SHORTMESS-1)){
	    memset(buf,'\0',SHORTMESS);
	    memset(message,'\0',SHORTMESS);
	    strcpy(buf,"Your message is too long !\nwrite your message again(finish with ---):");
	    if(send(sockfd,buf,sizeof(buf),0)==-1){
	      perror("send");
	      exit(1);	
	    }	    
	  }
	  else if(strcmp(buf,"---\r\n") == 0){
	    //printf("%s\n",message);
	    strcpy(client->message,message);
	    memset(buf,'\0',SHORTMESS);
	    strcpy(buf,"Bye Bye !\n");
	    if(send(sockfd,buf,sizeof(buf),0)==-1){
	      perror("send");
	      exit(1);	
	    }	
	    fflush(stdout);
	    disconnect(client);
	    return NULL;
	  }
	  else{
	    sprintf(message,"%s%s",message,buf);
	    memset(buf,'\0',SHORTMESS);	  
	  }
	
	}

	
	close(sockfd);
	return NULL;
}
