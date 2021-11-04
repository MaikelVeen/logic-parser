#include "reader.h"
#include "token.h"

#ifndef LEXER
#define LEXER

typedef struct Lexer
{
    Reader *reader;
    Token *next;
    int index;
} Lexer;

// Returns a new Lexer.
Lexer NewLexer(Reader *reader);

// Returns the current next token.
Token *NextToken(Lexer *lexer);

// Advances the lexer to the next token.
Token *ScanToken(Lexer *lexer);

int CloseLexer(Lexer *lexer);

#endif