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

SCalcCoreStatus getSCalcInvalidTokenError(const char* msg, const int originalPosition){
    SCalcCoreStatus res;
    res.code = S_CALC_ERR_INVALID_TOKEN;

    SCalcInvalidTokenError err;
    err.originalPosition = originalPosition;

    const size_t msgLen = msg == NULL? 0 : strlen(msg);
    if(msgLen == 0) {
        err.message = "Invalid token error";
    } else {
        err.message = (char*)calloc(msgLen + 1, sizeof(char));
        strcpy(err.message, msg);
    }

    res.invalidTokenError = err;
    return res;
}