#include "mpi.h"
#include <stdio.h>

void main(int argc, char* argv[])
{
	int rank, size, length;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("[Proceso %d] Hola desde %s!\n", rank, name);
	if (rank == 0) printf("El número total de procesos MPI es % d.\n", size);
		MPI_Finalize();
	return;
}