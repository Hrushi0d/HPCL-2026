//
// Created by lenovo on 7/29/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000 // Size of the array

int main() {
    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));
    float scalar = 2.5;

    // Initialize the input vector (only once)
    for (int i = 0; i < N; i++) {
        a[i] = i * 1.0;
    }

    // Loop from 1 to 32 threads
    for (int num_threads = 1; num_threads <= 32; num_threads++) {
        // Set the number of OpenMP threads
        omp_set_num_threads(num_threads);

        const double start_time = omp_get_wtime();

        // Parallelize the addition
#pragma omp parallel for
        for (int i = 0; i < N; i++) {
            b[i] = a[i] + scalar;
        }

        const double end_time = omp_get_wtime();

        printf("Threads: %2d | Time taken: %.6f seconds\n", num_threads, end_time - start_time);
    }

    free(a);
    free(b);
    return 0;
}
