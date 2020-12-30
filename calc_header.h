#pragma once

#include "TXLib.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <locale.h>
#include <math.h>

#define STANDART_INPUT

const int MAX_INPUT_SIZE = 1024;

enum OPERATIONS {
    OP_ERR = -1,
    OP_ADD =  0,
    OP_SUB =  1,
    OP_MUL =  2,
    OP_DIV =  3,
    OP_POW =  4,
    OP_SIN =  5,
    OP_COS =  6,
    OP_TAN =  7,
    OP_LN  =  8,
    OP_EXP =  9,
    OP_END
};

const int OPERATIONS_COUNT = OP_END;
const int UNARY_BEGIN = 5;

static char* operation_names[] {
    "+",
    "-",
    "*",
    "/",
    "^",
    "sin",
    "cos",
    "tan",
    "ln",
    "exp",
};

typedef struct Input {
    char* data;
    int ofs;
} Input;


double GetE(Input* input);
double GetG(Input* input);
double GetN(Input* input);
double GetD(Input* input);
double GetP(Input* input);
double GetT(Input* input);
double GetPow(Input* input);
void ProceedCalc(Input* input);
double SyntaxError(Input* input, char* message);
void InputConstruct(Input* input);
void InputDestruct(Input* input);
int GetOperation(Input* input);


