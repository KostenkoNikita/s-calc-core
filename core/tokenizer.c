#include "tokenizer.h"

int tokenize(const char* s, TokenList* l){
    for(; *s != '\0'; s++) {
        const char charValue = *s;
        if(IS_WHITESPACE(charValue)) {
            continue;
        } else if (IS_BRACKET(charValue) || IS_OPERATOR(charValue) || IS_SEPARATOR(charValue) || IS_DOT(charValue)){
            char tmp[2];
            tmp[0] = charValue;
            tmp[1] = '\0';
            token_list_append(l, tmp);
            continue;
        } else if(IS_FACTORIAL(charValue)) {
            if(IS_FACTORIAL(*(s + 1))) {
                int index = 0;
                size_t size = TMP_FACTORIAL_STRING_INITIAL_CAPACITY;
                char* tmp = calloc(size + 1, sizeof(char));
                char nextFactorialChar = *s;
                do
                {
                    check_string_length_and_extend(&tmp, &size, index);
                    tmp[index++] = nextFactorialChar;
                    s++;
                    nextFactorialChar = *s;
                } while (IS_FACTORIAL(nextFactorialChar));
                s--;
                tmp[index] = '\0';
                token_list_append(l, tmp);
                free(tmp);
                continue;
            } else {
                char tmp[2];
                tmp[0] = charValue;
                tmp[1] = '\0';
                token_list_append(l, tmp);
                continue;
            }
        } else if (isdigit(charValue)){
            int index = 0;
            size_t size = TMP_TOKENIZER_STRING_INITIAL_CAPACITY;
            char* tmp = calloc(size + 1, sizeof(char));
            char nextDigitTokenChar = *s;
            do
            {
                check_string_length_and_extend(&tmp, &size, index);
                tmp[index++] = nextDigitTokenChar;
                s++;
                nextDigitTokenChar = *s;
                if(IS_EXPONENT(nextDigitTokenChar)) {
                    if(IS_PLUS_OR_MINUS(*(s+1))){
                        int expOpIndex = index + 1;
                        check_string_length_and_extend(&tmp, &size, expOpIndex);
                        tmp[index] = nextDigitTokenChar;
                        tmp[expOpIndex] = *(s+1);
                        index+=2;
                        s+=2;
                        nextDigitTokenChar = *s;
                    } else {
                        check_string_length_and_extend(&tmp, &size, index);
                        tmp[index++] = nextDigitTokenChar;
                        s++;
                        nextDigitTokenChar = *s;
                    }
                }
            } while (IS_DIGIT_OR_DOT(nextDigitTokenChar));
            s--;
            tmp[index] = '\0';
            token_list_append(l, tmp);
            free(tmp);
            continue;
        } else if (isalpha(*s)){
            int index = 0;
            size_t size = TMP_TOKENIZER_STRING_INITIAL_CAPACITY;
            char* tmp = calloc(size + 1, sizeof(char));
            char nextAlNumTokenChar = *s;
            do
            {
                check_string_length_and_extend(&tmp, &size, index);
                tmp[index++] = nextAlNumTokenChar;
                s++;
                nextAlNumTokenChar = *s;
            } while (isalnum(nextAlNumTokenChar));
            s--;
            tmp[index] = '\0';
            token_list_append(l, tmp);
            free(tmp);
            continue;
        } else{
            return UNDEFINED_CHAR_ERR_CODE;
        }
    }
    return SUCCESS_RETURN_CODE;
}

inline void check_string_length_and_extend(char** str, size_t* size, const int index){
    if(index >= *size) {
        (*size) *= TMP_TOKENIZER_STRING_CAPACITY_MULTIPLIER;
        (*str) = realloc((*str), sizeof(char) * ((*size) + 1));
    }
}