//
// Created by lenovo on 9/9/2025.
//
#include <iostream>
#include <omp.h>
using namespace std;

#define N 2000

int main() {
    int* A = new int[N*N];
    int* x = new int[N];
    int* y = new int[N];

    // Initialize A and vector x
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            A[i*N + j] = i + j + 1;
        }
        x[i] = i+1;
    }

    // Normal multiplication
    double s = omp_get_wtime();
    for(int i=0;i<N;i++){
        y[i] = 0;
        for(int j=0;j<N;j++){
            y[i] += A[i*N + j] * x[j];
        }
    }
    double e = omp_get_wtime();
    cout << "Time taken for normal matrix-vector multiplication: " << (e-s) << " seconds\n";

    // Parallel multiplication
    double start = omp_get_wtime();
#pragma omp parallel for
    for(int i=0;i<N;i++){
        y[i] = 0;
        for(int j=0;j<N;j++){
            y[i] += A[i*N + j] * x[j];
        }
    }
    double end = omp_get_wtime();
    cout << "Time taken for parallel matrix-vector multiplication: " << (end-start) << " seconds\n";

    delete[] A; delete[] x; delete[] y;
    return 0;
}