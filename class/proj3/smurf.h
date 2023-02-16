/*
 * name: barrier.h
 * last-update:
 * 		10 oct 2022 -bjr: created
 *
 */

#ifndef _SMURF_H
#define _SMURF_H 1

#define USAGE_MSG "usage: %s [-v] [-k number-of-tasks] number-of-smurfs\n"
#define PROG_NAME "smurf"

#define SLEEP_MOD 7
#define COUNT_DOWN 3
#define COUNT_SLEEP 1

#define DEFAULT_K 5

struct Barrier {
	unsigned int count ;
	unsigned int n ;
 	sem_t mutex ;
 	sem_t turnstile ;
 	sem_t turnstile2 ;
} ;

struct T_arg {
 	unsigned int smurf ;
 	unsigned int task_num ;
 	struct Barrier * barrier ;
} ;
		
extern int is_verbose_g ;
extern int smurf_start_g ;

struct Barrier * init_barrier(int n) ;
struct T_arg * init_t_arg(int smurf, int task_num, struct Barrier * barrier) ;
unsigned int smurf_effort(unsigned int smurf, unsigned int task)  ;

#endif /* _SMURF_H */

