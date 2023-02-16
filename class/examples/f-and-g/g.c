#include<stdio.h>
#include<stdlib.h>

#ifdef HIDEIT
static int gx = 4 ;
static int fx = 14 ;
#else
int gx = 4 ;
extern int fx ;
#endif

extern int fgx ;

int g(int i) { printf("Goodnight moon %d %d %d\n", fx, gx, fgx) ; } 
