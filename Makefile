LC_ALL=cs_CZ.utf8
COMPILER=gcc
FLAGS=-g -std=c11 -pedantic -Wall -Wextra

# i dont know how this works yet :D

no-comment: no-comment.c error.h

error: error.c error.h
	$(COMPILER) $(FLAGS) error.c -o error.o
