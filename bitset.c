#include "bitset.h"

#ifdef USE_INLINE

inline void bitset_free(bitset_t jmeno_pole)
{
    free(jmeno_pole);
}

inline bitset_index_t bitset_size(bitset_t jmeno_pole)
{
    return jmeno_pole[0];
}

inline void bitset_fill(bitset_t jmeno_pole, bool bool_vyraz)
{
    bitset_index_t bitset_fill_velikost = CALCULATE_BITSET_SIZE(bitset_size(jmeno_pole));
    bitset_index_t bitset_fill_filler = (bool_vyraz) ? -1 : 0;

    for (bitset_index_t i = 1; i < bitset_fill_velikost; i++)
    {
        jmeno_pole[i] = bitset_fill_filler;
    }
}

inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz)
{
    bitset_index_t bitset_setbit_index = index + ULONG_BIT_COUNT;
    bitset_index_t bitset_setbit_velikost = bitset_size(jmeno_pole);

    if (bitset_setbit_index - ULONG_BIT_COUNT > bitset_setbit_velikost)
    {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", bitset_setbit_index - ULONG_BIT_COUNT, bitset_setbit_velikost);
    }
    else
    {
        bitset_index_t bitset_setbit_maska = 1UL << (bitset_setbit_index % ULONG_BIT_COUNT);

        if (bool_vyraz)
        {
            jmeno_pole[bitset_setbit_index / ULONG_BIT_COUNT] |= bitset_setbit_maska;
        }
        else
        {
            jmeno_pole[bitset_setbit_index / ULONG_BIT_COUNT] &= ~bitset_setbit_maska;
        }
    }
}

inline bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
{
    bitset_index_t bitset_getbit_index = index + ULONG_BIT_COUNT;
    bitset_index_t bitset_getbit_velikost = bitset_size(jmeno_pole);

    if (bitset_getbit_index - ULONG_BIT_COUNT > bitset_getbit_velikost)
    {
        return 2;
    }
    return (jmeno_pole[(bitset_getbit_index / ULONG_BIT_COUNT)] >> (bitset_getbit_index % ULONG_BIT_COUNT)) & 1UL;
}

#endif /* USE_INLINE */