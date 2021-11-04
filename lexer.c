#include "lexer.h"
#include "reader.h"
#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Returns a new Lexer.
Lexer NewLexer(Reader *reader)
{
    Lexer l = {.reader = reader,
               .index = 0,
               .next = 0};

    return l;
}

Token *AllocateToken() {
    Token *token = malloc(sizeof(Token));
    if(token == NULL) {
        return NULL;
    }

    return token;
}

void FreeToken(Token *token) {
    free(token);
}

void TokenFromChar(char c, Token *token)
{
   token->Lexeme = c;

   if(isalpha(c)) {
       token->Type= Proposition;
       return;
   }

   if(c == '0' || c == '1') {
       token->Type = TruthValue;
       return;
   }

    switch (c)
    {
        case '&':
            token->Type = Conjunction;
            break;
        case '|':
            token->Type = Disjunction;
            break;
        case '(':
            token->Type = LeftParen;
            break;
        case ')':
            token->Type = RightParen;
            break;
        case '!':
            token->Type = Negation;
            break;
        case ';':
            token->Type = Terminator;
            break;
        case '=':
            token->Type = Implication;
            break;
        default:
            token->Type = Invalid;
            break;
    }
}

// Sets the next token.
int fillNext(Lexer *lexer)
{
    if (!lexer->next)
    {
        Token *token = AllocateToken();

        // Read the next character.
        char c = ScanChar(lexer->reader);
        TokenFromChar(c, token);

        if (token->Type == Invalid)
        {
            printf("%c could not be parsed \n", c);
            return 1;
        }

        // Set the next to the gathered token.
        lexer->next = token;
    }


    // Successful operation.
    return 0;
}

Token *NextToken(Lexer *lexer)
{
    int s = fillNext(lexer);
    if (s > 0)
    {
        return 0;
    }

    return lexer->next;
}

Token *ScanToken(Lexer *lexer)
{
    int s = fillNext(lexer);
    if (s == 1)
    {
        return 0;
    }

    Token *result = lexer->next;
    lexer->next = 0;

    return result;
}