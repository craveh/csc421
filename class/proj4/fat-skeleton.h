/*
 * name: fat-skeleton.h
 * last-update:
 * 		13 nov 2022 -bjr: created
 *
 */

#ifndef _FAT_SKELETON_H
#define _FAT_SKELETON_H 1

#define FAT_NAME_LEN 24
#define ACTION_NAME_LEN 4
#define CLUSTER_SIZE 128
#define DIR_N 64
#define FAT_N 128
#define ACTION_N 5

#define USAGE_MSG "usage: %s [-v]\n"
#define PROG_NAME "fat-skeleton"
#define SEP_CHARS " \t\n"
#define LINE_MAX 1024

#define ERR_CREATE 1
#define ERR_NOEXIST 2
#define ERR_DIRFULL 3
#define ERR_ABORT -1
#define ERR_FATFULL 4


struct Actions {
	char action_name[ACTION_NAME_LEN] ;
	int action_parameters ;
	int (*action_function)(int, char *[]) ;
	} ;

struct  DirEnt {
	char name[FAT_NAME_LEN] ;
	unsigned int len ;
	unsigned int starting_cluster ;
	} ;

extern int is_verbose_g ;

void init_fat() ;

int qu_action(int, char *[]) ;
int ls_action(int, char *[]) ;
int cr_action(int, char *[]) ;
int rm_action(int, char *[]) ;
int pc_action(int, char *[]) ;

#endif /* _FAT_SKELETON_H */

