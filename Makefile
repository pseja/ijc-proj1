# eratosthenes.c
# Řešení IJC-DU1, příklad a), 20.3.2024
# Autor: Lukáš Pšeja, FIT
# Přeloženo: GNU Make 4.3

LC_ALL=cs_CZ.utf8
COMPILER=gcc
M32=
FLAGS=-g -std=c11 -pedantic -Wall -Wextra -O2

.PHONY: all run clean zip

all: primes primes-i no-comment

%.o: %.c
	$(COMPILER) $(FLAGS) $(M32) -c $< -o $@

%-i.o: %.c
	$(COMPILER) $(FLAGS) $(M32) -DUSE_INLINE -c $< -o $@

primes: primes.o error.o bitset.o eratosthenes.o
	$(COMPILER) $(FLAGS) $(M32) $^ -o $@ -lm

primes-i: primes-i.o error.o bitset-i.o eratosthenes-i.o
	$(COMPILER) $(FLAGS) $(M32) $^ -o $@ -lm

no-comment: no-comment.o error.o
	$(COMPILER) $(FLAGS) $(M32) $^ -o $@

run: all
	ulimit -s 83250 && ./primes && ./primes-i

clean:
	rm -f *.o primes primes-i no-comment xpsejal00.zip

zip:
	zip xpsejal00.zip *.c *.h Makefile

