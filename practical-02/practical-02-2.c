#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000; // Number of steps
double step;

int main() {
    int i;
    double x, pi = 0.0;
    for (int j = 1; j <= 32; j++) {
        double sum = 0.0;
        omp_set_num_threads(j);

        step = 1.0 / (double) num_steps;

        // Record start time
        double start_time = omp_get_wtime();

        // Parallelize the loop for Pi calculation
#pragma omp parallel for private(x) reduction(+:sum)
        for (i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

        pi = step * sum;

        // Record end time and calculate elapsed time
        double end_time = omp_get_wtime();
        printf("Calculated Pi = %.15f\n", pi);
        printf("Time taken for Pi Calculation with %ld steps [%d threads]: %.6f seconds\n", num_steps, j, end_time - start_time);
    }


    return 0;
}