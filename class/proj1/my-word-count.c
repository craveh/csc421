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

#define CAT_PROGRAM "cat"
#define WC_PROGRAM "wc"

// a rare use of globals; name mangle to alert 

int is_verbose_g ;

int main(int argc, char * argv[]) {

	// write code here

	return 0;

}

