/*
 *	list_conn looks for live connections
 *	It reports the total number and the age of the oldest
 */

#include "sms.h"

void list_conn(void) {	/* list number of current connections */
	extern Servlet *door;
	Servlet *count=door;
	time_t tm;
	int num=1;
	//printf("list_conn !!\n");
	//printf("< List Number of current connections > :");
	
	if(count == NULL){
		printf("There are 0 live connections\n");
		printf("There are oldest began 0 sec ago\n");		
		return;
	}
	while(count->next != NULL){
	  	num++;
		count = count->next;
	}
	
	time(&tm);
	printf("There are %d live connections\n",num);
	printf("There are oldest began %ld sec ago\n",tm - count->start);	

	return;
	
	
}
