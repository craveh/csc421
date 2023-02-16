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
	for(int i=0; i<DIR_N; i++){
		if(strcmp(root_dir[i].name, "")!=0){
			printf("%3d %4d %s\n", i, root_dir[i].len, root_dir[i].name) ;
		}
	}

	return 0 ;
}

int cr_action(int actc, char * actv[]) {
	// create the file named actv[2] of length actv[1]

	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}
	//check if file exists
	if(find_file(actv[2]) != -1){
		return ERR_CREATE;
	}

	//look for first empty dir_ent
	for(int i=0; i<DIR_N; i++){
		if(strcmp("", root_dir[i].name)==0){
			//create fat cluster
			int cluster_start = cluster_chain(atoi(actv[1]));
			if(cluster_start==-1){
				return ERR_FATFULL;
			}
			//update dirent
			root_dir[i].starting_cluster = cluster_start;
			root_dir[i].len = atoi(actv[1]);
			strncpy(root_dir[i].name, actv[2], FAT_NAME_LEN);
			return 0;
		}

	
	}
	//nothing empty return error
	return ERR_DIRFULL;
}

int rm_action(int actc, char * actv[]) {
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}
	
	// remove the file named actv[1]
	int file_location = find_file(actv[1]);
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

}

int pc_action(int actc, char * actv[]) {
	if (is_verbose_g>1) {
		printf("(%s,%d):action: %s, %d\n",__FILE__,__LINE__,(char *)actv[0], actc) ;
	}

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

/* end of file */
