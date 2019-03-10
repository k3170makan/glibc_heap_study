#!/bin/bash
lenchunks=$((1 + RANDOM % 256))
nchunks=$((1 + RANDOM % 10))
nthreads=$((1 + RANDOM % 10))

./pthread_arena.elf $nthreads $lenchunks $nchunks 1
