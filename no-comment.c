#include "error.h"

int main(int argc, char **argv)
{
    FILE *file;

    if (argc > 1)
    {
        char *filename = argv[1];
        file = fopen(filename, "r");

        if (file == NULL)
        {
            fprintf(stderr, "Error: Failed opening file: %s!\n", filename);
            return 1;
        }
    }
    else
    {
        file = stdin;
    }

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
            }
            else
            {
                state = 2;
                putchar('*');
            }
            break;

        case 5:
            if (c == '\n')
            {
                state = 3;
                putchar('\n');
            }
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

    if (file != stdin)
    {
        fclose(file);
    }

    if (state != 0)
    {
        fprintf(stderr, "Error: Unknown state!\n");
        return 2;
    }

    return 0;
}