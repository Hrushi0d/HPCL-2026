//
// Created by lenovo on 9/9/2025.
//
// Created by lenovo on 9/9/2025
#include <stdio.h>
#include <omp.h>

int main() {
    int n = 15;
    long long fib[n+1];  // fixed-size array, since n=150

    fib[0] = 0;
    fib[1] = 1;

    double start = omp_get_wtime();

    // Sequential computation
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    double mid = omp_get_wtime();

    printf("Fibonacci Computation Time (Sequential): %f s\n", mid - start);

    // Parallel print with synchronization
#pragma omp parallel for
    for (int i = 0; i <= n; i++) {
#pragma omp critical
        {
            printf("F(%d) = %lld\n", i, fib[i]);
        }
    }

    double end = omp_get_wtime();

    printf("Parallel Print Time: %f s\n", end - mid);

    return 0;
}
