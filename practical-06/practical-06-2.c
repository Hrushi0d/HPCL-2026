#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Comm comm = MPI_COMM_WORLD;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the total number of processes in the communicator
    MPI_Comm_size(comm, &size);

    // Get the rank of the current process
    MPI_Comm_rank(comm, &rank);

    // Print process information
    printf("Process %d of %d is in communicator group: MPI_COMM_WORLD\n", rank, size);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
