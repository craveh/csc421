#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

/*
 * name: exec-test
 * description: a program that prints itself
 *
 * last-update:
 *      4 sep 2022 -bjr: created
 */

#include "exec-test.h"

#define USAGE_MSG "usage: %s [-v]\n"
#define PROG_NAME "exec-test"

// a rare use of globals; name mangle to alert 

int is_verbose_g ;

int main(int argc, char * argv[]) {

	char * buf ;
	int ch ;

	buf = (char *) malloc(strlen(argv[0])+3) ;
	strcpy(buf,argv[0]) ;
	strcat(buf,".c") ;

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
 
	if (is_verbose_g) {
		fprintf(stderr, "(%s,%d): %s\n",  __FILE__, __LINE__, buf) ;
	}
	execlp("cat", buf, buf, (char *)NULL) ;
	perror("execlp") ;
	return errno ;

}

