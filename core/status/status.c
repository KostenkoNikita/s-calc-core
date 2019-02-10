#include "status.h"

SCalcCoreStatus getSCalcSuccessStatus(const char* msg) {
    SCalcCoreStatus res;
    res.code = S_CALC_SUCCESS;
    SCalcSuccess s;

    const size_t msgLen = msg == NULL? 0 : strlen(msg);
    if(msgLen == 0) {
        s.message = "Success";
    } else {
        s.message = (char*)calloc(msgLen + 1, sizeof(char));
        strcpy(s.message, msg);
    }

    res.success = s;
    return res;
}

SCalcCoreStatus getSCalcInvalidTokenError(const char* tokenString, const int originalPosition){
    SCalcCoreStatus res;
    res.code = S_CALC_ERR_INVALID_TOKEN;

    SCalcInvalidTokenError err;
    err.originalPosition = originalPosition;

    const char* msg1 = "Invalid token: ";
    err.message = (char*)calloc(strlen(msg1) + strlen(tokenString) + 1, sizeof(char));
    strcat(err.message, msg1);
    strcat(err.message, tokenString);

    res.invalidTokenError = err;
    return res;
}

SCalcCoreStatus getSCalcMismatchedParanthesesError() {
    SCalcCoreStatus res;
    res.code = S_CALC_ERR_MISMATCHED_PARANTHESES;

    SCalcSyntaxError err;
    err.message = "Mismatched parentheses";

    res.syntaxError = err;
    return res;
}