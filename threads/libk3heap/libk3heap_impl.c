#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>
#include "libk3heap.h"

/**

	libk3heap rough version
		- simple intercepted malloc, free and other heapy methods that I used
		to help elborate how the heap works
		- injects break points just before heap returns
		currenty only has rudimentary injeciton for:
			- free, malloc, *more coming soon*		
*/

int main(int argc, char **argv){

	
	int run = 0;
	/*
		todo : make this as easy as a sipmle include to instrument?
				 perhaps a lib call you give a pointer to malloc to and it returns a *wrapped* one?
				gotta make it simpler than this
	*/
	if (argc < 4){
		printf("[x] not enough arguments\nUsage : %s [number of threads] [chunk length (bytes)] [number of chunks] [rounds]\n",argv[0]);
		return 1;
	}
	int num_threads = atoi(argv[1]);
	
	pthread_t threads[num_threads];	
	size_t chunk_length = atoi(argv[2]);
	size_t number_of_chunks = atoi(argv[3]);
	int cycles = atoi(argv[4]);
	int index = 0;
	int thread_num = 0;
	size_t *args[2];

	args[0] = chunk_length;
	args[1] = number_of_chunks;
	for (thread_num = 0; thread_num < num_threads; thread_num++){


		args[2] = thread_num;

		pthread_create(&threads[thread_num],
							NULL,
							make_chunk_field_pthread,
							args);

		pthread_join(threads[thread_num],NULL);
	}

	for (thread_num = 0; thread_num < num_threads; thread_num++){
		pthread_join(threads[thread_num],NULL);
	}

}
