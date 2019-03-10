CC=gcc
PROG=pthread_arena
LIBS=-lpthread
FLAGS=-Wall -fPIC -g -O
DEBUG=-DDEBUG
RANDOM=-DRANDOM
DATA=-DDATA
all:
	$(CC) $(FLAGS) -o $(PROG).elf $(PROG).c $(LIBS) 
debug:
	$(CC) $(FLAGS) $(DEBUG) $(RANDOM) -o $(PROG).elf $(PROG).c $(LIBS) 
random_only:
	$(CC) $(FLAGS) $(RANDOM) -o $(PROG).elf $(PROG).c $(LIBS) 
data:
	$(CC) $(FLAGS) $(DATA) -o $(PROG).elf $(PROG).c $(LIBS) 
data_random:
	$(CC) $(FLAGS) $(RANDOM) $(DATA) -o $(PROG).elf $(PROG).c $(LIBS) 
test:
	./random_test.sh
clean:
	rm -rf *.elf
	rm -rf *.o 
