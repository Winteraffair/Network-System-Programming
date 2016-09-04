/*
 * lookup4 : This file does no looking up locally, but instead asks
 * a server for the answer. Communication is by message queues.
 * The protocol is : messages of type 1 are meant for the server.
 * The client only reads messages whose type matches their own pid.
 * The message queue key is what is passed as resource.
 */
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include "dict.h"
#include <sys/types.h>

int lookup(Dictrec * sought, const char * resource) {
	static ClientMessage snd;
	ServerMessage rcv;
	static int qid;
	static int pid;
	static int first_time = 1;
        char *endptr;

	if (first_time) { /* open message queue */
		first_time = 0;

		/* Prepare our ClientMessage structure. */
		pid = getpid();
		sprintf(snd.content.id,"%d",pid);
		snd.type = 1L;

		/* Open the message queue.  Use resource pointer value as key.
		 *
		 * Fill in code. */
                
                if((qid=msgget(strtol(resource,&endptr,0),0666))==-1){
                  perror("msgget");
                  exit(1);
                }
	}

	/* Send server the word to be found ; await reply
	 *
	 * Fill in code. */
        strcpy(snd.content.word,sought->word);
        if(msgsnd(qid,&snd,sizeof(Client),0)==-1){
          perror("msgrcv");
          exit(1);
        }
        
        
        if(msgrcv(qid,&rcv,sizeof(rcv.text),pid,0)==-1){
          perror("msgrcv");
          exit(1);
        }
	strcpy(sought->text,rcv.text);

	/* Server returns XXXX when it cannot find request. */
	if (strcmp(rcv.text,"XXXX") != 0)
		return FOUND;

	return NOTFOUND;
}
