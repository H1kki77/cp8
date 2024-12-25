#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdbool.h>
#define MIN 1e-3
#define MAX 1e3
char circuit_validation(unsigned);

double validate_float_type() {
    bool invalidInput;
    double value = 0.0;
    do {
        if (scanf("%lf", &value) != 1 || value > MAX || value < MIN) {
            printf("Invalid input. Please enter correct value.\n");
            fflush(stdin);
            invalidInput = true;
        } else {
            fflush(stdin);
            invalidInput = false;
        }
    } while (invalidInput);
    return value;
}
#endif //VALIDATION_H
