/*
 * lookup9 : does no looking up locally, but instead asks
 * a server for the answer. Communication is by Internet UDP Sockets
 * The name of the server is passed as resource. PORT is defined in dict.h
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	static int sockfd;
	static struct sockaddr_in server;
	struct hostent *host;
	static int first_time = 1;
	int len =sizeof(server);
	if (first_time) {  /* Set up server address & create local UDP socket */
		first_time = 0;

		/* Set up destination address.
		 * Fill in code. */
		if((host = gethostbyname("localhost"))==NULL){
			perror("gethostname");
			exit(1);		
		}
        	server.sin_family = AF_INET;
		server.sin_port = htons(33101);
		memcpy((char *)&server.sin_addr,host->h_addr,host->h_length);
		/* Allocate a socket.
		 * Fill in code. */
        	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1){
			perror("socket");
			exit(1);
       		}
	}

	/* Send a datagram & await reply
	 * Fill in code. */
	if(sendto(sockfd,sought,sizeof(Dictrec),0,(struct sockaddr *)&server,len)==-1){
		perror("sendto");
		exit(1);
	}
	if(recvfrom(sockfd,sought,sizeof(Dictrec),0,(struct sockaddr *)&server,&len)==-1){
		perror("recvfrom");
		exit(1);		
	}
	if (strcmp(sought->text,"XXXX") != 0) {
		return FOUND;
	}

	return NOTFOUND;
}
