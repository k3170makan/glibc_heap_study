CC=gcc
PROG=arena_study_stack
FLAGS=-Wall -fPIC -g -fno-stack-protector -O0
all:
	$(CC) $(FLAGS) -o $(PROG).elf $(PROG).c
gdbinit_on:
	cp ~/.gdbinit.bk ~/.gdbinit
gdbinit_off:
	mv ~/.gdbinit ~/.gdbinit.bk 
