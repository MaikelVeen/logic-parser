#include "reader.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *input = "!( p | q ) & r;";
    Reader reader = NewReader(input);
    Lexer lexer = NewLexer(&reader);

    Parse(&lexer);

    printf("\n END");
    CloseReader(&reader);
}