#include "calc_header.h"

#define SYMBOL input->data[input->ofs]

void InputConstruct(Input* input) {
    assert(input);

    input->data = (char*) calloc(MAX_INPUT_SIZE, sizeof(char));
    input->ofs = 0;
}

void InputDestruct(Input* input) {
    assert(input);

    free(input->data);
    input->ofs = -1;
}

void GetInput(Input* input) {
    assert(input);

    FILE* fp = {};


    #ifdef STANDART_INPUT
    fp = stdin;
    #else
    char* file_name = (char*) calloc(NAME_LEN, sizeof(char));
    printf("Type file name:");
    scanf ("%s", file_name);
    fp = fopen(filename, "r");
    assert(fp);
    free(file_name);
    #endif

    //fgets(input->data, MAX_INPUT_SIZE, fp);
    scanf("%s", input->data);

    #ifndef STANDART_INPUT
    fclose(fp);
    #endif
}

double SyntaxError(Input* input, char* message) {
    fprintf(stderr, "Syntax error in pos %d\n", input->ofs);
    fprintf(stderr, "%s", message);
    fprintf(stderr, "%s\n", input->data);

    for (int i = 0; i < input->ofs; ++i) {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "^\n");

    return NAN;
}

double GetN(Input* input) {
    assert(input);
    int value = 0;

    int ofs_begin = input->ofs;
    while ('0' <= SYMBOL && '9' >= SYMBOL) {
        value = value * 10 + SYMBOL - '0';
        ++input->ofs;
    }
    if (ofs_begin == input->ofs) {
        return SyntaxError(input, "");
    }

    return (double) value;
}

double GetP(Input* input) {
    assert(input);

    if (SYMBOL == '(') {
        ++input->ofs;
        double value = GetE(input);
        if (value != value) {
            return NAN;
        }
        if (SYMBOL != ')') {
            return SyntaxError(input, "Required ')'\n");
        }
        input->ofs++;
        return value;
    }
    else if (isalpha(SYMBOL) != 0) {
        int op_type = GetOperation(input);
        if (op_type == OP_ERR) {
            return SyntaxError(input, "Unknown operation\n");
        }

        double value = GetP(input);
        if (value != value) {
            return NAN;
        }
        switch(op_type) {
            case OP_SIN:
                return sin(value);
                break;

            case OP_COS:
                return cos(value);
                break;

            case OP_TAN:
                return tan(value);
                break;

            case OP_EXP:
                return exp(value);
                break;

            case OP_LN:
                return log(value);
                break;

            default:
                return SyntaxError(input, "Can't get unary operation type\n");
                break;
        }
    }
    else {
        return GetD(input);
    }
}

double GetE(Input* input) {
    assert(input);

    double value = GetT(input);
    if (value != value) {
        return NAN;
    }

    while (SYMBOL == '+' || SYMBOL == '-') {
        int operation = SYMBOL;
        ++input->ofs;
        double tmp_value = GetT(input);
        if (tmp_value != tmp_value) {
            return NAN;
        }
        if (operation == '+') {
            value += tmp_value;
        }
        else {
            value -= tmp_value;
        }
    }

    return value;
}

double GetT(Input* input) {
    assert(input);

    double value = GetPow(input);
    if (value != value) {
        return NAN;
    }

    while (SYMBOL == '*' || SYMBOL == '/') {
        int operation = SYMBOL;
        ++input->ofs;
        double tmp_value = GetPow(input);
        if (tmp_value != tmp_value) {
            return NAN;
        }
        if (operation == '*') {
            value *= tmp_value;
        }
        else {
            if (tmp_value == 0) {
                return SyntaxError(input, "Devision by zero\n");
            }
            value /= tmp_value;
        }
    }
    return value;
}

double GetG(Input* input) {
    assert(input);

    double value = GetE(input);
    if (value != value) {
        return NAN;
    }

    if (SYMBOL != '\0') {
        return SyntaxError(input, "");
    }

    return value;
}

double GetPow(Input* input) {
    assert(input);

    double value = GetP(input);
    if (value != value) {
        return NAN;
    }

    if (SYMBOL == '^') {
        ++input->ofs;
        double pow_value = GetP(input);
        if (pow_value != pow_value) {
            return NAN;
        }
        return pow(value, pow_value);
    }

    return value;
}

double GetD(Input* input) {
    assert(input);

    double value = GetN(input);
    if (value != value) {
        return NAN;
    }

    if (SYMBOL != '.') {
        return value;
    }
    ++input->ofs;
    int old_ofs = input->ofs;

    double fractial_part = GetN(input);
    if (fractial_part != fractial_part) {
        return NAN;
    }

    value += fractial_part / pow(10, input->ofs - old_ofs);

    return value;
}

int GetOperation(Input* input) {

    char* tmp_func = (char*) calloc(100, sizeof(char));

    sscanf(input->data + input->ofs, "%[a-z]s", tmp_func);

    fprintf(stderr, "scanned: <%s>\n", tmp_func); // debug
    input->ofs += strlen(tmp_func); //+1

    for (int i = UNARY_BEGIN; i < OPERATIONS_COUNT; ++i) {
        if (strcmp(tmp_func, operation_names[i]) == 0) {
            free(tmp_func);
            return i;
        }
    }

    free(tmp_func);
    return OP_ERR;
}

void ProceedCalc(Input* input) {
    assert(input);

    double value_out = GetG(input);
    if (value_out != value_out) {
        return;
    }

    printf("Value out: %llg", value_out);
}
