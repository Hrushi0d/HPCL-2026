//
// Created by lenovo on 7/29/2025.
//
#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000; // Higher steps = better precision
double step;

int main() {
    double x, sum = 0.0;
    step = 1.0 / (double) num_steps;

    // Parallel for loop with reduction to avoid race conditions
#pragma omp parallel for private(x) reduction(+:sum)
    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    const double pi = step * sum;

    printf("Approximated value of Pi = %.15f\n", pi);
    return 0;
}
