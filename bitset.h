#ifndef BITSET_H
#define BITSET_H

#include "error.h"
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

// Calculates the size of unsigned long in bits
#define ULONG_BITS ((sizeof(bitset_index_t)) * (__CHAR_BIT__))

// Calculates if the bitset needs to be increased by 1 to fit all the bits
#define SIZE_PLUS_ONE(velikost) (((velikost) % (ULONG_MAX)) ? (1) : (0))

// Calculates the size for the bitset
#define CALCULATE_BITSET_SIZE(velikost) ((((velikost) / (ULONG_MAX)) + ((SIZE_PLUS_ONE(velikost)) + (1))))

/*
*pole bude big-endian od 1 indexu do posledního indexu
TODO: vymyslet jak inicializovat pole, něco už mám, ale nevím jestli to funguje
TODO: vymyslet jak alokovat pole, něco už mám, ale nevím jestli to funguje
TODO: vyřešit inline funkce
*/

// Creates a bitset locally with the given name and size
#define bitset_create(jmeno_pole, velikost)                                                    \
    do                                                                                         \
    {                                                                                          \
        static_assert(velikost > 0, "bitset_create: Pole musí být větší než 0");               \
        static_assert(velikost <= __UINT_FAST64_MAX__, "bitset_create: Chyba alokace paměti"); \
        const bitset_index_t bitset_size = CALCULATE_BITSET_SIZE(velikost);                    \
        bitset_t jmeno_pole[bitset_size] = {[0] = (bitset_index_t)(velikost), 0};              \
        /*memset(&(jmeno_pole)[1], 0, (bitset_size - 1) * (sizeof(bitset_t)));*/               \
    } while (0)

// Allocates a bitset dynamically with the given name and size
#define bitset_alloc(jmeno_pole, velikost)                                        \
    do                                                                            \
    {                                                                             \
        assert((bitset_index_t)velikost > 0);                                     \
        assert((bitset_index_t)velikost <= __UINT_FAST64_MAX__);                  \
        const bitset_index_t bitset_size = CALCULATE_BITSET_SIZE(velikost);       \
        bitset_t jmeno_pole = (bitset_t *)calloc(bitset_size * sizeof(bitset_t)); \
        if (jmeno_pole == NULL)                                                   \
        {                                                                         \
            error_exit("bitset_alloc: Chyba alokace paměti");                     \
        }                                                                         \
        jmeno_pole[0] = (bitset_index_t)velikost;                                 \
    } while (0)

#ifndef USE_INLINE

// Frees the bitset
#define bitset_free(jmeno_pole) (free(jmeno_pole))

// Returns the size of the bitset
#define bitset_size(jmeno_pole) (jmeno_pole[0])

// Sets the bit at the given index to the given boolean value
#define bitset_setbit(jmeno_pole, index, bool_vyraz)                                                 \
    do                                                                                               \
    {                                                                                                \
        bitset_index_t index = (bitset_index_t)index + ULONG_BITS;                                   \
        bitset_index_t velikost = bitset_size(jmeno_pole);                                           \
        if (index >= velikost)                                                                       \
        {                                                                                            \
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index - ULONG_BITS, velikost); \
        }                                                                                            \
        else                                                                                         \
        {                                                                                            \
            bitset_index_t maska = 1UL << (index % ULONG_BITS);                                      \
            if (bool_vyraz)                                                                          \
            {                                                                                        \
                jmeno_pole[index / ULONG_BITS] |= maska;                                             \
            }                                                                                        \
            else                                                                                     \
            {                                                                                        \
                jmeno_pole[index / ULONG_BITS] &= ~maska;                                            \
            }                                                                                        \
        }                                                                                            \
        while (0)

// Returns the bit at the given index
#define bitset_getbit(jmeno_pole, index)                                                             \
    do                                                                                               \
    {                                                                                                \
        bitset_index_t index = (bitset_index_t)index + ULONG_BITS;                                   \
        bitset_index_t velikost = bitset_size(jmeno_pole);                                           \
        if (index >= velikost)                                                                       \
        {                                                                                            \
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", index - ULONG_BITS, velikost); \
        }                                                                                            \
        else                                                                                         \
        {                                                                                            \
            (jmeno_pole[(index / ULONG_BITS) + 1] >> (index % ULONG_BITS)) & 1UL;                    \
        }                                                                                            \
    } while (0)

#else

// Frees the bitset
void bitset_free(bitset_t jmeno_pole);

// Returns the size of the bitset
bitset_index_t bitset_size(bitset_t jmeno_pole);

// Sets the bit at the given index to the given boolean value
void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz);

// Returns the bit at the given index
bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

#endif /* !USE_INLINE */

#endif /* BITSET_H */
