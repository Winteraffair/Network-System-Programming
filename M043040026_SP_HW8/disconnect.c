/*
 *	disconnect is passed a pointer to a Servlet
 *	It should perform the following :
 *		1) Take the servlet out of the circular list
 *		2) Close the socket connection
 *		3) Create a Pending item and push pending stack
 *		4) Alert the garbage collector
 */

#include "sms.h"

void disconnect(Servlet *done) {
	Servlet *prevone,*nextone;
	extern Servlet *door;
	extern Pending *pending_stack;
	extern sem_t garbage_time;
	Pending *pending_place;
	//(1) Take the servlet out of the circular list
	prevone = done->prev;
	nextone = done->next;
	if(prevone == NULL){
	  	door = nextone;
	}
	else{
		prevone->next = nextone;
		if(nextone != NULL){
			nextone->prev = prevone;
		}	
	}

	//(2) Close the socket connection
	time(&(done->finish));
	close(done->fd);

	//(3) Create a Pending item and push pending stack
	if(pending_stack == NULL){
	  	pending_stack = (Pending *)malloc(sizeof(Pending));
		pending_stack->head = done;
		pending_stack->tail = NULL;
	}
	else{
		pending_place = pending_stack;
	  	while(pending_place->tail != NULL){
			pending_place = pending_place->tail;
		}
		pending_place->tail = (Pending *)malloc(sizeof(Pending));
		pending_place = pending_place->tail;
		pending_place->head = done;
		pending_place->tail = NULL;
	}
	//(4) Alert the garbage collector

	sem_post(&garbage_time);

}
