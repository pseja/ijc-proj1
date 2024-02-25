#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern void warning(const char *fmt, ...);
extern void error_exit(const char *fmt, ...);

#endif
