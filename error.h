// error.h
// Řešení IJC-DU1, příklad b), 20.3.2024
// Autor: Lukáš Pšeja, FIT
// Přeloženo: gcc 11.4.0

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif
