#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#ifndef COUNT
#define COUNT 10
#endif

int main(int argc, char * argv[]){

	int count = COUNT ;

	// Easy and affordable error handling;
	// prevent a bad thing from happeneing by aborting
	assert(count>=0) ;
	for (; count+1; count--) {
		printf("%d\n", count) ;
	}
	printf("BOOM!\n") ;
	return 0 ;
}

