#include "mpi.h"
#include <stdio.h>
#include <cmath>

void main(int argc, char* argv[]) {

	MPI_Status status;
	int rank, size, length, partner, message;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank < size / 2) {
		partner = rank + size / 2;
	} else {
		partner = rank - size / 2;
	}

	MPI_Send(&rank, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
	MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);

	MPI_Finalize();

	printf("[Proceso %d] Mi companero es %d y he recibido el mensaje: ", rank, message);

	return;
}