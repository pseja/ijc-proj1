// bitset.h
// Řešení IJC-DU1, příklad A), 20.3.2024
// Autor: Lukáš Pšeja, FIT
// Přeloženo: gcc 11.4.0

#ifndef BITSET_H
#define BITSET_H

#include "error.h"
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

// Calculates the size of unsigned long in bits
#define ULONG_BIT_COUNT ((sizeof(bitset_index_t)) * (__CHAR_BIT__))

// Calculates if the bitset needs to be increased by 1 to fit all the bits
#define SIZE_PLUS_ONE(velikost) (((velikost) % (ULONG_BIT_COUNT)) ? (1) : (0))

// Calculates the size for the bitset
#define CALCULATE_BITSET_SIZE(velikost) ((((velikost) / (ULONG_BIT_COUNT)) + ((SIZE_PLUS_ONE(velikost)) + (1))))

// Creates a bitset locally with the given name and size
#define bitset_create(jmeno_pole, velikost)                                        \
    static_assert((velikost) > 0, "bitset_create: Pole musí být větší než 0");     \
    static_assert((velikost) <= ULONG_MAX, "bitset_create: Chyba alokace paměti"); \
    const bitset_index_t bitset_create_size = CALCULATE_BITSET_SIZE(velikost);     \
    bitset_index_t jmeno_pole[bitset_create_size];                                 \
    jmeno_pole[0] = (bitset_index_t)velikost;

// Allocates a bitset dynamically with the given name and size
#define bitset_alloc(jmeno_pole, velikost)                                             \
    assert((bitset_index_t)velikost > 0);                                              \
    assert((bitset_index_t)velikost <= ULONG_MAX);                                     \
    const bitset_index_t bitset_alloc_size = CALCULATE_BITSET_SIZE(velikost);          \
    bitset_t jmeno_pole = (bitset_t)calloc(bitset_alloc_size, sizeof(bitset_index_t)); \
    if (jmeno_pole == NULL)                                                            \
    {                                                                                  \
        error_exit("bitset_alloc: Chyba alokace paměti");                              \
    }                                                                                  \
    jmeno_pole[0] = (bitset_index_t)velikost;

#ifndef USE_INLINE

// Frees the bitset
#define bitset_free(jmeno_pole) (free(jmeno_pole))

// Returns the size of the bitset
#define bitset_size(jmeno_pole) (jmeno_pole[0])

// Fills the array's bits with 0s or 1s
#define bitset_fill(jmeno_pole, bool_vyraz)                                                   \
    do                                                                                        \
    {                                                                                         \
        bitset_index_t bitset_fill_velikost = CALCULATE_BITSET_SIZE(bitset_size(jmeno_pole)); \
        bitset_index_t bitset_fill_filler = (bool_vyraz) ? -1 : 0;                            \
        for (bitset_index_t i = 1; i < bitset_fill_velikost; i++)                             \
        {                                                                                     \
            jmeno_pole[i] = bitset_fill_filler;                                               \
        }                                                                                     \
    } while (0)

// Sets the bit at the given index to the given boolean value
#define bitset_setbit(jmeno_pole, index, bool_vyraz)                                                                    \
    do                                                                                                                  \
    {                                                                                                                   \
        bitset_index_t setbit_index = (bitset_index_t)index + ULONG_BIT_COUNT;                                          \
        bitset_index_t setbit_velikost = bitset_size(jmeno_pole);                                                       \
        if (setbit_index - ULONG_BIT_COUNT > setbit_velikost)                                                           \
        {                                                                                                               \
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", setbit_index - ULONG_BIT_COUNT, setbit_velikost); \
        }                                                                                                               \
        else                                                                                                            \
        {                                                                                                               \
            bitset_index_t setbit_maska = 1UL << (setbit_index % ULONG_BIT_COUNT);                                      \
            if (bool_vyraz)                                                                                             \
            {                                                                                                           \
                jmeno_pole[setbit_index / ULONG_BIT_COUNT] |= setbit_maska;                                             \
            }                                                                                                           \
            else                                                                                                        \
            {                                                                                                           \
                jmeno_pole[setbit_index / ULONG_BIT_COUNT] &= ~setbit_maska;                                            \
            }                                                                                                           \
        }                                                                                                               \
    } while (0)

// Returns the bit at the given index, if the index is out of range, returns 2
#define bitset_getbit(jmeno_pole, index) (((bitset_index_t)index > bitset_size(jmeno_pole)) ? 2 : jmeno_pole[(((bitset_index_t)index + ULONG_BIT_COUNT) / ULONG_BIT_COUNT)] >> (((bitset_index_t)index + ULONG_BIT_COUNT) % ULONG_BIT_COUNT) & 1UL)

#else

// Frees the bitset
void bitset_free(bitset_t jmeno_pole);

// Returns the size of the bitset
bitset_index_t bitset_size(bitset_t jmeno_pole);

// Fills the array's bits with 0s or 1s
void bitset_fill(bitset_t jmeno_pole, bool bool_vyraz);

// Sets the bit at the given index to the given boolean value
void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, bool bool_vyraz);

// Returns the bit at the given index
bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

#endif /* !USE_INLINE */

#endif /* BITSET_H */
