#include "functions.h"

int isFunction(const char* str){
    return strcmp(str, SIN_FUNCTION) == 0 || strcmp(str, COS_FUNCTION) == 0;
}