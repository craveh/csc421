#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <ctype.h>

/*
 * demonstration program for fork and std file desc
 * csc421 (231)
 * last-update:
 * 	2 sep 2022 -bjr: created
 *
 */

int main(int argc, char * argv[]){

	printf("The program has the process fork, and both parent and child read from stdin and write to stdout.\n") ;
	printf("Type characters and newlines; end with one or two control-D ...\n\n") ;

	if (fork()==0) {
		int c = 0 ; 
		// child
		while (c!=EOF) {
			if (isprint(c)) printf("child %c\n",(char)c) ;
			c = getchar() ;
		}
		printf("child exiting..\n") ;
		return 0 ;
	}

	// parent 
	int c = 0 ;
	while (c!=EOF) {
		if (isprint(c)) printf("parent %c\n", (char)c) ;
		c = getchar() ;
	}
	printf("parent exiting..\n") ;
	return 0 ;
}

