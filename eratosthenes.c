#include "eratosthenes.h"
#include <math.h>

#define DEBUG

void Eratosthenes(bitset_t pole)
{
    bitset_index_t bitset_size_velikost = bitset_size(pole);
    bitset_index_t bitset_size_sqrt = ceil(sqrt((double)bitset_size_velikost));

#ifdef DEBUG
    printf("sqrt: %lu\n", bitset_size_sqrt);
#endif
    // 1) Nastavíme bitové pole p o rozměru N na samé 1.
    bitset_fill(pole, true);
#ifdef DEBUG
    for (bitset_index_t test = 0; test < bitset_size_velikost; test++)
    {
        printf("%lu ", bitset_getbit(pole, test));
    }
#endif
    // Nastavíme p[0]=0; p[1]=0; // 0 a 1 nejsou prvočísla index i nastavit na 2
    bitset_setbit(pole, 0, false);
    bitset_setbit(pole, 1, false);

    printf("\n");
#ifdef DEBUG
    for (bitset_index_t test = 0; test < bitset_size_velikost; test++)
    {
        printf("%lu ", bitset_getbit(pole, test));
    }

    printf("\nbitset_size_sqrt: %lu\n", bitset_size_sqrt);
#endif
    // 2) Vybereme nejmenší index i, takový, že p[i]==1. Potom je i prvočíslo
    for (bitset_index_t i = 2; i < bitset_size_sqrt; i++)
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
    }
}
