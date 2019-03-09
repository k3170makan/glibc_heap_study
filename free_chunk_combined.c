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
	char *array,*array_1,*array_2,*array_3;
	//char *array_;
	//char *array__;
	//find a way to show the chosen candiate for each round
	int inner_array = 0;
	int _char = 1;
	for(index = 0;index <= _len;index++){
		array = (char *)malloc(_len);
		array_1 = (char *)malloc(_len);
		array_2 = (char *)malloc(_len);
		array_3 = (char *)malloc(_len);
		printf("[*] @[%0.8p]\n",array);
		memset(array,_char,_len);
		memset(array_1,_char+1,_len+2);
		memset(array_2,_char+1,_len+5);
		memset(array_3,_char+1,_len+1);
		free(array);
		free(array_1);
		free(array_2);
		free(array_3);
		_char++;
	}	
	//printf("[*] done");
	return 0;
}
