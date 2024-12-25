#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>
#define RLC 49
#define RCL 50
#define R2CLR1 51
#define R1R2LC 52

typedef struct {
    double real;
    double imaginary;
} complex;

complex divide(complex a, complex b) {
    complex result;
    double denominator = b.real * b.real + b.imaginary * b.imaginary;
    result.real = (a.real * b.real + a.imaginary * b.imaginary) / denominator;
    result.imaginary = (a.imaginary * b.real - a.real * b.imaginary) / denominator;
    return result;
}

void print_complex(complex a, int precision) {
    printf("%.*lf + %.*e * i\n", precision, a.real, precision, a.imaginary);
}
double omega_calculation(const double fmin) {
    double f = 0.0, omega = 0.0;
    f = fmin;
    omega = 2 * M_PI * f;
    return omega;
}
void calculation_1(complex *numerator, complex *denominator, complex *z, double omega, double r, double l, double c) {
    numerator->real = l / c;
    numerator->imaginary = -r / (omega * c);
    denominator->real = r;
    denominator->imaginary = omega * l - 1.0 / (omega * c);
    *z = divide(*numerator, *denominator);
}

void calculation_2(complex *numerator, complex *denominator, complex *z, double omega, double r, double l, double c) {
    numerator->real = l / c;
    numerator->imaginary = r / (omega * c);
    denominator->real = r;
    denominator->imaginary = omega * l - 1.0 / (omega * c);
    *z = divide(*numerator, *denominator);
}

void calculation_3(complex *numerator, complex *denominator, complex *z, double omega, double r1, double r2, double l,
                   double c) {
    numerator->real = r1 * r2;
    numerator->imaginary = r1 * (omega * l - 1.0 / (omega * c));
    denominator->real = r1 + r2;
    denominator->imaginary = omega * l - 1.0 / (omega * c);
    *z = divide(*numerator, *denominator);
}

void calculation_4(complex *numerator, complex *denominator, complex *z, double omega, double r1, double r2, double l,
                   double c) {
    numerator->real = r1 * r2 + l / c;
    numerator->imaginary = omega * l * r1 - r2 / omega * c;
    denominator->real = r1 + r2;
    denominator->imaginary = omega * l - 1.0 / (omega * c);
    *z = divide(*numerator, *denominator);
}

void print_circuit_diagram() {
    printf("1.Circuit:\n"
        "●─┬────────▆▆▆──────◠◠◠◠──┬─●\n"
        "  │         R         L     │\n"
        "  │                         │\n"
        "  │               C         │\n"
        "  └───────────────││────────┘\n");
    printf("2.Circuit:\n"
    "●─┬────────▆▆▆──────││──────┬─●\n"
    "  │         R       C       │\n"
    "  │                         │\n"
    "  │      L                  │\n"
    "  └────◠◠◠◠───────────────┘\n");
    printf("3.Circuit:\n"
    "●─┬─────────▆▆▆──────││─────┓\n"
             "  │         R2         C    │\n"
             "  │                         │\n"
             "  █ R1     L                │\n"
             "●─┴──────◠◠◠◠─────────────┘\n");
    printf("4.Circuit:\n"
    "●─┬────────▆▆▆──────────────┓\n"
     "  █ R1     R2               │\n"
             "  ┴                         │\n"
             "  ┬ C       L               │\n"
             "●─┴───────◠◠◠◠────────────┚\n");
}

char circuit_choice() {
    char choice = 0;
    do {
        choice = getch();
        switch (choice) {
            case RLC:
                printf("Your choice is:\n");
                printf("●─┬────────▆▆▆──────◠◠◠◠──┬─●\n"
                    "  │         R         L     │\n"
                    "  │                         │\n"
                    "  │               C         │\n"
                    "  └───────────────││────────┘\n");
                break;

            case RCL:
                printf("Your choice is:\n");
                printf("●─┬────────▆▆▆──────││──────┬─●\n"
                    "  │         R       C       │\n"
                    "  │                         │\n"
                    "  │      L                  │\n"
                    "  └────◠◠◠◠───────────────┘\n");
                break;

            case R2CLR1:
                printf("Your choice is:\n");
                printf("●─┬─────────▆▆▆──────││─────┓\n"
                    "  │         R2         C    │\n"
                    "  │                         │\n"
                    "  █ R1     L                │\n"
                    "●─┴──────◠◠◠◠─────────────┘\n");
                break;

            case R1R2LC:
                printf("Your choice is:\n");
                printf("●─┬────────▆▆▆──────────────┓\n"
                    "  █ R1     R2               │\n"
                    "  ┴                         │\n"
                    "  ┬ C       L               │\n"
                    "●─┴───────◠◠◠◠────────────┚\n");
                break;

            default:
                break;
        }
    } while (choice < RLC || choice > R1R2LC);
    return choice;
}


#endif
