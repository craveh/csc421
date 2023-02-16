#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/time.h>
#include<assert.h>
#include<semaphore.h>

#include "smurf.h"

/*
 * author: burt rosenberg
 * last update:
 *    16 october 2022
 *
 */

extern int is_verbose_g ; 
extern int smurf_start_g ;

// this corresponds to the 3.7.4 Reusable barrier hint, plus some,
// in the Little Book Of Semaphores by Allen B. Downey

struct Barrier * init_barrier(int n) {
	struct Barrier * barrier ;
	barrier = (struct Barrier *)malloc(sizeof(struct Barrier)) ;
	assert(barrier) ;
	barrier->n = n ;
	barrier->count = 0 ;
	sem_init(&barrier->mutex,0,1) ;
	sem_init(&barrier->turnstile,0,0) ;
	sem_init(&barrier->turnstile2,0,1) ;
	return barrier ;
}

struct T_arg * init_t_arg(int smurf, int task_num, struct Barrier * barrier) {
	struct T_arg * t_arg ;
	t_arg = (struct T_arg *)malloc(sizeof(struct T_arg)) ;
	assert(t_arg) ;
	t_arg->barrier= barrier ;
	t_arg->smurf = smurf;
	t_arg->task_num = task_num ; 
	return t_arg ;
}

unsigned int smurf_effort(unsigned int smurf, unsigned int task) {
	return (3*smurf+task)%SLEEP_MOD+1 ;
}


