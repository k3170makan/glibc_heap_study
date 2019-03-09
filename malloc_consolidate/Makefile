CC=gcc
PROG=arena_study_2
FLAGS=-Wall -fPIC -g
all:
	$(CC) $(FLAGS) -o $(PROG).elf $(PROG).c
gdbinit_on:
	cp ~/.gdbinit.bk ~/.gdbinit
gdbinit_off:
	mv ~/.gdbinit ~/.gdbinit.bk 
