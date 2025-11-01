#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, n = 8;
    double A[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    double B[8] = {2, 2, 2, 2, 2, 2, 2, 2};
    double local_sum = 0.0, global_sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk = n / size;
    int start = rank * chunk;
    int end = (rank == size-1) ? n : start + chunk;

    double start_time = MPI_Wtime();
    // Local dot product
    for(int i = start; i < end; i++) {
        local_sum += A[i] * B[i];
        printf("Rank %d computes A[%d]*B[%d] = %lf\n", rank, i, i, A[i]*B[i]);
    }

    // Reduce to get global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if(rank == 0) {
        printf("Dot Product = %lf\n", global_sum);
        printf("Execution time with %d process(es): %lf seconds\n", size, end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
