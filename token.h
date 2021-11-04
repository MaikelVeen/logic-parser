#ifndef LOGIC_PARSER_TOKEN
#define LOGIC_PARSER_TOKEN

typedef enum TokenType
{
    Negation,
    Conjunction,
    Disjunction,
    Implication,
    Proposition,
    LeftParen,
    RightParen,
    Invalid,
    TruthValue,
    Terminator
} TokenType;

// A token is the data structure representing
// a tokenized output of the parser.
typedef struct Token {
    TokenType Type;
    char Lexeme;
}Token;

Token *AllocateToken();
void FreeToken(Token *token);

Token *NewToken(TokenType type, char lexeme);

#endif //LOGIC_PARSER_TOKEN