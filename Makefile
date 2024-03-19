LC_ALL=cs_CZ.utf8
COMPILER=gcc
FLAGS=-g -std=c11 -pedantic -Wall -Wextra -O2

.PHONY: all run clean zip

all: primes primes-i no-comment

%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

%-i.o: %.c
	$(COMPILER) $(FLAGS) -DUSE_INLINE -c $< -o $@

primes: primes.o error.o bitset.o eratosthenes.o
	$(COMPILER) $(FLAGS) $^ -o $@ -lm

primes-i: primes-i.o error.o bitset-i.o eratosthenes-i.o
	$(COMPILER) $(FLAGS) $^ -o $@ -lm

no-comment: no-comment.o error.o
	$(COMPILER) $(FLAGS) $^ -o $@

run: all
	ulimit -s 83250 && ./primes
	ulimit -s 83250 && ./primes-i

clean:
	rm -f *.o primes primes-i no-comment xpsejal00.zip

zip:
	zip xpsejal00.zip *.c *.h Makefile

