#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int send_data, recv_data;
    int next, prev;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Define neighbors in the ring
    prev = (rank - 1 + size) % size; // previous process
    next = (rank + 1) % size;        // next process

    // Initialize data to send
    send_data = rank * 10; // just an example value

    // Use blocking send/receive in ring
    if (rank % 2 == 0) {
        // Even ranks send first, then receive
        MPI_Send(&send_data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        // Odd ranks receive first, then send
        MPI_Recv(&recv_data, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&send_data, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    printf("Process %d sent %d to %d and received %d from %d\n",
            rank, send_data, next, recv_data, prev);

    MPI_Finalize();
    return 0;
}
