/*
 *	collect_garb :
 *	This function has the following responsibilities :
 *		1) Call zap_servlet
 *		2) Remove the head of the pending tray
 *	collect_garb is activated by the garbage_time semaphore
 */

#include "sms.h"

void *collect_garb(void *info) { /* garbage collector */
	extern sem_t garbage_time;
	extern Pending *pending_stack;
	Pending *tmp = pending_stack;
	//(1) Call zap_servlet
	
	while(1){
		sem_wait(&garbage_time); // sem_t -1 , wait sem_post
		zap_servlet(pending_stack->head);
		//(2) Remove the head of the pending tray
		pending_stack = pending_stack->tail;;
		free(tmp);

	}
	return NULL;
}
