// error.c
// Řešení IJC-DU1, příklad b), 20.3.2024
// Autor: Lukáš Pšeja, FIT
// Přeloženo: gcc 11.4.0

#include "error.h"

void warning(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);

    va_end(args);
}

void error_exit(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);

    va_end(args);

    exit(1);
}
