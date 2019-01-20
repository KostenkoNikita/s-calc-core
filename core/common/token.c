#include "token.h"

Token createToken(const char* tokenString, const int tokenType, const int originalPosition) {
    Token t;
    t.tokenType = tokenType;
    const size_t strLength = strlen(tokenString);
    t.tokenString = (char*)calloc(strLength + 1, sizeof(char));
    strcpy(t.tokenString, tokenString);
    return t;
}

int getOperatorPriority(const Token* t) {
    const char* tokenString = t->tokenString;
    const size_t tokenStringLength = strlen(tokenString);
    if(tokenStringLength == 0) {
        return TOKEN_INTERNAL_ERR_INVALID_TOKEN;
    }
    if(tokenStringLength == 1) {
        const char c = tokenString[0];
        switch (c) {
            case '+':
                return PLUS_OPERATOR_PRIORITY;
            case '-':
                return MINUS_OPERATOR_PRIORITY;
            case '*':
                return MULTIPLICATION_OPERATOR_PRIORITY;
            case '/':
                return DIVISION_OPERATOR_PRIORITY;
            case '%':
                return MODULO_OPERATOR_PRIORITY;
            case '^':
                return EXP_OPERATOR_PRIORITY;
            case '!':
                return FACTORIAL_OPERATOR_PRIORITY;
            default:
                return TOKEN_INTERNAL_ERR_INVALID_OPERATOR;
        }
    } else if(strcmp(tokenString, "mod") == 0) {
        return MODULO_OPERATOR_PRIORITY;
    } else {
        bool isFactorial = true;
        for(int i = 0; i < tokenStringLength; i++) {
            const char c = tokenString[i];
            if(c != '!') {
                isFactorial = false;
                break;
            }
        }
        if(isFactorial == true) {
            return FACTORIAL_OPERATOR_PRIORITY;
        } else {
            return TOKEN_INTERNAL_ERR_INVALID_OPERATOR;
        }
    }
}