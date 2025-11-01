#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int n = 10; // size of array
    int A[10] = {1,2,3,4,5,6,7,8,9,10};
    int local_sum = 0, total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if(rank==0) printf("Please run with exactly 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    int half = n / 2;

    if (rank == 0) {
        // P0 sums first half
        for (int i = 0; i < half; i++) {
            local_sum += A[i];
        }
        // Send local sum to P1
        MPI_Send(&local_sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // P1 sums second half
        for (int i = half; i < n; i++) {
            local_sum += A[i];
        }
        // Receive P0's sum
        int sum0;
        MPI_Recv(&sum0, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        total_sum = sum0 + local_sum;
        printf("Total sum of array elements: %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}
