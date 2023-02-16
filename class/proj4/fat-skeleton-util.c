#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/time.h>
#include<assert.h>
#include<time.h>

#include "fat-skeleton.h"

/*
 * name: fat-skeleton-util.c
 * last update:
 *    13 nov 2022, bjr
 *
 */

static struct DirEnt root_dir[DIR_N] ;
static unsigned int fat_table[FAT_N] ;

void init_fat() {
	 int i ;
	 
	 if (is_verbose_g>1) {
		printf("(%s,%d):\n\t%ld fat entries (%ld bytes),"
			"\n\t%ld dir entries (%ld bytes),"
			"\n\tdirent size is %ld bytes.\n", 
			__FILE__,__LINE__,
			(unsigned long) FAT_N, sizeof(fat_table), 
			(unsigned long) DIR_N, sizeof(root_dir), 
			 sizeof(struct DirEnt)
			) ;
	}

	for (i=0;i<FAT_N;i++) fat_table[i] = 0 ;
	for (i=0;i<sizeof(root_dir);i++) ((char *)root_dir)[i] = 0 ;
	return ;
}

int find_file(char * file_name) {
	// return directory index if found, else return -1
	int i ;
	
	return -1 ;
}

int cluster_chain(int byte_len) {
	// create a cluster chain of length minimally sufficient to 
	// hold byte_len bytes, but never less than one; or -1 if 
	// an error
	return -1 ;
}

int qu_action(int actc, char * actv[]) {
	if (is_verbose_g>1) {
		printf("(%s,%d):qu_action\n",__FILE__,__LINE__) ;
	}
	return ERR_ABORT ;
}

int ls_action(int actc, char * actv[]) {	
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}

	// print out all files in the following format:
	//printf("%3d %4d %s\n", i, root_dir[i].len, root_dir[i].name) ;

	return 0 ;
}

int cr_action(int actc, char * actv[]) {
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}

	// create the file named actv[2] of length actv[1]

	// errors:
	//   return ERR_CREATE ;  // file exists
	//   return ERR_DIRFULL ; // no room in directly
	//   return ERR_FATFULL ; // no room on disk
	
	return 0 ;
}

int rm_action(int actc, char * actv[]) {
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}
	
	// remove the file named actv[1]
	
	// errors:
	//    return ERR_NOEXIST ; // file does not exist
	
	return 0 ;

}

int pc_action(int actc, char * actv[]) {
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}
	
	// print the cluster chain for the file name actv[1]
	
	// use this format:
	// printf("%s: ",actv[1]) ;
	//    for each cluster in order printf("%d ", cluster ) ;
	// printf("\n") ;
	
	// errors:
	//   return ERR_NOEXIST ;  // file does not exist

	return 0 ;
}

/* end of file */
