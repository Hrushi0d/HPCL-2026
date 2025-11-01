#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define M 8   // Rows of A
#define K 4   // Columns of A / Rows of B
#define N 4   // Columns of B

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    int rows_per_proc = M / size;
    int remainder = M % size;
    int start_row, end_row;

    if(rank < remainder){
        start_row = rank * (rows_per_proc + 1);
        end_row = start_row + rows_per_proc;
    } else {
        start_row = rank * rows_per_proc + remainder;
        end_row = start_row + rows_per_proc - 1;
    }
    int local_rows = end_row - start_row + 1;

    double *A_local = (double*)malloc(local_rows * K * sizeof(double));
    double *C_local = (double*)malloc(local_rows * N * sizeof(double));
    double *B = (double*)malloc(K * N * sizeof(double));

    double *A = NULL;
    double *C = NULL;

    if(rank==0){
        A = (double*)malloc(M * K * sizeof(double));
        C = (double*)malloc(M * N * sizeof(double));

        // Initialize A and B
        for(int i=0;i<M;i++)
            for(int j=0;j<K;j++)
                A[i*K + j] = i + j + 1;
        for(int i=0;i<K;i++)
            for(int j=0;j<N;j++)
                B[i*N + j] = i + j + 1;
    }

    // Broadcast B to all processes
    MPI_Bcast(B, K*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Scatter rows of A
    int *sendcounts = malloc(size * sizeof(int));
    int *displs = malloc(size * sizeof(int));
    int offset = 0;
    for(int i=0;i<size;i++){
        int rows = (i < remainder) ? rows_per_proc + 1 : rows_per_proc;
        sendcounts[i] = rows * K;
        displs[i] = offset;
        offset += rows * K;
    }

    MPI_Scatterv(A, sendcounts, displs, MPI_DOUBLE, A_local, local_rows*K, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Local computation
    for(int i=0;i<local_rows;i++){
        for(int j=0;j<N;j++){
            C_local[i*N + j] = 0.0;
            for(int k=0;k<K;k++){
                C_local[i*N + j] += A_local[i*K + k] * B[k*N + j];
            }
        }
    }

    // Print local computation info
    for(int i=0;i<local_rows;i++){
        printf("Rank %d computed C row %d: ", rank, start_row + i);
        for(int j=0;j<N;j++) printf("%.2f ", C_local[i*N + j]);
        printf("\n");
    }

    // Gather results
    int *recvcounts = malloc(size * sizeof(int));
    int *rdispls = malloc(size * sizeof(int));
    offset = 0;
    for(int i=0;i<size;i++){
        int rows = (i < remainder) ? rows_per_proc + 1 : rows_per_proc;
        recvcounts[i] = rows * N;
        rdispls[i] = offset;
        offset += rows * N;
    }

    MPI_Gatherv(C_local, local_rows*N, MPI_DOUBLE, C, recvcounts, rdispls, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if(rank==0){
        printf("\nFinal Matrix C:\n");
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++) printf("%.2f ", C[i*N + j]);
            printf("\n");
        }
        printf("Execution time with %d process(es): %f seconds\n", size, end_time-start_time);
    }

    free(A_local); free(C_local); free(B);
    free(sendcounts); free(displs); free(recvcounts); free(rdispls);
    if(rank==0){ free(A); free(C); }

    MPI_Finalize();
    return 0;
}
