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

char * make_string(size_t length){
	char *arr = (char *)malloc(length);
	asm("int $3");
	return arr;
}
void free_string(char *arr){
	free(arr);
	asm("int $3");
}

int main(int argc, char **argv){

	int _len = 128;
	int index = 0;
	char *array,*array_1,*array_2,*array_3,*array_4;
	//char *array_;
	//char *array__;
	//find a way to show the chosen candiate for each round
	int inner_array = 0;
	int _char = 1;
	for(index = 0;index <= _len;index++){

		array = make_string(_len);
		memset(array,0xAA,_len);

		/* 4 more allocations*/	
		array_1 = make_string(_len+80*1);
		memset(array_1,0xBB,_len+80*1);

		array_2 = make_string(_len+80*2);
		memset(array_2,0xCC,_len+80*2);

		array_3 = make_string(_len+80*3);
		memset(array_3,0xDD,_len+80*3);

		array_4 = make_string(_len+80*4);
		memset(array_4,0xEE,_len+80*4);

		/*free each array and clear it */

		memset(array_1,0xFF,_len+10);
		free_string(array_1);

		memset(array,0xFF,_len);
		free_string(array); 
	
		memset(array_2,0xFF,_len+20);
		free_string(array_2);

		memset(array_3,0xFF,_len+30);
		free_string(array_3);

		memset(array_4,0xFF,_len+40);
		free_string(array_4);

		_char++;
		printf("\n\n");
	}	
	//printf("[*] done");
	return 0;
}
