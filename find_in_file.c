#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "finderBM.h"


static const char * const exit_str = "exit\n" ;
static const char * const yes_str = "YES\n" ;
static const char * const no_str = "NO\n" ;
static const char * const arg_error = "Argument error\n" ;
static const int MAX_TEXT_SIZE = 128 * 1024 * 1024;
static const int MAX_PATTERN_SIZE = 64 * 1024;

int equals_str_in_al(const char* str_one,const char* str_two) {
	int i;	
	for(i=0; (str_one[i]>=AOFFSET)&&(str_one[i]>=AOFFSET); i++) {
		if(str_one[i]!=str_two[i])
			return 0;
	}
	if((str_one[i]<AOFFSET)&&(str_one[i]<AOFFSET)) {
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	
	char* text;
 	char* pattern;
	int file_fd;
	int text_length;
	int no_str_length;
	int yes_str_length;
	int pattern_length;
	if(argc!=2) { 
		fprintf(stderr,arg_error);
		exit(EXIT_FAILURE);
	}
	if(-1==(file_fd=open(argv[1],O_RDONLY))) {
		fprintf(stderr,"%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	if(NULL==(text=(char*)malloc(MAX_TEXT_SIZE))) { 
		fprintf(stderr,"%s\n",strerror(ENOMEM));
		exit(EXIT_FAILURE);
	}
	if(NULL==(pattern=(char*)malloc(MAX_PATTERN_SIZE))) { 
		fprintf(stderr,"%s\n",strerror(ENOMEM));;
		exit(EXIT_FAILURE);
	}
	yes_str_length=strlen(yes_str);
	no_str_length=strlen(no_str);
	text_length=read(file_fd,text,MAX_TEXT_SIZE);		
	while(1)
	{	
		int ret_val;
		pattern_length=read(STDIN_FILENO,pattern,MAX_PATTERN_SIZE)-1;
		if(equals_str_in_al(pattern,exit_str))
			exit(EXIT_SUCCESS);
		ret_val=findBM(text,pattern,text_length,pattern_length);
		if(ret_val>=0) {
			write(STDOUT_FILENO,yes_str,yes_str_length);
			continue;
		}
		if(ret_val==-1) {
			write(STDOUT_FILENO,no_str,no_str_length);
			continue;
		}
		if(ret_val==-2) {
		fprintf(stderr,"%s\n",strerror(ENOMEM));
		exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}

