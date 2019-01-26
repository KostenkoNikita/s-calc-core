#include "token_stack.h"

TokenStack* initTokenStack(){
    TokenStack* sp = (TokenStack*)malloc(sizeof(TokenStack));
    sp->data = (Token*)calloc(TOKEN_STACK_INITIAL_CAPACITY, sizeof(Token));
    sp->capacity = TOKEN_STACK_INITIAL_CAPACITY;
    sp->top = TOKEN_STACK_INITIAL_TOP_INDEX;
    return sp;
}

bool isTokenStackFull(const TokenStack *sp){
    return sp->top + 1 == sp->capacity;
}

bool isTokenStackEmpty(const TokenStack *sp){
    return sp->top == TOKEN_STACK_INITIAL_TOP_INDEX;
}

void tokenStackPush(TokenStack *sp, Token* tp){
    if(isTokenStackFull(sp)) {
        sp->capacity *= TOKEN_STACK_CAPACITY_MULTIPLIER;
        sp->data = (Token*)realloc(sp->data, sizeof(Token) * sp->capacity);
    }
    sp->data[++sp->top] = tokenDeepClone(tp);
}

Token tokenStackPop(TokenStack *sp){
    return sp->data[sp->top--];
}

Token* tokenStackPeek(const TokenStack *sp){
    if(isTokenStackEmpty(sp)) {
        return NULL;
    }
    return &sp->data[sp->top];
}

void tokenStackClear(const TokenStack *sp) {
    const int top = sp->top;
    if(top == TOKEN_STACK_INITIAL_TOP_INDEX) {
        return;
    }
    for(int i = 0; i <= top; i++) {
        freeToken(&sp->data[i]);
    }
}

void freeTokenStack(TokenStack* s) {
    tokenStackClear(s);
    free(s->data);
    free(s);
}