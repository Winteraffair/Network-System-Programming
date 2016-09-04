/*
 * lookup3 : This file does no looking up locally, but instead asks
 * a server for the answer. Communication is by named pipes.
 * The server sits listening on a "well-known" named pipe
 * (this is what is passed to lookup3 as resource)
 * The Client sets up a FIFO for reply, and bundles the FIFO
 * name with the word to be looked up. (See Client in dict.h)
 * Care must be taken to avoid deadly embrace (client & server
 * both waiting for something which can never happen)
 */

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "dict.h"

static Client me;

void cleanup(void) {
	/* Delete named pipe from system. 
	 *
	 * Fill in code. */
        system("rm myfifo");
        exit(0);
}

int lookup(Dictrec * sought, const char * resource) {
	static int write_fd;
	int read_fd;
	static int first_time = 1;
        

	if (first_time) {
		first_time = 0;

		/* Open existing named pipe for client->server communication.
		 *
		 * Fill in code. */
                if((write_fd = open(resource,O_WRONLY))==-1){
                  perror("open");
                  exit(1); 
                }
		/* Create temporary named pipe for server->client communication. */
		umask(0);
		tmpnam(me.id);
		/* Fill in code. */
                
                if(mkfifo(me.id,0666)==-1){
                  perror("open");
                  exit(1); 
                }
		/* Register cleanup handler.
		 *
		 * Fill in code. */
               if(signal(SIGINT,cleanup)==SIG_ERR){
                 perror("signal");
                 exit(1);
               }
               if(signal(SIGQUIT,cleanup)==SIG_ERR){
                 perror("signal");
                 exit(1);
               }

	}

	/* Send server the word to be found ; await reply */
	strcpy(me.word,sought->word);
	/* Fill in code. */
        write(write_fd,&me,sizeof(Client));
	/* Open the temporary named pipe to get the answer from it.
	 *
	 * Fill in code. */
        if((read_fd = open(me.id,O_RDONLY))==-1){
          perror("open");
          exit(1); 
        }
	/* Get the answer.
	 *
	 * Fill in code. */
        read(read_fd,sought->text,sizeof(sought->text));
	/* Close the temporary named pipe as done.
	 *
	 * Fill in code. */
        close(read_fd);
	/* If word returned is not XXXX it was found. */
	if (strcmp(sought->text,"XXXX") != 0)
		return FOUND;

	return NOTFOUND;
}
