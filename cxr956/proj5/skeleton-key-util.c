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
	for(int i=0; i<DIR_N; i++){
		if(strcmp(file_name, root_dir[i].name)==0){
			// printf("MATCH\n");
			return i;
		}	
	}
	// printf("The strings do not match");
	return -1 ;
}

int get_number_clusters(int size){
	if(size!=0 && size%CLUSTER_SIZE ==0){
		return size/CLUSTER_SIZE;
	}
	return size/CLUSTER_SIZE + 1;
	
}

int cluster_chain(int byte_len) {
	// create a cluster chain of length minimally sufficient to 
	// hold byte_len bytes, but never less than one; or -1 if 
	// an error
	// return -1 ;
	//get num clusters needed
	int num_clusters_needed = get_number_clusters(byte_len); 
	
	//check that enough available and mark them down
	int spots[num_clusters_needed];
	int counter = 0;
	int i;
	for (i=0; i<FAT_N; i++){
		if(counter==num_clusters_needed){
			break;
		}
		if(fat_table[i]==0){
			//fill data at this spot with \0
			// printf("Data stored at %d is %c\n", i*CLUSTER_SIZE, '\0');
			data[i*CLUSTER_SIZE] = '\0';
			// printf("Data stored at %d is %c\n", i*CLUSTER_SIZE, data[i*CLUSTER_SIZE]);
			spots[counter] = i;
			counter++;
		}
	}

	//not enough spots
	if(counter!=num_clusters_needed){
		return -1;
	}

	//fill in FAT table
	fat_table[spots[counter-1]] = -1;
	for(i=0; i<num_clusters_needed-1; i++){
		fat_table[spots[i]] = spots[i+1];
	}
	return spots[0];
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
	for(int i=0; i<DIR_N; i++){
		if(strcmp(root_dir[i].name, "")!=0){
			printf("%3d %4d %s\n", i, root_dir[i].len, root_dir[i].name) ;
		}
	}

	return 0 ;
}

// create needs to be updated to write a \0 in the 0th byte of the file so created

int cr_action_aux(char * file_name, int len) {
	// create the file name file_name of length len
	
	// errors:
	//   return ERR_CREATE ;  // file exists
	//   return ERR_DIRFULL ; // no room in directly
	//   return ERR_FATFULL ; // no room on disk

	//check if file exists
	if(find_file(file_name) != -1){
		return ERR_CREATE;
	}

	//look for first empty dir_ent
	for(int i=0; i<DIR_N; i++){
		if(strcmp("", root_dir[i].name)==0){
			//create fat cluster
			int cluster_start = cluster_chain(len);
			if(cluster_start==-1){
				return ERR_FATFULL;
			}
			//update dirent
			root_dir[i].starting_cluster = cluster_start;
			root_dir[i].len = len;
			strncpy(root_dir[i].name, file_name, FAT_NAME_LEN);
			return 0;
		}

	
	}
	//nothing empty return error
	return ERR_DIRFULL;

	// return 0 ;
}

int rm_action_aux(char * file_name) {
	// remove the file named file_name
	int file_location = find_file(file_name);
	if (file_location == -1){
		return ERR_NOEXIST;
	}

	//set fat table spots to zero
	int next;
	for(int i=root_dir[file_location].starting_cluster; i<FAT_N; i){
		if (fat_table[i]== -1){
			fat_table[i] = 0;
			break;
		}
		next = fat_table[i];
		fat_table[i] = 0;
		i = next;
	}
	
	//set dir to empty
	strncpy(root_dir[file_location].name, "", FAT_NAME_LEN);

	return 0 ;
	
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

	int file_location = find_file(actv[1]);
	if (file_location == -1){
		return ERR_NOEXIST;
	}


	printf("%s: ",actv[1]) ;
	// int num_clusters = root_dir[file_location].len/128 + 1;
	int num_clusters = get_number_clusters(root_dir[file_location].len);
	int cluster_chain[num_clusters];

	cluster_chain[0] = root_dir[file_location].starting_cluster;
	// printf("Cluster chain[0]=%d, cluster_head=%d\n", cluster_chain[0], cluster_head);
	// printf("TEST HERE 2\n");
	int i;
	for(i=1; i<num_clusters; i++){
		cluster_chain[i] = fat_table[cluster_chain[i-1]];
	}
	// printf("TEST HERE 2\n");
	
	for(i=0; i<num_clusters;i++){
		printf("%d ", cluster_chain[i] ) ;
	}
	printf("\n");

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
	// strcpy(buf, "test");
	// res = 0;
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
	// printf("Buf: %s, n: %d, cluster: %d, len: %d\n", buf, n, cluster, len);
	
	//get number of clusters
	int num_clusters = get_number_clusters(len);
	int cluster_chain[num_clusters];

	cluster_chain[0] = cluster;
	// printf("Cluster chain[0]=%d, cluster_head=%d\n", cluster_chain[0], cluster_head);
	// printf("TEST HERE 2\n");
	//create array with the cluster locations
	int i;
	for(i=1; i<num_clusters; i++){
		cluster_chain[i] = fat_table[cluster_chain[i-1]];
	}
	// printf("TEST HERE 2\n");
	// for(int x=0; x<num_clusters; x++){
	// 	printf("%d ", cluster_chain[x]);
	// }
	// printf("\n");
	
	//put contents of buffer into data
	int counter = 0;
	for(i=0; i<num_clusters;i++){
		for(int j=0; j<CLUSTER_SIZE; j++){
			if(counter == n){
				data[cluster_chain[i]*CLUSTER_SIZE + j] = '\0';
				break;
			}	
			data[cluster_chain[i]*CLUSTER_SIZE + j] = buf[counter];
			counter++;
		}
		// printf("%d ", cluster_chain[i] ) ;
	}
	// printf("\n");
	// return ERR_DATA ;
}

int chaining_read(char buf[], int n, int cluster, int len ) {
	// copy len butes into buf beginning at cluster*CLUSTER_SIZE
	// and following the cluster chain, as needed.

	//get number of clusters
	int num_clusters = get_number_clusters(len);
	int cluster_chain[num_clusters];

	cluster_chain[0] = cluster;
	// printf("Cluster chain[0]=%d, cluster_head=%d\n", cluster_chain[0], cluster_head);
	// printf("TEST HERE 2\n");
	//create array with the cluster locations
	int i;
	for(i=1; i<num_clusters; i++){
		cluster_chain[i] = fat_table[cluster_chain[i-1]];
	}
	// printf("TEST HERE 2\n");
	
	//put contents of buffer into data
	int counter = 0;
	for(i=0; i<num_clusters;i++){
		for(int j=0; j<CLUSTER_SIZE; j++){
			if(counter == n){
				// buf[i*CLUSTER_SIZE + j] = '\0';
				// printf("%s\n", buf);
				break;
			}
			buf[counter] = data[cluster_chain[i]*CLUSTER_SIZE + j];
			// data[i*CLUSTER_SIZE + j] = buf[counter];
			counter++;
		}
		// if(counter == n){
		// 		// buf[counter] = '\0';
		// 		// printf("%s\n", buf);
		// 		break;
		// 	}
	}
	// return buf;
	return 0;

	// return ERR_DATA ;
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
	rm_action_aux(actv[1]);
	int cr_return = cr_action_aux(actv[1], strlen(actv[2]) + 1);

	if(cr_return != 0){
		return -1;
	}
	int starting_cluster = root_dir[find_file(actv[1])].starting_cluster;


	chaining_write(actv[2], strlen(actv[2]), starting_cluster, strlen(actv[2])+ 1);


	return 0 ;
}


/* end of file */
