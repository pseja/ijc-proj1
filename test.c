#include "bitset.h"

int main()
{
    printf("Alokuju pole...\n");
    bitset_alloc(pole, 100L);
    bitset_index_t bitset_size_velikost = bitset_size(pole);

    printf("bitset_size promenna: %lu\nbitset_size makro: %lu\n\n", bitset_alloc_size, bitset_size_velikost);

    printf("Vypisuju...\n");
    for (bitset_index_t i = 0; i < bitset_alloc_size; i++)
    {
        printf("%lu\n", pole[i]);
    }

    printf("\n");

    printf("Nastavuju 64 bit na true...\n");
    bitset_setbit(pole, 64, true);

    printf("Vypisuju...\n");
    for (bitset_index_t i = 0; i < bitset_alloc_size; i++)
    {
        printf("%lu\n", pole[i]);
    }

    printf("Dostavam bity z pole...\n");
    bitset_index_t nulka = bitset_getbit(pole, 0);
    bitset_index_t sedesatctyri = bitset_getbit(pole, 64);

    printf("nulka: %lu\nsedesatctyri: %lu\n", nulka, sedesatctyri);

    printf("Vyplnuju pole 1...\n");
    bitset_fill(pole, true);

    printf("Vypisuju...\n");
    for (bitset_index_t i = 0; i < bitset_alloc_size; i++)
    {
        printf("%lu\n", pole[i]);
    }

    printf("\nULONG_MAX pro kontrolu: %lu\n\n", ULONG_MAX);

    printf("Vyplnuju pole 0...\n");
    bitset_fill(pole, false);

    printf("Vypisuju...\n");
    for (bitset_index_t i = 0; i < bitset_alloc_size; i++)
    {
        printf("%lu\n", pole[i]);
    }

    printf("\n");

    bitset_free(pole);
    return 0;
}