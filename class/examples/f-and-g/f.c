#include<stdio.h>
#include<stdlib.h>

#ifdef HIDEIT
static int fx = 3 ;
static int gx = 13 ;
#else
int fx = 3;
extern int gx ;
#endif

extern int fgx  ;

int f(int i) { printf("Hello world %d %d %d\n",fx,gx, fgx) ; }
