#include "tokenizer.h"

int tokenize(const char* s, StringList* l){
    for(; *s != '\0'; s++) {
        const char charValue = *s;
        if(IS_WHITESPACE(charValue)) {
            continue;
        } else if (IS_BRACKET(charValue) || IS_OPERATOR(charValue) || IS_SEPARATOR(charValue) || IS_DOT(charValue)){
            char tmp[2];
            tmp[0] = charValue;
            tmp[1] = '\0';
            string_list_append(l, tmp);
            continue;
        } else if(IS_FACTORIAL(charValue)) {
            process_factorial(&s, l);
            continue;
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
                    const char charAfterExp = *(s+1);
                    const char charAfterCharAfterExp = *(s+2);
                    if(IS_PLUS_OR_MINUS(charAfterExp) && isdigit(charAfterCharAfterExp)){
                        int expOpIndex = index + 1;
                        int expDigitIndex = index + 2;
                        check_string_length_and_extend(&tmp, &size, expDigitIndex);
                        tmp[index] = nextDigitTokenChar;
                        tmp[expOpIndex] = charAfterExp;
                        tmp[expDigitIndex] = charAfterCharAfterExp;
                        index+=3;
                        s+=3;
                        nextDigitTokenChar = *s;
                    } else if(isdigit(charAfterExp)) {
                        int expDigitIndex = index + 1;
                        check_string_length_and_extend(&tmp, &size, expDigitIndex);
                        tmp[index] = nextDigitTokenChar;
                        tmp[expDigitIndex] = charAfterExp;
                        index+=2;
                        s+=2;
                        nextDigitTokenChar = *s;
                    }
                }
            } while (IS_DIGIT_OR_DOT(nextDigitTokenChar));
            s--;
            tmp[index] = '\0';
            string_list_append(l, tmp);
            free(tmp);
            continue;
        } else if (isalpha(*s)){
            process_alpha_char(&s, l);
            continue;
        } else{
            return UNDEFINED_CHAR_ERR_CODE;
        }
    }
    return SUCCESS_RETURN_CODE;
}

inline void process_alpha_char(const char** str_p, StringList *l) {
    int index = 0;
    size_t size = TMP_TOKENIZER_STRING_INITIAL_CAPACITY;
    char* tmp = calloc(size + 1, sizeof(char));
    char nextAlNumTokenChar = *(*str_p);
    do
    {
        check_string_length_and_extend(&tmp, &size, index);
        tmp[index++] = nextAlNumTokenChar;
        (*str_p)++;
        nextAlNumTokenChar = *(*str_p);
    } while (isalnum(nextAlNumTokenChar));
    (*str_p)--;
    tmp[index] = '\0';
    string_list_append(l, tmp);
    free(tmp);
}

inline void process_factorial(const char** str_p, StringList* l) {
    if(IS_FACTORIAL(*(*str_p + 1))) {
        int index = 0;
        size_t size = TMP_FACTORIAL_STRING_INITIAL_CAPACITY;
        char* tmp = calloc(size + 1, sizeof(char));
        char nextFactorialChar = *(*str_p);
        do
        {
            check_string_length_and_extend(&tmp, &size, index);
            tmp[index++] = nextFactorialChar;
            (*str_p)++;
            nextFactorialChar = *(*str_p);
        } while (IS_FACTORIAL(nextFactorialChar));
        (*str_p)--;
        tmp[index] = '\0';
        string_list_append(l, tmp);
        free(tmp);
    } else {
        char tmp[2];
        tmp[0] = *(*str_p);
        tmp[1] = '\0';
        string_list_append(l, tmp);
    }
}

inline void check_string_length_and_extend(char** str, size_t* size, const int index){
    if(index >= *size) {
        (*size) *= TMP_TOKENIZER_STRING_CAPACITY_MULTIPLIER;
        (*str) = realloc(*str, sizeof(char) * ((*size) + 1));
    }
}