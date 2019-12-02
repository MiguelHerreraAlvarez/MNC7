#include "mpi.h"
#include <stdio.h>
#include <cmath>

void main(int argc, char* argv[]) {

	int rank, size, length, partner;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Status status[2];
	MPI_Request request[2];
	char sndMessage[100];
	char rcvMessage[100];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank < size / 2) {
		partner = rank + size / 2;
	}
	else {
		partner = rank - size / 2;
	}

	sprintf_s(sndMessage, "Mensaje enviado por %d, a %d", rank, partner);

	MPI_Isend(&sndMessage, 100, MPI_CHAR, partner, 1, MPI_COMM_WORLD, &request[1]);
	MPI_Irecv(&rcvMessage, 100, MPI_CHAR, partner, 1, MPI_COMM_WORLD, &request[0]);

	MPI_Waitall(2, request, status);
	MPI_Finalize();
	
	printf("[Proceso %d] Mi companero es %d y he recibido el mensaje ", rank, partner);
	printf(rcvMessage);

	

	return;
}