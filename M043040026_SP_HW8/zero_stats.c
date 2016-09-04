/*
 *	zero_stats just frees the stats stack (means "history")
 */

#include "sms.h"
void free_stats(Stats *);

void zero_stats(void) { /* re-start statistics */
	extern Stats * history;	
	//Stats *free_stat = history;
	
	if(history == NULL){
		printf("History is NULL now!!\n");
		return;	
	}
	else{
	
		free_stats(history);
		history = NULL;
	}

	printf("History has been deleted !!\n");
	return;
}

void free_stats(Stats * head){
	Stats *tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		free(tmp);
	}
	

	return;
}
