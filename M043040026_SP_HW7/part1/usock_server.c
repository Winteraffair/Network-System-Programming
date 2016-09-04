/*
 * usock_server : listen on a Unix socket ; fork ;
 *                child does lookup ; replies down same socket
 * argv[1] is the name of the local datafile
 * PORT is defined in dict.h
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>
#include "dict.h"

int main(int argc, char **argv) {
    struct sockaddr_un server;
    int sd,cd,n,len;
    Dictrec tryit;
    len = sizeof(server);
    if (argc != 3) {
      fprintf(stderr,"Usage : %s <dictionary source>"
          "<Socket name>\n",argv[0]);
      exit(errno);
    }

    /* Setup socket.
     * Fill in code. */
    if((sd = socket(AF_UNIX,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
    }
    /* Initialize address.
     * Fill in code. */
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path,argv[2]);
    unlink(argv[2]);
    if(bind(sd,(struct sockaddr*)&server,len)==-1){
		perror("bind");
		exit(1);
    }
    /* Name and activate the socket.
     * Fill in code. */
    if(listen(sd,10)==-1){
    		perror("listen");
		exit(1);
    }
    /* main loop : accept connection; fork a child to have dialogue */
    for (;;) {
		/* Wait for a connection.
		 * Fill in code. */
		if((cd = accept(sd,(struct sockaddr*)&server,&len))==-1){
			perror("accept");
			exit(1);
		}
		/* Handle new client in a subprocess. */
		switch (fork()) {
			case -1 : 
				DIE("fork");
			case 0 :
				close (sd);	/* Rendezvous socket is for parent only. */
				/* Get next request.
				 * Fill in code. */
				while (1) {
					n= read(cd,&tryit,sizeof(Dictrec));
					/* Lookup request. */
					switch(lookup(&tryit,argv[1]) ) {
						/* Write response back to client. */
						case FOUND: 
							/* Fill in code. */
							write(cd,&tryit,sizeof(Dictrec));
							break;
						case NOTFOUND: 
							/* Fill in code. */
							strcpy(tryit.text,"XXXX");
							//printf("%s\n",tryit.text);
							write(cd,&tryit,sizeof(Dictrec));
							break;
						case UNAVAIL:
							DIE(argv[1]);
					} /* end lookup switch */

				} /* end of client dialog */

				/* Terminate child process.  It is done. */
				exit(0);

			/* Parent continues here. */
			default :
				close(cd);
				break;
		} /* end fork switch */
    } /* end forever loop */
} /* end main */
