#ifndef BITSET_H
#define BITSET_H

#include "error.h"
#include <string.h>
#include <assert.h>

typedef unsigned long bitset_t;
typedef unsigned long bitset_index_t;

// Calculates the size of unsigned long in bits
#define ULONG_MAX ((sizeof(bitset_t)) * (__CHAR_BIT__))

// Calculates if the bitset needs to be increased by 1 to fit all the bits
#define MODULO(velikost) (((velikost) % (ULONG_MAX)) ? (1) : (0))

// Calculates the size for the bitset
#define CALCULATE_BITSET_SIZE(velikost) ((((velikost) / (ULONG_MAX)) + ((MODULO(velikost)) + (1))))

// Creates a bitset locally with the given name and size
#define bitset_create(jmeno_pole, velikost)                                                              \
    do                                                                                                   \
    {                                                                                                    \
        static_assert((bitset_t)velikost != 0, "bitset_create: Chyba alokace paměti");                   \
        static_assert((bitset_t)velikost <= __UINT_FAST64_MAX__, "bitset_create: Chyba alokace paměti"); \
        const bitset_t bitset_size = CALCULATE_BITSET_SIZE(velikost);                                    \
        bitset_t jmeno_pole[bitset_size] = {[0] = (velikost), 0};                                        \
        memset(&(jmeno_pole)[1], 0, (bitset_size - 1) * (sizeof(bitset_t)));                             \
    } while (0)

// Allocates a bitset dynamically with the given name and size
#define bitset_alloc(jmeno_pole, velikost)                                         \
    do                                                                             \
    {                                                                              \
        assert((bitset_t)velikost != 0);                                           \
        assert((bitset_t)velikost <= __UINT_FAST64_MAX__);                         \
        const bitset_t bitset_size = CALCULATE_BITSET_SIZE(velikost);              \
        bitset_t *jmeno_pole = (bitset_t *)calloc(bitset_size * sizeof(bitset_t)); \
        if (jmeno_pole == NULL)                                                    \
        {                                                                          \
            error_exit("bitset_alloc: Chyba alokace paměti");                      \
        }                                                                          \
        jmeno_pole[0] = (bitset_t)velikost;                                        \
    } while (0)

#ifndef INLINE_FUNKCE
#define INLINE_FUNKCE

#endif /* INLINE_FUNKCE */

#endif /* BITSET_H */
