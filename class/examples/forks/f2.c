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

#define SLEEP_SECONDS 3

int main(int argc, char * argv[]){

	printf("This program forks a child that loops until killed.\n") ;
	printf("\tThe parent exits, use ps to get the PID of child, to run kill -9.\n\n") ;

	if (fork()==0) {
		// child
		while (1) {
			sleep(SLEEP_SECONDS) ;
			printf("child yawns ..\n") ;
		}
		printf("child exiting..\n") ;
		return 0 ;
	}

	// parent 
	printf("parent exiting..\n") ;
	return 0 ;
}

