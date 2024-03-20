// eratosthenes.c
// Řešení IJC-DU1, příklad a), 20.3.2024
// Autor: Lukáš Pšeja, FIT
// Přeloženo: gcc 11.4.0

#include "eratosthenes.h"
#include <math.h>

// #define DEBUG

void Eratosthenes(bitset_t pole)
{
    bitset_index_t bitset_size_velikost = bitset_size(pole);
    bitset_index_t bitset_size_sqrt = ceil(sqrt((double)bitset_size_velikost));

    // Fast fill of the bitset on 32 and 64 bit systems
    if (ULONG_BIT_COUNT == 32)
    {
        for (bitset_index_t i = 1; i < CALCULATE_BITSET_SIZE(bitset_size_velikost); i++)
        {
            pole[i] = (bitset_index_t)0xAAAAAAAA;
        }
    }
    else if (ULONG_BIT_COUNT == 64)
    {
        for (bitset_index_t i = 1; i < CALCULATE_BITSET_SIZE(bitset_size_velikost); i++)
        {
            pole[i] = (bitset_index_t)0xAAAAAAAAAAAAAAAA;
        }
    }
    else
    {
        for (bitset_index_t i = 0; i < bitset_size_velikost; i += 2)
        {
            bitset_setbit(pole, i, false);
        }
    }

    // Setting odd multiples of 3 to 0
    for (bitset_index_t i = 9; i < bitset_size_velikost; i += 6)
    {
        bitset_setbit(pole, i, false);
    }

    // Set p[1]=0; p[2]=1 because of the fast fill
    bitset_setbit(pole, 1, false);
    bitset_setbit(pole, 2, true);

    // 2) Choose the smallest index i such that p[i]==1. Then i is a prime number
    for (bitset_index_t i = 5; i < bitset_size_sqrt; i += 4)
    {
        if (bitset_getbit(pole, i))
        {
            // 3) For all multiples of i, set the p[n*i] bit to 0 ('discard' all multiples of i - they are not prime numbers)
            for (bitset_index_t n = 2; n * i < bitset_size_velikost; n++)
            {
                bitset_setbit(pole, n * i, false);
            }
        }

        i += 2;

        if (bitset_getbit(pole, i))
        {
            for (bitset_index_t n = 2; n * i < bitset_size_velikost; n++)
            {
                bitset_setbit(pole, n * i, false);
            }
        }
    }
}
