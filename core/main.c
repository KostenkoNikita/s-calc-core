#include <stdio.h>
#include "common/token_stack.h"
#include "common/token.h"

int main() {
    /*SOURCE CODE FOR LOCAL DEBUG*/
    TokenStack* sp= initTokenStack();
    Token t1 = createToken("12",TOKEN_NUMBER, 0);
    Token t2 = createToken("+",TOKEN_NUMBER, 2);
    Token t3 = createToken("42",TOKEN_NUMBER, 3);
    Token t4 = createToken("-",TOKEN_NUMBER, 5);
    Token t5 = createToken("17",TOKEN_NUMBER, 6);
    tokenStackPush(sp, &t1);
    tokenStackPush(sp, &t2);
    tokenStackPush(sp, &t3);
    tokenStackPush(sp, &t4);
    tokenStackPush(sp, &t5);

    printf("STACK TOP TEST (PEEK): %s\n", (tokenStackPeek(sp)->tokenString));

    Token pop_t5 = tokenStackPop(sp);
    Token pop_t4 = tokenStackPop(sp);
    Token pop_t3 = tokenStackPop(sp);
    Token pop_t2 = tokenStackPop(sp);
    Token pop_t1 = tokenStackPop(sp);
    printf("%s\n", pop_t1.tokenString);
    printf("%s\n", pop_t2.tokenString);
    printf("%s\n", pop_t3.tokenString);
    printf("%s\n", pop_t4.tokenString);
    printf("%s\n", pop_t5.tokenString);
    freeToken(&t1);
    freeToken(&t2);
    freeToken(&t3);
    freeToken(&t4);
    freeToken(&t5);

    freeToken(&pop_t1);
    freeToken(&pop_t2);
    freeToken(&pop_t3);
    freeToken(&pop_t4);
    freeToken(&pop_t5);
    freeTokenStack(sp);
    return 0;
}