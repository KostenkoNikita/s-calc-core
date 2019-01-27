#pragma once

#include "token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_STACK_INITIAL_TOP_INDEX -1
#define TOKEN_STACK_INITIAL_CAPACITY 10
#define TOKEN_STACK_CAPACITY_MULTIPLIER 2

typedef struct {
    int top;
    unsigned int capacity;
    Token** data;
} TokenStack;

TokenStack* initTokenStack();

bool isTokenStackEmpty(const TokenStack *sp);

void tokenStackPush(TokenStack *sp, Token* tp);

Token* tokenStackPop(TokenStack *sp);

Token* tokenStackPeek(const TokenStack *sp);

void tokenStackClear(TokenStack *sp);

void freeTokenStack(TokenStack* s);




