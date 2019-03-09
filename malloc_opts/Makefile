CC=gcc
PROG=mallopt_test
FLAGS=-Wall -fPIC -g -O0
all:
	$(CC) $(FLAGS) -o $(PROG).elf $(PROG).c
gdbinit_on:
	cp ~/.gdbinit.bk ~/.gdbinit
gdbinit_off:
	mv ~/.gdbinit ~/.gdbinit.bk 
