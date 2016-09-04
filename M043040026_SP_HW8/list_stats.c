/*
 *	list_stats produces a report from the stats heap
 */

#include "sms.h"

void list_stats(void) { /* Summmarise statistics */
	extern Stats * history;
	Stats *count = history;
	double num=0,time=0,size=0,abort=0;

	//printf("list_stats !!\n");
	

	if(count == NULL){
		printf("No connection on record\n");
		return;
	}
	while(count != NULL){
		num++;
		time = time + count->connect;
		size = size + count->size;
		if(count->aborted == 1){abort++;}
		count = count->next;
	}
	
	printf("%.0f connections\n",num);
	printf("%.1f%% aborted\n",(abort / num)*100);
	printf("average connect = %.1f sec\n",time / num);
	printf("average size = %.1f byte\n",size / num);

	return;
	
}
