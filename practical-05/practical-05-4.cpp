//
// Created by lenovo on 9/9/2025.
//
#include <iostream>
#include <omp.h>
using namespace std;

#define N 100000

int main() {
    int* arr = new int[N];
    int* prefix = new int[N];

    // Initialize array
    for(int i=0;i<N;i++) arr[i] = 1;

    // Normal prefix sum
    double s = omp_get_wtime();
    prefix[0] = arr[0];
    for(int i=1;i<N;i++){
        prefix[i] = prefix[i-1] + arr[i];
    }
    double e = omp_get_wtime();
    cout << "Time taken for normal prefix sum: " << (e-s) << " seconds\n";

    // Naive parallel prefix sum
    double start = omp_get_wtime();
#pragma omp parallel for
    for(int i=0;i<N;i++){
        int sum = 0;
        for(int j=0;j<=i;j++) sum += arr[j];
        prefix[i] = sum;
    }
    double end = omp_get_wtime();
    cout << "Time taken for parallel prefix sum (naive): " << (end-start) << " seconds\n";

    delete[] arr; delete[] prefix;
    return 0;
}