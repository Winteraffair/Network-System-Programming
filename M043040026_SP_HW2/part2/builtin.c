/*
 * builtin.c : check for shell built-in commands
 * structure of file is
 * 1. definition of builtin functions
 * 2. lookup-table
 * 3. definition of is_builtin and do_builtin
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/utsname.h>
#include "shell.h"

/****************************************************************************/
/* builtin function definitions                                             */
/****************************************************************************/
static void bi_builtin(char ** argv);	/* "builtin" command tells whether a command is builtin or not. */
static void bi_cd(char **argv) ;		/* "cd" command. */
static void bi_echo(char **argv);		/* "echo" command.  Does not print final <CR> if "-n" encountered. */
static void bi_hostname(char ** argv);	/* "hostname" command. */
static void bi_id(char ** argv);		/* "id" command shows user and group of this process. */
static void bi_pwd(char ** argv);		/* "pwd" command. */
static void bi_quit(char **argv);		/* quit/exit/logout/bye command. */




/****************************************************************************/
/* lookup table                                                             */
/****************************************************************************/

static struct cmd {
  	char * keyword;					/* When this field is argv[0] ... */
  	void (* do_it)(char **);		/* ... this function is executed. */
} inbuilts[] = {
  	{ "builtin",    bi_builtin },   /* List of (argv[0], function) pairs. */

    /* Fill in code. */
    { "echo",       bi_echo },
    { "quit",       bi_quit },
    { "exit",       bi_quit },
    { "bye",        bi_quit },
    { "logout",     bi_quit },
    { "cd",         bi_cd },
    { "pwd",        bi_pwd },
    { "id",         bi_id },
    { "hostname",   bi_hostname },
    {  NULL,        NULL }          /* NULL terminated. */
};


static void bi_builtin(char ** argv) {
	/* Fill in code. */
	struct cmd *command;
	if(argv[1]!=NULL){
	    for(command = inbuilts ; command->keyword != NULL ; command++){
	        if((strcmp(command->keyword,argv[1])) == 0 ){
		    printf("%s is a builtin feature\n",argv[1]);
		    return;
		}
	    }
	}
	printf("%s is NOT a builtin feature\n",argv[1]);
	return;
}

static void bi_cd(char **argv) {
	/* Fill in code. */
	int count_arg=1;
	char *blank=" ";
	if(argv[1]!=NULL){
	    chdir(argv[1]);
	}
	else{
	    printf("Can't change the workplace \n");
	}
	return;
}

static void bi_echo(char **argv) {
	/* Fill in code. */
	int i=0,k=1;
	int j = *argv[2] - '0';
	while(argv[i]!=NULL){
	    i++;
	}
	if(strcmp(argv[1],"-n")==0){
	    if((j+2) <= (i-1)){
	        printf("%s ",argv[j+2]);
	    }
	}
	else{
	    while(argv[k]!=NULL){
	        printf("%s ",argv[k]);
		k++;
	    }
	}
	printf("\n");
}

static void bi_hostname(char ** argv) {
	/* Fill in code. */
	struct utsname uts;

	if(uname(&uts) == -1){
	    perror("myuname.c:main:uname");
	    exit(0);
	}

	printf("Hostname : %s\n",uts.nodename);
}

static void bi_id(char ** argv) {
 	/* Fill in code. */
	struct passwd *getuname = getpwuid(getuid()); 
	struct group *getgname = getgrgid(getgid());
	printf("UserID = %d(%s) , GroupID = %d(%s)\n", getuname->pw_uid, getuname->pw_name, getgname->gr_gid, getgname->gr_name);
}

static void bi_pwd(char ** argv) {
	/* Fill in code. */
	printf("%s\n",getcwd(NULL,0));
}

static void bi_quit(char **argv) {
	exit(0);
}


/****************************************************************************/
/* is_builtin and do_builtin                                                */
/****************************************************************************/

static struct cmd * this; /* close coupling between is_builtin & do_builtin */

/* Check to see if command is in the inbuilts table above.
Hold handle to it if it is. */
int is_builtin(char *cmd) {
	struct cmd *tableCommand;

  	for (tableCommand = inbuilts ; tableCommand->keyword != NULL; tableCommand++)
    	if (strcmp(tableCommand->keyword,cmd) == 0) {
      		this = tableCommand;
      		return 1;
    	}
  return 0;
}


/* Execute the function corresponding to the builtin cmd found by is_builtin. */
int do_builtin(char **argv) {
	this->do_it(argv);
}
