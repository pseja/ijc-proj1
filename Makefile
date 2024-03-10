LC_ALL=cs_CZ.utf8
COMPILER=gcc
FLAGS=-g -std=c11 -pedantic -Wall -Wextra

test: test.c bitset.c bitset.h error.c error.h
	$(COMPILER) $(FLAGS) test.c bitset.c bitset.h error.c error.h -o test
