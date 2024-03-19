#include "eratosthenes.h"
#include <math.h>

// #define DEBUG

void Eratosthenes(bitset_t pole)
{
    bitset_index_t bitset_size_velikost = bitset_size(pole);
    bitset_index_t bitset_size_sqrt = ceil(sqrt((double)bitset_size_velikost));

    // Rychlé nastavení sudých čísel na 0 na 32 a 64 bitových systémech
    if (ULONG_BIT_COUNT == 32)
    {
        for (bitset_index_t i = 1; i <= CALCULATE_BITSET_SIZE(bitset_size_velikost); i++)
        {
            pole[i] = (bitset_index_t)0xAAAAAAAA;
        }
    }
    else if (ULONG_BIT_COUNT == 64)
    {
        for (bitset_index_t i = 1; i <= CALCULATE_BITSET_SIZE(bitset_size_velikost); i++)
        {
            pole[i] = (bitset_index_t)0xAAAAAAAAAAAAAAAA;
        }
    }
    else
    {
        for (bitset_index_t i = 0; i <= bitset_size_velikost; i += 2)
        {
            bitset_setbit(pole, i, false);
        }
    }

    // Nastavení lichých násobků 3 na 0
    for (bitset_index_t i = 9; i <= bitset_size_velikost; i += 6)
    {
        bitset_setbit(pole, i, false);
    }

#ifdef DEBUG
    printf("sqrt: %lu\n", bitset_size_sqrt);

    for (bitset_index_t test = 0; test < bitset_size_velikost; test++)
    {
        printf("%lu ", bitset_getbit(pole, test));
    }
#endif
    // Nastavíme p[1]=0; p[2]=1 kvůli rychlému nastavování
    bitset_setbit(pole, 1, false);
    bitset_setbit(pole, 2, true);

#ifdef DEBUG
    printf("\n");

    for (bitset_index_t test = 0; test < bitset_size_velikost; test++)
    {
        printf("%lu ", bitset_getbit(pole, test));
    }

    printf("\nbitset_size_sqrt: %lu\n", bitset_size_sqrt);
#endif
    // 2) Vybereme nejmenší index i, takový, že p[i]==1. Potom je i prvočíslo
    for (bitset_index_t i = 5; i < bitset_size_sqrt; i += 4)
    {
        if (bitset_getbit(pole, i))
        {
            // 3) Pro všechny násobky i nastavíme bit p[n*i] na 0 ('vyškrtneme' všechny násobky i - nejsou to prvočísla)
            for (bitset_index_t n = 2; n * i < bitset_size_velikost; n++)
            {
                bitset_setbit(pole, n * i, false);
            }
#ifdef DEBUG
            printf("i: %lu\n", i);

            for (bitset_index_t test = 0; test < bitset_size_velikost; test++)
            {
                printf("%lu ", bitset_getbit(pole, test));
            }
            printf("\n");
#endif
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
