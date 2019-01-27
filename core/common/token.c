#include "token.h"

Token* createToken(const char* tokenString, const int tokenType, const unsigned int originalPosition) {
    Token* t = (Token*)malloc(sizeof(Token));
    t->tokenType = tokenType;
    t->originalPosition = originalPosition;
    t->tokenString = (char*)calloc(strlen(tokenString) + 1, sizeof(char));
    strcpy(t->tokenString, tokenString);
    return t;
}

Token* tokenDeepClone(const Token *tp) {
    return createToken(tp->tokenString, tp->tokenType, tp->originalPosition);
}

int getOperatorPriority(const Token* tp) {
    const int tokenType = tp->tokenType;
    if(tokenType != TOKEN_LEFT_ASSOCIATIVE_OPERATOR && tokenType != TOKEN_RIGHT_ASSOCIATIVE_OPERATOR) {
        return TOKEN_INTERNAL_TOKEN_IS_NOT_AN_OPERATOR;
    }
    const char* tokenString = tp->tokenString;
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

void freeToken(Token* tp) {
    free(tp->tokenString);
    free(tp);
}