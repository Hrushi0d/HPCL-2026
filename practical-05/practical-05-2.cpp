//
// Created by lenovo on 9/9/2025.
//
#include <iostream>
#include <omp.h>
using namespace std;

#define N 1000

int main() {
    // Allocate dynamically
    int* A = new int[N*N];
    int* B = new int[N*N];
    int* C = new int[N*N];

    // Initialize A and B
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            A[i*N + j] = i + j + 1;
            B[i*N + j] = (i+1)*(j+1);
        }
    }

    // Normal multiplication
    double s = omp_get_wtime();
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            C[i*N + j] = 0;
            for(int k=0;k<N;k++){
                C[i*N + j] += A[i*N + k] * B[k*N + j];
            }
        }
    }
    double e = omp_get_wtime();
    cout << "Time taken for normal matrix-matrix multiplication: " << (e-s) << " seconds\n";

    // Parallel multiplication
    double start = omp_get_wtime();
#pragma omp parallel for collapse(2)
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            C[i*N + j] = 0;
            for(int k=0;k<N;k++){
                C[i*N + j] += A[i*N + k] * B[k*N + j];
            }
        }
    }
    double end = omp_get_wtime();
    cout << "Time taken for parallel matrix-matrix multiplication: " << (end-start) << " seconds\n";

    delete[] A; delete[] B; delete[] C;
    return 0;
}