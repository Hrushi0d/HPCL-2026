//
// Created by lenovo on 9/9/2025.
//
#include <iostream>
#include <omp.h>

using namespace std;

#define N 250
int main() {
    int A[N][N] , B[N][N], C[N][N];
    //Initialize mat A and B
    //cout<<"Matrix A:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = i + j+1;
            // cout<<A[i][j]<<" ";
        }
        // cout<<endl;
    }
    //cout<<"Matrix B:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            B[i][j] = (i + 1) * (j + 1);
            // cout<<B[i][j]<<" ";
        }
        // cout<<endl;
    }
    double s= omp_get_wtime();
    //Normal matrix multiplication
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = 0;
            for(int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double e = omp_get_wtime();
    cout << "Time taken for normal matrix multiplication: " << (e - s) << " seconds\n";


    double start = omp_get_wtime();

    //parallel matrix multiplication
#pragma omp parallel for collapse(2)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = 0;
            for(int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double end = omp_get_wtime();
    //Print Result
    //cout<<"Resultant Matrix C:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            // cout<<C[i][j]<<" ";
        }
        // cout<<endl;
    }

    cout<<  "Time taken for matrix multiplication: " << (end - start) << " seconds\n";
    return 0;
}