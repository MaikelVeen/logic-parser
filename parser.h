#include "lexer.h"

#ifndef LOGIC_PARSER_PARSER_H
#define LOGIC_PARSER_PARSER_H

typedef enum NodeType
{
    BinaryOperator,
    UnaryOperator,
    Variable
} NodeType;

// Node represent a node in the abstract
// syntax tree.
typedef struct ParseTree {
    NodeType Type;
    Token *Data;
    struct ParseTree *Left;
    struct ParseTree *Right;
}ParseTree;

// Traverses the node tree and prints the
// lexeme representations of the nodes.
void PrintSentence(ParseTree *tree);

// Evaluates the node
_Bool Evaluate(ParseTree *tree);

// Top level function to call parse.
void Parse(Lexer *lexer);

#define PARSING_ERROR -1
#define SUBTREE_OK 0
#define MEMORY_ERROR 1

int ParseProposition(Lexer *lexer, ParseTree **tree);
int ParseSentence(Lexer *lexer, ParseTree **tree);
int ParseComplexSentence(Lexer *lexer, ParseTree **tree);

ParseTree *AllocateParseTree();
ParseTree *NewParseTree(NodeType type, char lexeme);

void FreeNode(ParseTree *node);
#endif //LOGIC_PARSER_PARSER_H
