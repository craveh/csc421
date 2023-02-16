#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

/*
 * name: pipe-test
 * description: a file to demonstrate how to set up a pipe.
 *
 * last-update:
 *      4 sep 2022 -bjr: template for student
 */

#include "pipe-test.h"

#define USAGE_MSG "usage: %s [-v]\n"
#define PROG_NAME "pipe-test"

#define HELLO_WORLD "hello world!"

// a rare use of globals; name mangle to alert 

int is_verbose_g ;

int main(int argc, char * argv[]) {

	int fd[2] ;
	pid_t c_pid;
	int ch ;

	// my standard options processing code; from the man page
	while ((ch = getopt(argc, argv, "v")) != -1) {
		switch(ch) {
			case 'v':
				is_verbose_g = 1 ;
				break ;
			default:
				printf(USAGE_MSG, PROG_NAME) ;
				return 0 ;
		}
	}
	argc -= optind;
	argv += optind;
	// check no arguments were given
	assert(argc==0) ;

	pipe(fd) ;
	c_pid = fork() ;

	if(c_pid == -1) {
		perror("fork") ;
		return errno ;
	}

	if(!c_pid) {
		// child
		
		char * buf ;
		buf = (char *) malloc(strlen(HELLO_WORLD)+1) ; // add 1 for the null byte
		if (!buf) {
			perror("malloc") ;
			return errno ;
		}
		
		// close the write end of the pipe and
		// copy the read end of the pipe as stdin
		close(fd[1]) ;
		close(STDIN_FILENO) ;
		dup(fd[0]) ;

		// !!! super unsafe call! no way of knowing the length needed for buf!
		gets(buf) ;
		if (is_verbose_g) {
			fprintf(stderr,"(%s,%d): child prints |%s|\n", __FILE__, __LINE__, buf ) ;
		}
		printf("%s\n", buf) ;
		return 0;
	}

	// parent 
	
	// close the read end of the pipe
	// and copy stdout as the read write end of the pipe
	close(fd[0]) ;
	close(STDOUT_FILENO) ;
	dup(fd[1]) ;
	
	if (is_verbose_g) {
		fprintf(stderr,"(%s,%d): child pid %ld\n",  __FILE__, __LINE__, (long) c_pid) ;
	}
	printf("%s\n", HELLO_WORLD ) ;

	return 0;

}

