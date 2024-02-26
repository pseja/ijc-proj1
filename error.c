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

int main()
{
    return 0;
}
