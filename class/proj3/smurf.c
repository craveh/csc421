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
 *    14 october 2022
 *
 */
  
// implements a barrier as in figure 3.7.5 Reusable barrier solution
// Little Book Of Semaphores by Allen B. Downey

int is_verbose_g = 0 ; 
int smurf_start_g = 0 ;

void * smurf(void * the_args) {

	struct T_arg * t_arg = (struct T_arg *) the_args ;
	struct Barrier * barrier = t_arg->barrier ;
	unsigned int task = 1 ;
	unsigned int sleep_seconds ;
	
	if (is_verbose_g) {
		printf("(%s:%d): smurf %d entered!\n",__FILE__,__LINE__,t_arg->smurf) ;
	}
	// wait to get the global start signal
	while (1) if (smurf_start_g) break ;
	
	for (task=1;task<=t_arg->task_num;task++) {




		sleep_seconds = smurf_effort(t_arg->smurf,task) ;
		sleep(sleep_seconds) ;




		
		printf("smurf %d has finished task %d\n",t_arg->smurf,task) ;



		
	}
	
	if (is_verbose_g) {
		printf("(%s:%d): smurf %d is exiting\n",__FILE__,__LINE__,t_arg->smurf) ;
	}
	pthread_exit(NULL) ;
}

int main(int argc, char * argv[]) {
	int ch, i ;
	
	pthread_t thread_id ;
	struct T_arg * t_arg_p ;
	struct Barrier * barrier_p ; 
	unsigned int n, k ;

	k = DEFAULT_K ;
	while ((ch = getopt(argc, argv, "vk:?h")) != -1) {
		switch(ch) {
			case 'v':
				is_verbose_g += 1 ;
				break ;
			case 'k':
				k = (unsigned int) atoi(optarg) ;
				break ;
			case '?':
			case 'h':
			default:
				printf(USAGE_MSG, PROG_NAME) ;
				return 0 ;
		}
	}
	argc -= optind;
	argv += optind;
	if (argc!=1) {
		printf(USAGE_MSG, PROG_NAME) ;
		return 0 ;
	}
	n = (unsigned int) atoi(argv[0]) ;	
	assert(n<10) ;
	assert(k<10) ;

	if (is_verbose_g) {
		printf("(%s,%d): num. smurfs:%d, num. tasks: %d \n",__FILE__,__LINE__,n,k) ;
	}

	// initialize and launch threads
	barrier_p = init_barrier(n) ;
	for (i=0;i<n;i++) {
		t_arg_p = init_t_arg(i+1,k,barrier_p) ;
		if (pthread_create( &thread_id, NULL, smurf, (void *) t_arg_p )) {
			perror("pthread_create") ;
			exit(-1) ;
		}
	}

	{
		// count down!
		int count_down = COUNT_DOWN ;
		printf("Get ready, Smurfs!\n") ;
		while (count_down) {
			printf("%d\n",count_down) ;
			sleep(COUNT_SLEEP);
			count_down-- ;
		}
		printf("GO SMURFS!!!\n") ;
	}
	smurf_start_g = 1 ; /* tell thread to start */
	
	pthread_exit(NULL) ; /* wait for all threads to exit */
	return 0 ;
}
