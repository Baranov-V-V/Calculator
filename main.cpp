#include "calc_header.h"
#include "calc_func.cpp"

int main() {
    Input input = {};
    InputConstruct(&input);
    GetInput(&input);

    ProceedCalc(&input);

    InputDestruct(&input);
    return 0;
}

