// primes.c
// Řešení IJC-DU1, příklad A), 20.3.2024
// Autor: Lukáš Pšeja, FIT
// Přeloženo: gcc 11.4.0

#include "eratosthenes.h"
#include <time.h>

int main(void)
{
    clock_t start = clock();

    // ulimit -s 83250
    bitset_create(arr, 666000000UL);

    Eratosthenes(arr);

    bitset_index_t primes[10] = {0};
    int count = 0;
    for (bitset_index_t i = bitset_size(arr) - 1; i > 0 && count < 10; i--)
    {
        bitset_index_t bit = bitset_getbit(arr, i);
        if (bit == 2)
        {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", i, bitset_size(arr));
        }
        else if (bit == 1)
        {
            primes[count] = i;
            count++;
        }
    }

    for (int i = 9; i >= 0; i--)
    {
        printf("%lu\n", primes[i]);
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}