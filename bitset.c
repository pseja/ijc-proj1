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

inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz)
{
    bitset_index_t index = index + ULONG_BITS;
    bitset_index_t velikost = bitset_size(jmeno_pole);

    if (index >= velikost)
    {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index - ULONG_BITS, velikost);
    }
    else
    {
        bitset_index_t maska = 1UL << (index % ULONG_BITS);

        if (bool_vyraz)
        {
            jmeno_pole[index / ULONG_BITS] |= maska;
        }
        else
        {
            jmeno_pole[index / ULONG_BITS] &= ~maska;
        }
    }
}

inline bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index)
{
    bitset_index_t index = index + ULONG_BITS;
    bitset_index_t velikost = bitset_size(jmeno_pole);

    if (index >= velikost)
    {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index - ULONG_BITS, velikost);
    }
    else
    {
        return (jmeno_pole[(index / ULONG_BITS) + 1] >> (index % ULONG_BITS)) & 1UL;
    }
}

#endif /* USE_INLINE */