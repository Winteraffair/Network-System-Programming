/*
 *	zap_servlet does the following :
 *		1) Append the message to an appropriate file
 *		2) Capture statistics and push onto stat stack
 *		3) Dispose of the Servlet
 */

#include "sms.h"

void zap_servlet(Servlet *victim) { /* remove and free memeory */
	FILE *in;
	extern Stats * history;	
	Stats *last = history;	
	char buf[100];
	//(1) Append the message to an appropriate file
	getcwd(buf,sizeof(buf));
	sprintf(buf,"%s%s",buf,"/message");
	chdir(buf);
	if(strlen(victim->dest) > 0 && strlen(victim->message) >0 ){
		victim->dest[strlen(victim->dest)-2]='\0';
		if((in=fopen(victim->dest,"a"))==NULL){
       			perror("fopen");
			exit(1);	
		}
	
		if(fwrite(victim->message,strlen(victim->message),1,in) < 0){
	      	 	perror("write");
			exit(1);
		}
	
		if(fwrite("\n",1,1,in) < 0){
	     	  	perror("write");
			exit(1);
		}
		fclose(in);
	}
	//(2) Capture statistics and push onto stat stack
	if(history == NULL){
		history = (Stats *)malloc(sizeof(Stats));
		history->cust_ip = victim->cust_ip;
		strcpy(history->dest,victim->dest);
	        history->size = strlen(victim->message);
		history->connect = victim->finish - victim->start;
		history->aborted = victim->aborted;
		history->next = NULL;
	}
	else{
		while(last->next != NULL){
			last = last->next;		
		}
		last->next = (Stats *)malloc(sizeof(Stats));
		last = last->next;
		last->cust_ip = victim->cust_ip;
		strcpy(last->dest,victim->dest);
	        last->size = strlen(victim->message);
		last->connect = victim->finish - victim->start;
		last->aborted = victim->aborted;
		last->next = NULL;
	}
	//(3) Dispose of the Servlet
	free(victim);
	return;
}
