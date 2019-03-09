#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/** simple experiment 
	1) learn the format
	2) learn how the format allocates first off
	3) show how free'd chunk formats are used
	4) show how chunks are recylced
	5) - maybe show the internal data structures
			- fast bins
			- malloc_state
			etc
	6) show how to influence which ones are returned
	
**/	
int main(int argc, char **argv){

	int _len = 30;
	int index = 0;
	char **heap_pointers = malloc(sizeof(void)*4);
	char *array,*array_,*array2;
	//char *array_;
	//char *array__;
	//find a way to show the chosen candiate for each round
	int inner_array = 0;
	int _char = 1;
	for(index = 0;index <= _len;index++){
		array = (char *)malloc(_len);
		array2= (char *)malloc(_len);
		printf("[*] @[%0.8p] @[%0.8p] :: ",array,array2);
		memset(array,_char,_len);
		memset(array2,_char,_len);
		
		for(inner_array = 0;inner_array<5;inner_array++){
			array_ = (char *)malloc(_len);
			memset(array_,_char,_len);
			heap_pointers[inner_array] = array_;
			printf(" %d@[%0.8p]",inner_array,array_);
		}
		for (inner_array = 0;inner_array<5;inner_array++){
			//printf("[*] heap poitner %d @[%p]\n",inner_array,heap_pointers[inner_array]);
			free(heap_pointers[inner_array]);
			
		}
		printf("\n");
		if (index % 2){
			free(array);
			free(array2);
		}
		_char++;
	}	
	//printf("[*] done");
	return 0;
}
