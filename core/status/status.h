#pragma once

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define S_CALC_SUCCESS 0
#define S_CALC_ERR_INVALID_TOKEN 1

typedef struct {
    char* message;
} SCalcSuccess;

typedef struct {
    char* message;
    int originalPosition;
} SCalcInvalidTokenError;

typedef struct {
    int code;
    union {
        SCalcSuccess success;
        SCalcInvalidTokenError invalidTokenError;
    };
} SCalcCoreStatus;

SCalcCoreStatus getSCalcSuccessStatus(const char* msg);

SCalcCoreStatus getSCalcInvalidTokenError(const char* msg, int originalPosition);


