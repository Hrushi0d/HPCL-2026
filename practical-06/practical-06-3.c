#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int msg = 100;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if(rank==0) printf("Please run this program with exactly 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    printf("Program is hanging because of deadlock.\n");
    if (rank == 0) {
        // Process 0 sends first, then receives
        MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received message: %d\n", msg);
    } else if (rank == 1) {
        // Process 1 sends first, then receives
        MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message: %d\n", msg);
    }

    MPI_Finalize();
    return 0;
}

