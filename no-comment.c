// error.h
// Řešení IJC-DU1, příklad b), 20.3.2024
// Autor: Lukáš Pšeja, FIT
// Přeloženo: gcc 11.4.0
// musí být definováno _POSIC_C_SOURCE 200809L, jinak nastanou při překladu problémy s funkcí fileno()

#define _POSIX_C_SOURCE 200809L
#include "error.h"
#include <sys/stat.h>
#include <unistd.h>

FILE *handleFile(int argc, char **argv)
{
    FILE *file;

    if (argc > 1)
    {
        char *filename = argv[1];
        file = fopen(filename, "r");

        if (file == NULL)
        {
            error_exit("Failed opening file: %s!\n", filename);
        }
    }
    else
    {
        file = stdin;
    }

    return file;
}

int stateMachine(FILE *file)
{
    int state = 0;
    int c = 0;

    while ((c = fgetc(file)) != EOF)
    {
        switch (state)
        {
        case 0:
            if (c == '/')
            {
                state = 1;
            }
            else if (c == '"')
            {
                state = 6;
                putchar('"');
            }
            else if (c == '\'')
            {
                state = 7;
                putchar('\'');
            }
            else
            {
                putchar(c);
            }
            break;

        case 1:
            if (c == '/')
            {
                state = 3;
            }
            else if (c == '*')
            {
                state = 2;
            }
            else
            {
                putchar('/');
                putchar(c);
                state = 0;
            }
            break;

        case 2:
            if (c == '*')
            {
                state = 4;
            }
            break;

        case 3:
            if (c == '\\')
            {
                state = 5;
            }
            else if (c == '\n')
            {
                state = 0;
                putchar('\n');
            }
            break;

        case 4:
            if (c == '/')
            {
                state = 0;
                putchar(' ');
            }
            else if (c == '*')
            {
                continue;
            }
            else
            {
                state = 2;
            }
            break;

        case 5:
            if (c == '\n')
            {
                putchar('\n');
            }
            state = 3;
            break;

        case 6:
            if (c == '\\')
            {
                state = 8;
            }
            else if (c == '"')
            {
                state = 0;
            }
            putchar(c);
            break;

        case 7:
            if (c == '\\')
            {
                state = 9;
            }
            else if (c == '\'')
            {
                state = 0;
            }
            putchar(c);
            break;

        case 8:
            state = 6;
            putchar(c);
            break;

        case 9:
            state = 7;
            putchar(c);
            break;
        }
    }

    return state;
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        error_exit("Too many arguments.\n");
    }

    // stat struct for handling input file == output file
    struct stat stat_input, stat_output;

    FILE *file = handleFile(argc, argv);

    if (file != stdin)
    {
        fstat(fileno(file), &stat_input);
        fstat(STDOUT_FILENO, &stat_output);

        if (stat_input.st_ino == stat_output.st_ino)
        {
            if (fclose(file) == EOF)
            {
                error_exit("Failed to close input file!\n");
            }
            error_exit("Input file is the same as output file!\n");
        }
    }

    int state = stateMachine(file);

    if (file != stdin)
    {
        if (fclose(file) == EOF)
        {
            error_exit("Failed to close input file!\n");
        }
    }

    if (state != 0)
    {
        error_exit("Unclosed comment or string!\n");
    }

    return 0;
}
