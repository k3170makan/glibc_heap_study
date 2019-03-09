
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>

char *make_string(size_t);
void free_string(char *);
void make_chunk(size_t,size_t);
void make_chunk_filed_pthread(size_t *);
void make_chunk_field(size_t, size_t,size_t);

char *make_string(size_t length){
	char *arr = (char *) malloc(length);
	asm("int $3");
	return arr;
}
void free_string(char *arr){
	free(arr);
	asm("int $3");
	return;
}

void make_chunk_field_pthread(size_t *args){
	size_t len = args[0];
	size_t amount = args[1];
	size_t id = args[2];

	make_chunk_field(id,len,amount);
}
/*
	Generate chunks in a list with a single size
		- shows us how fast chunks work
*/
void make_chunk_field(size_t id, size_t chunk_length, size_t amount_of_chunks){	
	int index = 0;	
	char **chunks = malloc(amount_of_chunks*sizeof(char *)); 

	for (index = 0;index < amount_of_chunks; index++){
		printf("[*]\tthread [%d]: making string...\n",(int) id);
		chunks[index] = make_string(chunk_length);
		memset(chunks[index],0x40+index,chunk_length);	
	}
	for (index = 0; index < amount_of_chunks;index++){
		memset(chunks[index],0xFF,chunk_length);	
		printf("[*]\tthread [%d]: freeing string...\n",(int) id);
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
