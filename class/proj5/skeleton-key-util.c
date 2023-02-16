#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/time.h>
#include<assert.h>
#include<time.h>

#include "skeleton-key.h"

/*
 * name: skeleton-key-util.c
 * last update:
 *    29 nov 2022, bjr
 *
 */

static struct DirEnt root_dir[DIR_N] ;
static unsigned int fat_table[FAT_N] ;
static char data[FAT_N*CLUSTER_SIZE] ;

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
	for (i=0;i<FAT_N*CLUSTER_SIZE;i++) data[i] = 0 ;
	return ;
}

// ---------------------------
// project 4 routines
// ---------------------------

// note update! rm_action and rm_action_aux work together, with 
// rm_action just breaking out the actv arguments and passing them to rm_action_aux
// same for cr_action and cr_action_aux.

// this is done to save work on the new project 5 routines.


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

// create needs to be updated to write a \0 in the 0th byte of the file so created

int cr_action_aux(char * file_name, int len) {
	// create the file name file_name of length len
	
	// errors:
	//   return ERR_CREATE ;  // file exists
	//   return ERR_DIRFULL ; // no room in directly
	//   return ERR_FATFULL ; // no room on disk

	return 0 ;
}

int rm_action_aux(char * file_name) {
	// remove the file named file_name
	
	// errors:
	//    return ERR_NOEXIST ; // file does not exist
	
	return 0 ;
}

int rm_action(int actc, char * actv[]) {
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}
	return rm_action_aux(actv[1]) ;
}

int cr_action(int actc, char * actv[]) {
	int len ;

	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}
	len =  atoi(actv[1]) ;
	return cr_action_aux(actv[2],len) ;
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
	

// ---------------------------
// project 5 new routines
// ---------------------------

// these two new actions are done for you

int dd_action(int actc, char * actv[]) {
	int i ;
	for (i=0;i<FAT_N*CLUSTER_SIZE;i++) {
		if (!(i&0x0f)) 
			printf("\n%04d: ", i ) ;
		printf("%02x ", data[i]) ;
	}
	printf("\n") ;
	return 0 ;
}

// need a prototype for a forwardly defined function
int chaining_read(char buf[], int n, int cluster, int len )  ; 

int rd_action(int actc, char * actv[]) {
	int f, n ;
	char * buf ;
	int res ;
	
	f = find_file(actv[1]) ;
	if (f==-1) return ERR_NOEXIST ;
	n = root_dir[f].len ;
	buf = (char *) malloc(n) ;
	assert(buf) ;
	
	res = chaining_read( buf, n, root_dir[f].starting_cluster, root_dir[f].len) ;
	if (res) {
		free(buf) ;
		return res ;
	}
	printf("%s: %s\n", actv[1], buf) ;
	free(buf) ;
	return 0 ;

}


// chaining_write and chaining_read are the tricky ones.

// 1) get chaining_write done. chaining_read will be a one line
//    change that you can do at the last minute.
// 2) first do it for 1 cluster files, no chaining. 
// 3) have a plan, and let printf tell you the computer is carrying out your plan

int chaining_write(char buf[], int n, int cluster, int len ) {
	// copy the n bytes in buf to data[] beginning at cluster*CLUSTER_SIZE
	// and following the cluster chain, as needed.
	
	return ERR_DATA ;
}

int chaining_read(char buf[], int n, int cluster, int len ) {
	// copy len butes into buf beginning at cluster*CLUSTER_SIZE
	// and following the cluster chain, as needed.

	return ERR_DATA ;
}

int wr_action(int actc, char * actv[]) {
	// write the string (including the \0) of actv[2] into file
	// with filename actv[1]
	
	// hint: 
	//  1) first call rm_action_aux and ignore the return value
	//  2) then call cr_action_aux with the filename and the string length plus one
	//  3) check the return value
	//  4) call chaining_write
	// 

	return 0 ;
}


/* end of file */
