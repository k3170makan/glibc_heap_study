#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
void first_fit(size_t chunk_length,int run){	

	if (run = 0){
		run = 1;
	}
		
	char *array = make_string(chunk_length);	
	memset(array,0x41,chunk_length);

	char *array_ = make_string(chunk_length+0x10);	
	memset(array_,0x42,chunk_length+0x10);

	char *array__ = make_string(chunk_length+0x20);	
	memset(array__,0x43,chunk_length+0x20);

	char *array___ = make_string(chunk_length+0x30);	
	memset(array___,0x44,chunk_length+0x30);

		
	memset(array,0xFF,chunk_length);
	free_string(array);

	memset(array_,0xFF,chunk_length+0x10);
	free_string(array_);

	memset(array__,0xFF,chunk_length+0x20);
	free_string(array__);


}

int main(int argc, char **argv){
	/*
		Demonstrating first fit behaviour based on chunk size allocated.

		The C program here allocates a bunch of objects on the heap,
		free's them all in a strict order and then re-allocates them.
	
		Essentially I want to see which one gets chosen on the first re-allocation.
		By extension then. 
	
		Other experiments:
		 - See if changing the size of the allocated chunks allows you to re-order
			which one is selected
		 - What if some of them are fastbins?
		 - What if there is a massive fast bin chain but a non-fast chunk that is
			slower to search? - can this be used as a side channel?
		 - can we cause inner and outer fragmentation? - is it exploitable?
	*/
	int run = 0;
	int cycles = 2;
	int chunk_length = 20;
	int index = 0;
	for (index =0;index<cycles;index++){
		first_fit(chunk_length,run);
	}	
}
