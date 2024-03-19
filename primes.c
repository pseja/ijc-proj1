#include "bitset.h"
#include "eratosthenes.h"
#include <time.h>

int main(void)
{
    clock_t start = clock();

    // ulimit -s 83250
    bitset_create(arr, 666000000);

    Eratosthenes(arr);

    bitset_index_t primes[10] = {0};
    int count = 0;
    for (bitset_index_t i = bitset_size(arr) - 1; i > 0 && count < 10; i--)
    {
        if (bitset_getbit(arr, i))
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