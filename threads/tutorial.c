#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message(char *);


int main(int argc, char **argv){
	
	int num_threads = atoi(argv[1]);
	if (argc < num_threads+1){
		printf("[x] not enough messages\nUsage: ./%s [number of threads] [message 0] [message 1] ... [message n]",argv[0]);
		return 1;
	}
	pthread_t threads[num_threads];
	int rc;
	int t;

	for (t = 0; t < num_threads; t++){
		pthread_create(&threads[t],NULL,(void *) print_message,(char *) argv[2+t]);
	}
	for (t = 0; t < num_threads; t++){
		pthread_join(threads[t],NULL);	
	}
	return 0;
}
void *print_message(char *message){
	printf("\t[*] my message is %s\n",(char *)message);
	return  NULL;
}
