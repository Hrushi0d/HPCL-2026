#include <stdio.h>
#include <omp.h>

int main() {
    const int N = 1000;
    float a[N], b[N];
    const float scalar = 2.4;
    for (int i = 0; i < N; i++) {
        a[i] = i * scalar;
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        b[i] = a[i] + scalar;
    }
    printf("a[] + scalar = b[]\n\n");
    for (int i = 0; i < 10; i++) {
        printf("a[%d] = %2f\t\t b[%d] = %2f\n", i, a[i], i, b[i]);
    }
    return 0;
}