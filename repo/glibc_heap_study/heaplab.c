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

	int a_len = 100;
	char *A = (char *)malloc(100);
	memset(A,0x41,(size_t)a_len);
	A[a_len] = '\0';

	int b_len = 200;
	char *B = (char *)malloc(b_len);
	memset(B,0x42,(size_t)b_len);
	B[b_len] = '\0';

	int c_len = 300;
	char *C = (char *)malloc(c_len);
	memset(C,0x43,(size_t)c_len);
	C[c_len] = '\0';
		
	free(A);
	printf("[*] A has been freed\n");
	free(B);
	printf("[*] B has been freed\n");
	free(C);
	printf("[*] C has been freed\n");
	return 0;
}
