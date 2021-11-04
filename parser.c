#include "lexer.h"
#include "parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* BNF for Basic Propositional Logic
 *
 * <Sentence> ::= <Proposition> | <ComplexSentence> | (<ComplexSentence>)
 * <Proposition> ::= P | Q | R ...
 * <ComplexSentence> ::= (<Sentence>) |
 *                        !<Sentence> |
 *            <Sentence> | <Sentence> |
 *            <Sentence> & <Sentence> |
 *            <Sentence> = <Sentence> |
 *            <Sentence> v <Sentence> |
 * */

// Allocates a new ParseTree in memory
// and explicitly sets the pointer to subtree to NULL.
// Returns a pointer.
ParseTree *AllocateParseTree() {
    ParseTree *node = malloc(sizeof(ParseTree));
    if (node == NULL) {
        return NULL;
    }

    node->Right = NULL;
    node->Left = NULL;

    return node;
};

int ParseProposition(Lexer *lexer, ParseTree **tree) {
    Token *token = NextToken(lexer);

    if (token->Type == Proposition) {
        ParseTree *t = *tree;
        t->Data = token;
        t->Type = Variable;
        ScanToken(lexer);

        return SUBTREE_OK;
    }

    // Expected proposition but got something else.
    return PARSING_ERROR;
}

int ParseComplexSentence(Lexer *lexer, ParseTree **tree) {
    int status = 0;

    if (NextToken(lexer)->Type == LeftParen) {
        ScanToken(lexer);

        status = ParseSentence(lexer, tree);
        if (status != SUBTREE_OK) {
            return status;
        }

        while (NextToken(lexer)->Type != RightParen) {
            status = ParseSentence(lexer, tree);
            if (status != SUBTREE_OK) {
                return status;
            }
        }

        ScanToken(lexer);
    }
        // Token is type of negation.
    else if (NextToken(lexer)->Type == Negation) {
        Token *tok = ScanToken(lexer);
        ParseTree *argument = AllocateParseTree();

        // Parse the argument of the negation
        int status = ParseSentence(lexer, &argument);
        if (status != SUBTREE_OK) {
            return status;
        }

        ParseTree *t = *tree;
        t->Data = tok;
        t->Type = UnaryOperator;
        t->Left = argument;
    } else if (NextToken(lexer)->Type == Conjunction) {
        Token *tok = ScanToken(lexer);

        ParseTree *right = AllocateParseTree();
        int status = ParseSentence(lexer, &right);
        if (status != SUBTREE_OK) {
            return status;
        }

        ParseTree *newTree = AllocateParseTree();
        newTree->Data = tok;
        newTree->Left = *tree;
        newTree->Right = right;
        newTree->Type = BinaryOperator;

        *tree = newTree;
    }
    else if (NextToken(lexer)->Type == Disjunction) {
        Token *tok = ScanToken(lexer);

        ParseTree *right = AllocateParseTree();
        int status = ParseSentence(lexer, &right);
        if (status != SUBTREE_OK) {
            return status;
        }

        ParseTree *newTree = AllocateParseTree();
        newTree->Data = tok;
        newTree->Left = *tree;
        newTree->Right = right;
        newTree->Type = BinaryOperator;

        *tree = newTree;
    }

    return status;
}

int ParseSentence(Lexer *lexer, ParseTree **tree) {
    TokenType type = NextToken(lexer)->Type;

    if (type == Proposition) {
        return ParseProposition(lexer, tree);
    } else {
        return ParseComplexSentence(lexer, tree);
    }
}

void Parse(Lexer *lexer) {
    int status;
    ParseTree *tree = AllocateParseTree();

    while (NextToken(lexer)->Type != Terminator) {
        status = ParseSentence(lexer, &tree);
        if (status != SUBTREE_OK) {
            printf("Parsing result status: %d", status);

            return;
        }
    }

    PrintSentence(tree);
    printf("\n");
    printf("Parsing result status: %d", status);
}

void PrintSentence(ParseTree *tree) {
    switch (tree->Type) {
        case BinaryOperator:
            printf("( ");
            PrintSentence(tree->Left);
            printf(" %c ", tree->Data->Lexeme);
            PrintSentence(tree->Right);
            printf(" )");
            break;
        case Variable:
            printf("%c", tree->Data->Lexeme);
            break;
        case UnaryOperator:
            printf("%c", tree->Data->Lexeme);
            PrintSentence(tree->Left);
            break;
    }
}



