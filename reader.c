#include <string.h>
#include <stdlib.h>
#include "reader.h"

char *StripWhitespace(char *s)
{
    int len = strlen(s), idx = 0;
    char *result = malloc(len);
    for (int i = 0; i < len; i++)
    {
        if (s[i] != ' ' && s[i] != '\n')
        {
            result[idx] = s[i];
            idx++;
        }

        if (s[i] == '\0')
        {
            result[idx] = '\0';
            break;
        }
    }

    return result;
}

Reader NewReader(char *input)
{
    char *p = StripWhitespace(input);

    int len = strlen(p);
    Reader r = {.input = p,
                .index = 0,
                .length = len};

    return r;
}

int CloseReader(Reader *reader)
{
    free(reader->input);

    return 0;
}

char ScanChar(Reader *reader)
{
    char c = reader->input[reader->index];
    reader->index++;

    return c;
};

char NextChar(Reader *reader)
{
    char c = reader->input[reader->index];
    return c;
};