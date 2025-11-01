#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define M 8
#define N 4

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time, end_time;
    start_time = MPI_Wtime(); // Start timing

    int rows_per_proc = M / size;
    int remainder = M % size;

    int start_row, end_row;
    if (rank < remainder) {
        start_row = rank * (rows_per_proc + 1);
        end_row = start_row + rows_per_proc;
    } else {
        start_row = rank * rows_per_proc + remainder;
        end_row = start_row + rows_per_proc - 1;
    }
    int local_rows = end_row - start_row + 1;

    double *local_A = (double*)malloc(local_rows * N * sizeof(double));
    double *local_y = (double*)malloc(local_rows * sizeof(double));
    double x[N];

    double *A = NULL;
    double *y = NULL;
    if(rank == 0){
        A = (double*)malloc(M * N * sizeof(double));
        y = (double*)malloc(M * sizeof(double));
        for(int i=0;i<M;i++)
            for(int j=0;j<N;j++)
                A[i*N + j] = i + j + 1; // example values
        for(int j=0;j<N;j++)
            x[j] = j + 1;
    }

    // Broadcast vector
    MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Scatter matrix rows
    int *sendcounts = malloc(size * sizeof(int));
    int *displs = malloc(size * sizeof(int));
    int offset = 0;
    for(int i=0;i<size;i++){
        int rows = (i < remainder) ? rows_per_proc + 1 : rows_per_proc;
        sendcounts[i] = rows * N;
        displs[i] = offset;
        offset += rows * N;
    }

    MPI_Scatterv(A, sendcounts, displs, MPI_DOUBLE, local_A, local_rows*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Local computation
    for(int i=0;i<local_rows;i++){
        local_y[i] = 0.0;
        for(int j=0;j<N;j++)
            local_y[i] += local_A[i*N + j] * x[j];
    }

    // Print local computation info
    for(int i=0;i<local_rows;i++){
        printf("Rank %d computed y[%d] = %.2f\n", rank, start_row + i, local_y[i]);
    }

    // Gather results
    int *recvcounts = malloc(size * sizeof(int));
    int *rdispls = malloc(size * sizeof(int));
    offset = 0;
    for(int i=0;i<size;i++){
        int rows = (i < remainder) ? rows_per_proc + 1 : rows_per_proc;
        recvcounts[i] = rows;
        rdispls[i] = offset;
        offset += rows;
    }

    MPI_Gatherv(local_y, local_rows, MPI_DOUBLE, y, recvcounts, rdispls, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime(); // End timing

    if(rank==0){
        printf("\nFinal result vector y:\n");
        for(int i=0;i<M;i++)
            printf("%.2f ", y[i]);
        printf("\n");
        printf("Execution time with %d process(es): %f seconds\n", size, end_time - start_time);
    }

    free(local_A); free(local_y);
    free(sendcounts); free(displs);
    free(recvcounts); free(rdispls);
    if(rank==0){ free(A); free(y); }

    MPI_Finalize();
    return 0;
}
