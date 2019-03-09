#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

static int verbose_flag;

int main(int argc, char **argv){

	int c;
	while(1){
		static struct option long_options[] = {
			{"verbose"  ,no_argument		,&verbose_flag},
			{"brief"		,no_argument		,&verbose_flag},
			{"add"		,no_argument		,0	,'a'},
			{"append"	,no_argument		,0	,'b'},
			{"delete"	,required_argument,0 ,'d'},
			{"create"	,required_argument,0 ,'c'},
			{"file" 	   ,required_argument,0 ,'f'},
			{0,0,0,0}
			
		};
		int option_index = 0;
		
		c = getopt_long (argc,argv,"abc:d:f:",
								long_options, &option_index);
		
		if (c == -1)
				break;
		switch (c){
			case 0:
				if (long_options[option_index].flag != 0)
					break;
				printf("options %s",long_options[option_index].name);
				if (optarg)
					printf(" with arg %s",optarg);
				printf("\n");
				break;
			case 'a':
				puts("option -a\n");
				break;
			case 'c':
				printf("option -c with value '%s\n'",optarg);
				break;
			case 'd':
				printf("option -d with value '%s\n'",optarg);
				break;
			case 'f':
				printf("option -f with value '%s\n'",optarg);
				break;
			default:
				abort();
		}
	}
}	
