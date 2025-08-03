#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int compare_asc(const void *x, const void *y) {
    const float a = *(float *)x;
    const float b = *(float *)y;
    return (a > b) - (a < b);  // ascending
}

int compare_desc(const void *x, const void *y) {
    const float a = *(float *)x;
    const float b = *(float *)y;
    return (b > a) - (b < a);  // descending
}

#define N 10000000

int main() {
    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));

    if (!a || !b) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Thread-safe random number generation using rand_r()
    srand(42);  // Fixed seed for reproducibility

    // Sequential initialization
    for (int i = 0; i < N; i++) {
        float rand_val = (float)rand() / RAND_MAX;
        a[i] = rand_val;
        b[i] = rand_val;
    }

    // Sort arrays
    qsort(a, N, sizeof(float), compare_asc);
    qsort(b, N, sizeof(float), compare_desc);

    // Sequential dot product
    double sum_seq = 0.0;
    double start_time_seq = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        sum_seq += a[i] * b[i];
    }
    double end_time_seq = omp_get_wtime();
    printf("Dot product: %f\n", sum_seq);
    printf("Time for reduction [Sequential]: %f\n", end_time_seq - start_time_seq);

    // Parallel dot product
    double sum = 0.0;
    double start_time = omp_get_wtime();
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += a[i] * b[i];
    }
    double end_time = omp_get_wtime();
    printf("Dot product: %f\n", sum);
    printf("Time for reduction [Parallel]: %f\n", end_time - start_time);
    free(a);
    free(b);
    return 0;
}
