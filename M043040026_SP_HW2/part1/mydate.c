#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>

int main(void){
	struct tm *timeinfo;
	time_t t;
	char timestr[40];
	time(&t);

	timeinfo=localtime(&t);
 	strftime(timestr,40,"%b %d(%a),%Y  %I:%M %p",timeinfo);
	puts(timestr);

	

	exit(0);
}
