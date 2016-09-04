/*
 *	get_stale merely locates a stale servlet
 *	It returns a valid pointer on success
 *	It returns NULL if no stale servlets are found
 */

#include "sms.h"

Servlet *get_stale(int secs) { /* find ONE stale client */
	extern Servlet *door;
	Servlet *count = door;
	time_t tm;


	while(count != NULL){
		time(&tm);
	  	if((tm - count->start) > secs){
			return count;		
		}
		count = count->next;
	}
	return NULL;
}
