/*
 *	menu :
 *	A generalised menu function
 *	The argument is base of an array of Menu_item, which
 *	must be suitably NULL-teminated
 */

#include "sms.h"

void menu(Menu_item *menu) {
	char get_options[10];
	Menu_item *cmd = menu;

	while(1){
		printf("\n      1) List Number of current connections\n");
		printf("      2) Summarize statistic\n");
		printf("      3) Restart statistic\n");
		printf("      4) Zap stale clients and free memory\n\n");
		
		
		printf("Please Choose(1 - 4):");
		memset(get_options,'\0',10);
		scanf("%s",get_options);
		cmd = menu;

		while(cmd->chat != NULL){
			if(strcmp(cmd->chat,get_options)==0){
				break;			
			}
			cmd ++;
		}
		if(cmd->chat == NULL){
			printf("Wrong command number !\n");		
		}
		else{
			cmd->act();
		}
	
	}
}
