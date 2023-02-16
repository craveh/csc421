#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// see: https://www.se.rit.edu/~swen-250/slides/instructor-specific/Rabb/C/06-C-Memory-Alloc-Strings.pdf

#define H "hello"

int main(int argc, char *argv[]) {
	char h[5] ;
	strcpy(h,"hello") ;
	printf("%s\n",h) ;
	return 0 ;
}

