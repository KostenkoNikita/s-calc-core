#include "token_stack.h"

bool isTokenStackFull(const TokenStack *sp){
    return sp->top + 1 == sp->capacity;
}

TokenStack* initTokenStack(){
    TokenStack* sp = (TokenStack*)malloc(sizeof(TokenStack));
    sp->data = (Token**)calloc(TOKEN_STACK_INITIAL_CAPACITY, sizeof(Token*));
    sp->capacity = TOKEN_STACK_INITIAL_CAPACITY;
    sp->top = TOKEN_STACK_INITIAL_TOP_INDEX;
    return sp;
}

bool isTokenStackEmpty(const TokenStack *sp){
    return sp->top == TOKEN_STACK_INITIAL_TOP_INDEX;
}

void tokenStackPush(TokenStack *sp, Token* tp){
    if(isTokenStackFull(sp)) {
        sp->capacity *= TOKEN_STACK_CAPACITY_MULTIPLIER;
        sp->data = (Token**)realloc(sp->data, sizeof(Token*) * sp->capacity);
    }
    sp->data[++sp->top] = tp;
}

Token* tokenStackPop(TokenStack *sp){
    if(isTokenStackEmpty(sp)) {
        return NULL;
    }
    return sp->data[sp->top--];
}

Token* tokenStackPeek(const TokenStack *sp){
    if(isTokenStackEmpty(sp)) {
        return NULL;
    }
    return sp->data[sp->top];
}

void tokenStackClear(TokenStack *sp) {
    while(!isTokenStackEmpty(sp)) {
        Token* tp = tokenStackPop(sp);
        freeToken(tp);
    }
}

void freeTokenStack(TokenStack* s) {
    tokenStackClear(s);
    free(s->data);
    free(s);
}