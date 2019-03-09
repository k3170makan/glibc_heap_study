#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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
/*
	Generate chunks in a list with a single size
		- shows us how fast chunks work
*/
void make_chunk_field(size_t chunk_length,size_t amount_of_chunks){	
	/*Trying a slight different allocation, libc might have optimization for arrays*/
	int index = 0;	
	char **chunks = malloc(amount_of_chunks*sizeof(char *)); 

	for (index = 0;index < amount_of_chunks; index++){
		
		char *chunk =  make_string(chunk_length);
		chunks[index] = chunk;
		memset(chunks[index],0x40+index,chunk_length);	
	}
	for (index = 0; index < amount_of_chunks;index++){
		memset(chunks[index],0xFF,chunk_length);	
		free_string(chunks[index]);
	}
}
/*
	Generate chunks with a slightly randomized, unique size for each chunk
		- shows us how unsorted chunks have
*/
void make_chunk_field_rnd(size_t chunk_length,size_t amount_of_chunks){

	srand(time(NULL));
	size_t *size_dict = (size_t*) alloca(amount_of_chunks * sizeof(size_t));
	size_t rand_size = 0;
	int index = 0;	
	char **chunks = malloc(amount_of_chunks*sizeof(char *)); 
	for (index = 0;index < amount_of_chunks; index++){
		rand_size = (rand()*999999+chunk_length) % 80;	
		size_dict[index] = rand_size;
		printf("random chunk size: [%i] %d\n",index,size_dict[index]);

		chunks[index] = make_string(rand_size);
		memset(chunks[index],0x40+index,rand_size);	
	}
	
	for (index = 0; index < amount_of_chunks;index++){

		memset(chunks[index],0xFF,size_dict[index]);	//can only clear out the base size
		free_string(chunks[index]);
	}
	

}	
int main(int argc, char **argv){
	int run = 0;
	if (argc < 4){
		printf("Usage : ./%s [chunk length (bytes)] [number of chunks] [rounds]");
		return 2;
	}
	size_t chunk_length = atoi(argv[1]);
	unsigned int number_of_chunks = atoi(argv[2]);
	int cycles = atoi(argv[3]);
	int index = 0;
	for (index =0;index<cycles;index++){
		//make_chunk_field_rnd(chunk_length,number_of_chunks);
		make_chunk_field(chunk_length,number_of_chunks);
		//printf("\n");
	}	
}
