#include "rpn_writer.h"

inline void checkStringLengthAndExtend(char **str, size_t *size, const int index){
    if(index >= *size) {
        (*size) *= TMP_TOKENIZER_STRING_CAPACITY_MULTIPLIER;
        (*str) = realloc(*str, sizeof(char) * ((*size) + 1));
    }
}

inline char* processAlphaChar(const char **str_p, int *currStrIndex) {
    int index = 0;
    const char* str = *str_p;
    size_t size = TMP_TOKENIZER_STRING_INITIAL_CAPACITY;
    char* tmp = (char*)calloc(size + 1, sizeof(char));
    char nextAlNumTokenChar = str[*currStrIndex];
    do
    {
        checkStringLengthAndExtend(&tmp, &size, index);
        tmp[index++] = nextAlNumTokenChar;
        (*currStrIndex)++;
        nextAlNumTokenChar = str[*currStrIndex];
    } while (isalnum(nextAlNumTokenChar));
    (*currStrIndex)--;
    tmp[index] = '\0';
    return tmp;
}

inline char* processFactorial(const char **str_p, int *currStrIndex) {
    const char* str = *str_p;
    if(IS_FACTORIAL(str[*currStrIndex + 1])) {
        int index = 0;
        size_t size = TMP_FACTORIAL_STRING_INITIAL_CAPACITY;
        char* tmp = (char*)calloc(size + 1, sizeof(char));
        char nextFactorialChar = str[*currStrIndex];
        do
        {
            checkStringLengthAndExtend(&tmp, &size, index);
            tmp[index++] = nextFactorialChar;
            (*currStrIndex)++;
            nextFactorialChar = str[*currStrIndex];
        } while (IS_FACTORIAL(nextFactorialChar));
        (*currStrIndex)--;
        tmp[index] = '\0';
        return tmp;
    } else {
        char* tmp = (char*)calloc(2, sizeof(char));
        tmp[0] = str[*currStrIndex];
        tmp[1] = '\0';
        return tmp;
    }
}

inline char* processDigit(const char **str_p, int *currStrIndex) {
    int index = 0;
    size_t size = TMP_TOKENIZER_STRING_INITIAL_CAPACITY;
    const char* str = *str_p;
    char* tmp = (char*)calloc(size + 1, sizeof(char));
    char nextDigitTokenChar = str[*currStrIndex];
    do
    {
        checkStringLengthAndExtend(&tmp, &size, index);
        tmp[index++] = nextDigitTokenChar;
        (*currStrIndex)++;
        nextDigitTokenChar = str[*currStrIndex];
        if(IS_EXPONENT(nextDigitTokenChar)) {
            const char charAfterExp = str[*currStrIndex + 1];
            const char charAfterCharAfterExp = str[*currStrIndex + 2];
            if(IS_PLUS_OR_MINUS(charAfterExp) && isdigit(charAfterCharAfterExp)){
                int expOpIndex = index + 1;
                int expDigitIndex = index + 2;
                checkStringLengthAndExtend(&tmp, &size, expDigitIndex);
                tmp[index] = nextDigitTokenChar;
                tmp[expOpIndex] = charAfterExp;
                tmp[expDigitIndex] = charAfterCharAfterExp;
                index+=3;
                *currStrIndex+=3;
                nextDigitTokenChar = str[*currStrIndex];
            } else if(isdigit(charAfterExp)) {
                int expDigitIndex = index + 1;
                checkStringLengthAndExtend(&tmp, &size, expDigitIndex);
                tmp[index] = nextDigitTokenChar;
                tmp[expDigitIndex] = charAfterExp;
                index+=2;
                *currStrIndex+=2;
                nextDigitTokenChar = str[*currStrIndex];
            }
        }
    } while (IS_DIGIT_OR_DOT(nextDigitTokenChar));
    (*currStrIndex)--;
    tmp[index] = '\0';
    return tmp;
}

