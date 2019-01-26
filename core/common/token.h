#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TOKEN_WHITESPACE 0
#define TOKEN_NUMBER 1
#define TOKEN_FUNCTION 2
#define TOKEN_SEPARATOR 3
#define TOKEN_LEFT_ASSOCIATIVE_OPERATOR 4
#define TOKEN_RIGHT_ASSOCIATIVE_OPERATOR 5
#define TOKEN_LEFT_BRACKET 6
#define TOKEN_RIGHT_BRACKET 7

#define PLUS_OPERATOR_PRIORITY 1
#define MINUS_OPERATOR_PRIORITY 1
#define MULTIPLICATION_OPERATOR_PRIORITY 2
#define DIVISION_OPERATOR_PRIORITY 2
#define MODULO_OPERATOR_PRIORITY 2
#define FACTORIAL_OPERATOR_PRIORITY 3
#define EXP_OPERATOR_PRIORITY 3

#define TOKEN_INTERNAL_ERR_INVALID_TOKEN -1
#define TOKEN_INTERNAL_ERR_INVALID_OPERATOR -2
#define TOKEN_INTERNAL_TOKEN_IS_NOT_AN_OPERATOR -3

typedef struct {
    char* tokenString;
    int tokenType;
    unsigned int originalPosition;
} Token;

Token createToken(const char* tokenString, int tokenType, unsigned int originalPosition);

Token tokenDeepClone(const Token *tp);

int getOperatorPriority(const Token* tp);

char* tokenToString(const Token *tp);

void freeToken(Token* tp);
