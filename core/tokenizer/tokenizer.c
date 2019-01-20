#include "tokenizer.h"

inline void check_string_length_and_extend(char** str, size_t* size, const int index){
    if(index >= *size) {
        (*size) *= TMP_TOKENIZER_STRING_CAPACITY_MULTIPLIER;
        (*str) = realloc(*str, sizeof(char) * ((*size) + 1));
    }
}

inline char* process_alpha_char(const char** str_p, int* currStrIndex) {
    int index = 0;
    const char* str = *str_p;
    size_t size = TMP_TOKENIZER_STRING_INITIAL_CAPACITY;
    char* tmp = (char*)calloc(size + 1, sizeof(char));
    char nextAlNumTokenChar = str[*currStrIndex];
    do
    {
        check_string_length_and_extend(&tmp, &size, index);
        tmp[index++] = nextAlNumTokenChar;
        (*currStrIndex)++;
        nextAlNumTokenChar = str[*currStrIndex];
    } while (isalnum(nextAlNumTokenChar));
    (*currStrIndex)--;
    tmp[index] = '\0';
    return tmp;
}

inline char* process_factorial(const char** str_p, int* currStrIndex) {
    const char* str = *str_p;
    if(IS_FACTORIAL(str[*currStrIndex + 1])) {
        int index = 0;
        size_t size = TMP_FACTORIAL_STRING_INITIAL_CAPACITY;
        char* tmp = (char*)calloc(size + 1, sizeof(char));
        char nextFactorialChar = str[*currStrIndex];
        do
        {
            check_string_length_and_extend(&tmp, &size, index);
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

inline char* process_digit(const char** str_p, int* currStrIndex) {
    int index = 0;
    size_t size = TMP_TOKENIZER_STRING_INITIAL_CAPACITY;
    const char* str = *str_p;
    char* tmp = (char*)calloc(size + 1, sizeof(char));
    char nextDigitTokenChar = str[*currStrIndex];
    do
    {
        check_string_length_and_extend(&tmp, &size, index);
        tmp[index++] = nextDigitTokenChar;
        (*currStrIndex)++;
        nextDigitTokenChar = str[*currStrIndex];
        if(IS_EXPONENT(nextDigitTokenChar)) {
            const char charAfterExp = str[*currStrIndex + 1];
            const char charAfterCharAfterExp = str[*currStrIndex + 2];
            if(IS_PLUS_OR_MINUS(charAfterExp) && isdigit(charAfterCharAfterExp)){
                int expOpIndex = index + 1;
                int expDigitIndex = index + 2;
                check_string_length_and_extend(&tmp, &size, expDigitIndex);
                tmp[index] = nextDigitTokenChar;
                tmp[expOpIndex] = charAfterExp;
                tmp[expDigitIndex] = charAfterCharAfterExp;
                index+=3;
                *currStrIndex+=3;
                nextDigitTokenChar = str[*currStrIndex];
            } else if(isdigit(charAfterExp)) {
                int expDigitIndex = index + 1;
                check_string_length_and_extend(&tmp, &size, expDigitIndex);
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

SCalcCoreStatus tokenize(const char* s, StringList* l){
    for(int i = 0; ; i++) {
        const char charValue = *(s + i);
        if(charValue == '\0') {
            break;
        }
        if(IS_WHITESPACE(charValue)) {
            continue;
        } else if (IS_BRACKET(charValue) || IS_OPERATOR(charValue) || IS_SEPARATOR(charValue) || IS_DOT(charValue)){
            char tmp[2];
            tmp[0] = charValue;
            tmp[1] = '\0';
            string_list_append(l, tmp);
            continue;
        } else if(IS_FACTORIAL(charValue)) {
            char* tmp = process_factorial(&s, &i);
            string_list_append(l, tmp);
            free(tmp);
            continue;
        } else if (isdigit(charValue)){
            char* tmp = process_digit(&s, &i);
            string_list_append(l, tmp);
            free(tmp);
            continue;
        } else if (isalpha(charValue)){
            char* tmp = process_alpha_char(&s, &i);
            string_list_append(l, tmp);
            free(tmp);
            continue;
        } else{
            SCalcCoreStatus err = getSCalcInvalidTokenError("An error occurred while resolving token", i);
            return err;
        }
    }
    return getSCalcSuccessStatus("String has been successfully processed");
}