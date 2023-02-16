#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

/*
 * name: my-word-count
 * description: project 1, csc421 (231)
 *		this project is essentially cat _filename_ | wc _options_
 *
 * last-update:
 *		4 sep 2022 -bjr: template for student
 */

#include "my-word-count.h"

#define USAGE_MSG "usage: %s [-vclmw] _filename_\n"
#define PROG_NAME "my-word-count"


#define HELLO_WORLD "hello world!"

#define CAT_PROGRAM "cat"
#define WC_PROGRAM "wc"

#define MAXLINES 255

// a rare use of globals; name mangle to alert 
int is_verbose_g ;

int main(int argc, char * argv[]) {

	// write code here
	int fd[2];
	pid_t c_pid;
	char * buf;
	char * options;
	char * filename;
	int ch;
	int is_c, is_l, is_m, is_w;

	is_c = is_l = is_m = is_w = 0;
	
	buf = (char *) malloc(strlen(argv[0])+2) ;
	strcpy(buf,argv[0]) ;
	strcat(buf,".c") ;

	options = (char *) malloc(6);
	strcpy(options, "-");


	// my standard options processing code; from the man page
	while ((ch = getopt(argc, argv, "vwmcl")) != -1) {
		switch(ch) {
			case 'v':
				is_verbose_g = 1;
				break;
			case 'c':
				if(is_c){
					break;
				}
				is_c = 1;
				strcat(options, "c");
				break;
			case 'l':
				if(is_l){
					break;
				}
				is_l = 1;
				strcat(options, "l");
				break;
			case 'w':
				if(is_w){
					break;
				}
				is_w = 1;
				strcat(options, "w");
				break;
			case 'm':
				if(is_m){
					break;
				}
				is_m = 1;
				strcat(options, "m");
				break;
			case ':':
				printf("need an option");
				break;
			case '?':
				printf("unkown option %c\n", optopt);
				break;
			default:
				printf(USAGE_MSG, PROG_NAME) ;
				return 0 ;
		}
	}
	filename = argv[optind];

	if(strcmp(options, "-") == 0){
		strcat(options, "lwc");
	}

	strcat(options, "\0");
	optind += 1;
	argc -= optind;
	argv += optind;
	// check no arguments were given
	assert(argc==0) ;

 
	if (is_verbose_g) {
		printf("%s\n", filename);
		fprintf(stderr, "(%s,%d): %s\n",  __FILE__, __LINE__, buf) ;
		printf("Options selected test: %s\n", options);
	}

	
	pipe(fd) ;
	c_pid = fork() ;

	if(c_pid == -1) {
		perror("fork") ;
		return errno ;
	}

	if(!c_pid) { //CHILD
		
		// close the write end of the pipe and copy the read end of the pipe as stdin
		close(fd[1]);
		close(STDIN_FILENO);
		dup(fd[0]);

		execlp("wc", options, options, (char *)NULL);
		perror("execlp");

		return errno ;

	}

	// PARENT 
	
	// close the read end of the pipe
	// and copy stdout as the read write end of the pipe
	close(fd[0]) ;
	close(STDOUT_FILENO) ;
	dup(fd[1]) ;
	
	if (is_verbose_g) {
		fprintf(stderr,"(%s,%d): child pid %ld\n",  __FILE__, __LINE__, (long) c_pid) ;
	}
	
	execlp("cat", filename, filename, (char *)NULL) ;
	perror("execlp") ;
	return errno ;

}