SCalcCoreStatus writeRpn(const char* str, TokenStack* s, TokenQueue* q){
    for(unsigned int i = 0; ; i++) {
        const char charValue = *(str + i);
        const unsigned int originalPosition = i;
        if(charValue == '\0') {
            break;
        }
        if(IS_WHITESPACE(charValue)) {
            continue;
        } else if(IS_DIGIT(charValue)) {
            const char* tmp = processDigit(&str, &i);
            Token* t = createToken(tmp, TOKEN_NUMBER, originalPosition);
            tokenQueueEnqueue(q, t);
        } else if (isalpha(charValue)) {
            const char* tmp = processAlphaChar(&str, &i);
            if(isFunction(tmp)) {
                Token* t = createToken(tmp, TOKEN_FUNCTION, originalPosition);
                tokenQueueEnqueue(q, t);
            } else {
                const SCalcCoreStatus err = getSCalcInvalidTokenError(tmp, i);
                return err;
            }
        } else if (IS_SEPARATOR(charValue)) {
            while (tokenStackPeek(s)->tokenType != TOKEN_OPENING_BRACKET) {
                tokenQueueEnqueue(q, tokenStackPop(s));
                if (isTokenStackEmpty(s)) {
                    SCalcCoreStatus err = getSCalcMismatchedParanthesesError();
                    return err;
                }
            }
        } else if(IS_OPERATOR(charValue)) {
            Token* op1Token;
            char* tmp;
            int op1TokenType;
            if(IS_FACTORIAL(charValue)) {
                tmp = processFactorial(&str, &i);
                op1TokenType = TOKEN_RIGHT_ASSOCIATIVE_OPERATOR;
            } else {
                tmp = (char*)calloc(2, sizeof(char));
                tmp[0] = charValue;
                tmp[1] = '\0';
                op1TokenType = TOKEN_LEFT_ASSOCIATIVE_OPERATOR;
            }
            op1Token = createToken(tmp, op1TokenType, originalPosition);
            Token* op2Token;
            while(!isTokenStackEmpty(s) && isOperatorToken(op2Token = tokenStackPop(s))) {
                const int op1Priority = getOperatorPriority(op1Token);
                const int op2Priority = getOperatorPriority(op2Token);
                if((op1TokenType == TOKEN_LEFT_ASSOCIATIVE_OPERATOR && op1Priority <= op2Priority) || (op1TokenType == TOKEN_LEFT_ASSOCIATIVE_OPERATOR && op1Priority < op2Priority)) {
                    tokenQueueEnqueue(q, op2Token);
                }
            }
            if(isTokenStackEmpty(s) || tokenStackPeek(s)->tokenType == TOKEN_OPENING_BRACKET) {
                tokenStackPush(s, op1Token);
            }
        } else if (IS_OPENING_BRACKET(charValue)) {
            char tmp[2];
            tmp[0] = charValue;
            tmp[1] = '\0';
            Token* t = createToken(tmp, TOKEN_OPENING_BRACKET, originalPosition);
            tokenStackPush(s, t);
        } else if(IS_CLOSING_BRACKET(charValue)) {
            while (tokenStackPeek(s)->tokenType != TOKEN_OPENING_BRACKET) {
                tokenQueueEnqueue(q, tokenStackPop(s));
                if (isTokenStackEmpty(s)) {
                    SCalcCoreStatus err = getSCalcMismatchedParanthesesError();
                    return err;
                }
            }
            tokenStackPop(s);
            if(!isTokenStackEmpty(s) && tokenStackPeek(s)->tokenType == TOKEN_FUNCTION) {
                tokenQueueEnqueue(q, tokenStackPop(s));
            }
        } else {
            char charValAsString[2];
            charValAsString[0] = charValue;
            charValAsString[1] = '\0';
            const SCalcCoreStatus err = getSCalcInvalidTokenError(charValAsString, i);
            return err;
        }
    }
    while(!isTokenStackEmpty(s)) {
        const Token* t = tokenStackPeek(s);
        const int tokenType = t->tokenType;
        if(tokenType == TOKEN_OPENING_BRACKET || tokenType == TOKEN_CLOSING_BRACKET) {
            SCalcCoreStatus err = getSCalcMismatchedParanthesesError();
            return err;
        }
        tokenQueueEnqueue(q, tokenStackPop(s));
    }
    return getSCalcSuccessStatus("String has been successfully processed");
}