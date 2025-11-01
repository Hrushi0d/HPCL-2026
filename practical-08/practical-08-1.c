#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define M 6   // Rows of input matrix
#define N 6   // Columns of input matrix
#define K 3   // Kernel size

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

    double *A_local = malloc(local_rows * N * sizeof(double));
    double *C_local = malloc(local_rows * N * sizeof(double));
    double kernel[K*K];
    double *A = NULL;
    double *C = NULL;

    if(rank == 0){
        A = malloc(M * N * sizeof(double));
        C = malloc(M * N * sizeof(double));

        // Initialize input matrix A
        for(int i=0;i<M;i++)
            for(int j=0;j<N;j++)
                A[i*N + j] = i*10 + j + 1;

        // Example kernel (3x3)
        double temp[K*K] = {0,1,0,1,-4,1,0,1,0};
        for(int i=0;i<K*K;i++) kernel[i] = temp[i];
    }

    // Broadcast kernel to all processes
    MPI_Bcast(kernel, K*K, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Scatter rows of A
    int *sendcounts = malloc(size*sizeof(int));
    int *displs = malloc(size*sizeof(int));
    int offset=0;
    for(int i=0;i<size;i++){
        int rows = (i < remainder) ? rows_per_proc + 1 : rows_per_proc;
        sendcounts[i] = rows * N;
        displs[i] = offset;
        offset += rows * N;
    }

    MPI_Scatterv(A, sendcounts, displs, MPI_DOUBLE, A_local, local_rows*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Local 2D convolution
    for(int i=0;i<local_rows;i++){
        for(int j=0;j<N;j++){
            double sum = 0.0;
            for(int ki=0; ki<K; ki++){
                for(int kj=0; kj<K; kj++){
                    int ai = i + ki - K/2 + start_row;
                    int aj = j + kj - K/2;
                    if(ai>=0 && ai<M && aj>=0 && aj<N)
                        sum += A_local[(ai-start_row)*N + aj] * kernel[ki*K + kj];
                }
            }
            C_local[i*N + j] = sum;
            printf("Rank %d computed C[%d][%d] = %.2f\n", rank, start_row + i, j, sum);
        }
    }

    // Gather results
    int *recvcounts = malloc(size*sizeof(int));
    int *rdispls = malloc(size*sizeof(int));
    offset=0;
    for(int i=0;i<size;i++){
        int rows = (i < remainder) ? rows_per_proc + 1 : rows_per_proc;
        recvcounts[i] = rows*N;
        rdispls[i] = offset;
        offset += rows*N;
    }

    MPI_Gatherv(C_local, local_rows*N, MPI_DOUBLE, C, recvcounts, rdispls, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if(rank==0){
        printf("\nFinal Convolved Matrix:\n");
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++) printf("%.2f ", C[i*N + j]);
            printf("\n");
        }
        printf("Execution time with %d process(es): %f seconds\n", size, end_time-start_time);
    }

    free(A_local); free(C_local); free(sendcounts); free(displs); free(recvcounts); free(rdispls);
    if(rank==0){ free(A); free(C); }

    MPI_Finalize();
    return 0;
}
