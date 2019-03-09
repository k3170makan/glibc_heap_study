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

	int _len = 50;
	int index = 0;
	char *array,*array_,*array__;
	//char *array_;
	//char *array__;

	int _char = 1;
	for(index = 0;index <= _len;index++){
		array = (char *)malloc(_len+index);
		array_ = (char *)malloc(_len+index);
		array__ = (char *)malloc(_len+index);

		printf("[*] arrays allocated\n");
		//array_ = (char *)malloc(_len+index+1);
		//array__ = (char *)malloc(_len+index+1);


		memset(array,_char,_len+index);
		printf("[*] array initialized\n");
		//memset(array_,_char,_len+index+1);
		//memset(array__,_char,_len+index+1);

		free(array);
		free(array_);
		printf("[*] array freed\n");
		//free(array__);
		
		if (index % 2){
			free(array__);
		}
		_char++;
	}	
	
	//free(array);
	printf("[*] A has been freed\n");
	return 0;
}
