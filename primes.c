#include "bitset.h"
#include "eratosthenes.h"
#include <time.h>

#define POCET_CISEL 30

int main(void)
{
    clock_t start = clock();

    bitset_alloc(arr, POCET_CISEL);

    Eratosthenes(arr);

    bitset_index_t primes[10] = {0};
    int pocet = 0;
    for (bitset_index_t i = bitset_size(arr) - 1; i > 0 && pocet < 10; i--)
    {
        if (bitset_getbit(arr, i))
        {
            primes[pocet] = i;
            pocet++;
        }
    }

    for (int i = 9; i >= 0; i--)
    {
        printf("%lu\n", primes[i]);
    }

    bitset_free(arr);
    printf("Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}