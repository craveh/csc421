#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// see: https://www.se.rit.edu/~swen-250/slides/instructor-specific/Rabb/C/06-C-Memory-Alloc-Strings.pdf

#define H "hello"

int main(int argc, char *argv[]) {
//	char h[strlen(H)] = "hello" ;
	char * h;
	h = malloc(strlen(H) + 1);
	strcpy(h, H);
	//printf("TEST\n");
	printf("%s\n",h) ;
	free(h);
	return 0 ;
}

