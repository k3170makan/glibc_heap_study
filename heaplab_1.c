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

	char *A = (char *)malloc(100);
	char *B = (char *)malloc(200);
	char *C = (char *)malloc(300);
		
	free(A);
	printf("[*] A has been freed\n");
	free(B);
	printf("[*] B has been freed\n");
	free(C);
	printf("[*] C has been freed\n");
	return 0;
}
