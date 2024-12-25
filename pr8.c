#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "function.h"
#include "validation.h"

int main() {
    printf(
        "This program calculates the complex resistance of a given oscillating circuit depending on the current frequency\n");
    SetConsoleOutputCP(CP_UTF8);
    do {

        char user_choice = 0;
        print_circuit_diagram();
        printf("Choose a circuit type:\n");

        user_choice = circuit_choice();

        double l = 0.0, c = 0.0;
        printf("Enter the inductance - L (mHn)[from 1e-3 to 1e3]. Values must be positive:\n");
        l = validate_float_type();
        printf("Enter the capacitance - C (mcF)[from 1e-3 to 1e3]. Values must be positive:\n");
        c = validate_float_type();

        double r = 0.0;
        double r1 = 0.0, r2 = 0.0;
        switch (user_choice) {
            case RLC:
            case RCL:
                printf("Enter the resistance - R (Ohm)[from 1e-3 to 1e3]. Values must be positive:\n");
                r = validate_float_type();
                break;
            case R2CLR1:
            case R1R2LC:
                printf("Enter the resistance - R1 (Ohm)[from 1e-3 to 1e3]. Values must be positive:\n");
                r1 = validate_float_type();
                printf("Enter the resistance - R2 (Ohm)[from 1e-3 to 1e3]. Values must be positive:\n");
                r2 = validate_float_type();
                break;
            default:
                break;
        }

        double fmin = 0.0, fmax = 0.0;
        do {
            printf("Enter the MIN frequency - fmin(Hz)[from 1e-3 to 1e3]. Value must be positive:\n");
            fmin = validate_float_type();
            printf("Enter the MAX frequency - fmax(Hz)[from 1e-3 to 1e3]. Value must be positive:\n");
            fmax = validate_float_type();
            if (fmin > fmax) {
                printf("fmin must be < than fmax\n");
            }
        } while (fmin > fmax);

        double step = 0.0;
        do {
            printf("Enter the STEP df - (Hz)[from 1e-3 to 1e3]. Value must be positive:\n");
            step = validate_float_type();
            if (step > fmax - fmin) {
                printf("STEP must be < than difference between frequencies (fmax-fmin)\n");
            }
            fflush(stdin);
        } while (step > fmax - fmin);

        complex numerator = {0.0, 0.0}, denominator = {0.0, 0.0}, z = {0.0, 0.0};
        double f0 = 0.0;
        f0 = 1.0 / (2.0 * M_PI * sqrt(l * c));
        printf("Resonance frequency = %lf Hz\n", f0);

        int i = 0;
        double f = fmin;
        do {
            double omega = omega_calculation(f);
            switch (user_choice) {
                case RLC:
                    calculation_1(&numerator, &denominator, &z, omega, r, l, c);
                    break;
                case RCL:
                    calculation_2(&numerator, &denominator, &z, omega, r, l, c);
                    break;
                case R2CLR1:
                    calculation_3(&numerator, &denominator, &z, omega, r1, r2, l, c);
                    break;
                case R1R2LC:
                    calculation_4(&numerator, &denominator, &z, omega, r1, r2, l, c);
                    break;
                default:
                    printf("Invalid circuit type.\n");
                    break;
            }
            printf("f(%d) = %.3lf\t", i + 1, f);
            printf("Z(%d) = ", i + 1);
            print_complex(z, 15);
            f += step;
            i++;
        } while (f <= fmax);

        printf("\nPress 'r' to RESTART or any other key to EXIT.\n");
    } while (getch() == 'r');
    return 0;
}
