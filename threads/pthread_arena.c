#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>

char *make_string(size_t);
void free_string(char *);
void make_chunk(size_t,size_t);
void make_chunks_pthread(size_t *);
void make_chunks_pthread_rnd(size_t *);
void make_chunks(size_t, size_t,size_t);
void make_chunks_rnd(size_t, size_t,size_t);

char *make_string(size_t length){
	char *arr = (char *) malloc(length);
	//add if debug flag is preset
	#ifdef DEBUG
		asm("int $3");
	#endif 
	return arr;
}
void free_string(char *arr){
	free(arr);
	#ifdef DEBUG
	asm("int $3");
	#endif
	return;
}
void make_chunks_pthread_rnd(size_t *args){
	size_t len = args[0];
	size_t amount = args[1];
	size_t id = args[2];

	make_chunks_rnd(id,len,amount);

}
void make_chunks_pthread(size_t *args){
	size_t len = args[0];
	size_t amount = args[1];
	size_t id = args[2];

	make_chunks(id,len,amount);
}
/*
	Generate chunks in a list with a single size
		- shows us how fast chunks work
*/
void make_chunks(size_t id, size_t chunk_length, size_t nchunks){	
	int index = 0;	
	char **chunks = malloc(nchunks*sizeof(char *)); 

	for (index = 0;index < nchunks; index++){
		chunks[index] = make_string(chunk_length);
		#ifdef DATA
			printf("%p %d %d\n",chunks[index],chunks[index], chunk_length);
		#else
			printf("[*]\tthread [%d]: freeing string @[%p]\n",(int) id, chunks[index]);
		#endif
		memset(chunks[index],0x40+index,chunk_length);	
	}
	for (index = 0; index < nchunks;index++){
		memset(chunks[index],0xFF,chunk_length);	
		#ifdef DEBUG
		printf("[*]\tthread [%d]: freeing string @[%p]\n",(int) id, chunks[index]);
		#endif
		free_string(chunks[index]);
	}
}

/*
	Generate chunks with a slightly randomized, unique size for each chunk
		- shows us how unsorted chunks have
*/
unsigned int _rand(){
	FILE *dev_random = fopen("/dev/urandom","r");
	unsigned int seed = 0;
	fread(&seed, sizeof(seed), 1, dev_random);
	fclose(dev_random);
	//srand(seed);
	return seed;
}
void make_chunks_rnd(size_t id, size_t chunk_length, size_t nchunks){	

	unsigned int seed = _rand();
	size_t *size_dict = (size_t*) alloca(nchunks * sizeof(size_t));
	size_t rand_size = 0;
	int index = 0;	
	char **chunks = malloc(nchunks*sizeof(char *)); 
	for (index = 0;index < nchunks; index++){
		seed = _rand();
		rand_size = (seed*999999) % chunk_length;	
		size_dict[index] = rand_size;
		chunks[index] = make_string(rand_size);

		#ifdef DATA
			printf("%p %d %d\n",chunks[index],chunks[index], rand_size);
		#else
			printf("[*]\tthread [%d]: @[%p] {%d}\n",(int) id,chunks[index],rand_size);
		#endif
		memset(chunks[index],0x40+index,rand_size);	
	}
	
	for (index = 0; index < nchunks;index++){

		memset(chunks[index],0xFF,size_dict[index]);	//can only clear out the base size
		free_string(chunks[index]);
	}
	

}


int main(int argc, char **argv){

	int run = 0;
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
		#ifdef DEBUG
		printf("[*] creating thread [%d]\n",thread_num);
		#endif
		pthread_create(&threads[thread_num],
							NULL,
								#ifdef RANDOM
									make_chunks_pthread_rnd,
								#else
									make_chunks_pthread,
								#endif
							args);

		pthread_join(threads[thread_num],NULL);
	}

	for (thread_num = 0; thread_num < num_threads; thread_num++){
		pthread_join(threads[thread_num],NULL);
	}

}
	
