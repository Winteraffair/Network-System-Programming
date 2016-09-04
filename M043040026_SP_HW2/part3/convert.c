/*
 * convert.c : take a file in the form 
 *  word1
 *  multiline definition of word1
 *  stretching over several lines, 
 * followed by a blank line
 * word2....etc
 * convert into a file of fixed-length records
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#include "dict.h"
#define BIGLINE 512

int main(int argc, char **argv) {
	FILE *in;
	FILE *out;        /* defaults */
	char *line=NULL;
	static Dictrec dr, blank , nocopy;
	size_t len=0;
	size_t read;
	int first=0,check=0;
	int cyclecount=0;
	char *blankline = "\n";
	int lenofword,lenoftext;
	
	
	/* If args are supplied, argv[1] is for input, argv[2] for output */
	if (argc==3) {
		if ((in =fopen(argv[1],"r")) == NULL){DIE(argv[1]);}
		if ((out =fopen(argv[2],"w")) == NULL){DIE(argv[2]);}	
	}
	else{
		printf("Usage: convert [input file] [output file].\n");
		return -1;
	}

	/* Main reading loop : read word first, then definition into dr */

	/* Loop through the whole file. */
	while (!feof(in)) {
		
		/* Create and fill in a new blank record.
		 * First get a word and put it in the word field, then get the definition
		 * and put it in the text field at the right offset.  Pad the unused chars
		 * in both fields with nulls.
		 */
		strcpy(nocopy.word,dr.word);
		strcpy(nocopy.text,dr.text);
		
		for(lenofword = 0;lenofword <= sizeof(dr.word)-1;lenofword++){
		    dr.word[lenofword]=NULL;
		}
		for(lenoftext = 0;lenoftext <= sizeof(dr.text)-1;lenoftext++){
		    dr.text[lenoftext]=NULL;
		}
		
		/* Read word and put in record.  Truncate at the end of the "word" field.
		 *
		 * Fill in code. */
		if((read = getline(&line,&len,in)) != -1){
		    strcpy(dr.word,line);  
		 
		      
		}
		/*for(lenofword = (strlen(line)+2);lenofword <= sizeof(dr.word);lenofword++){
		    dr.word[lenofword]=NULL;
		}*/
		

		/* Read definition, line by line, and put in record.
		 *
		 * Fill in code. */
		while(check == 0 && cyclecount <= 10){
		    if(first==1 && check == 0 ){
			if((read = getline(&line,&len,in)) != -1){
			    if(strcmp(line,"\n")==0 ){
			        check=1;
			    }
			
		            else {
			        strcat(dr.text,line);
			    }
			}
			
			
		    }
		    if(first==0 && check == 0){
			if((read = getline(&line,&len,in)) != -1 ){
			    if(strcmp(line,"\n")==0 ){
			        check=1;
			    }
			
		            else {
			        strcpy(dr.text,line);
				first++;
			    }
			}
		   
		    }
		    cyclecount++;       
		}
		
		/*for(lenoftext = (strlen(line)+2);lenoftext <= sizeof(dr.text);lenoftext++){
		    dr.text[lenoftext]=NULL;
		}*/
		first = 0;
		check = 0;
		cyclecount=0;
		//printf("%s\n%s",dr.word,dr.text);

		/* Write record out to file.
		 *
		 * Fill in code. */
		//fwrite(&dr,sizeof(Dictrec),1,out);
		//fwrite(&(dr.word),sizeof(char)*(lenofword+1),1,out);
		//fwrite(&(dr.text),sizeof(char)*(lenoftext+1),1,out);
		if(strcmp(nocopy.word,dr.word) != 0){
		fwrite(&dr,sizeof(Dictrec),1,out);
		/*fprintf(out,&(dr.word));
		fprintf(out,&(dr.text));
		fprintf(out,blankline);*/	
		}
		
	}

	fclose(in);
	fclose(out);
	return 0;
}
