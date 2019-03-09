#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int
main(int argc, char **argv){
	
	int aflag = 0;
	int bflag = 0;
	
	char *cvalue = NULL;
	
	int index;
	int c;
	opterr = 0;
	
	while ((c = getopt(argc, argv, "abc:")) != -1) {
		switch (c){
			case 'a':
				aflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'c':
				cvalue = optarg;
				break;
			case '?':
				break;
		}
	}		
	printf("aflag = %d, bflag = %d, cvalue = %s\n",
				aflag,bflag,cvalue);
}
