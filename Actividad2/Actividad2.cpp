#include "mpi.h"
#include <stdio.h>

void execute() {
	double op1 = 7.0;
	for (double i = 1.0; i < 1e9; i++)
	{
		double xd = i * 1.000001;
		op1 *= xd;
	}
}

void main(int argc, char* argv[])
{
	int rank, size, length;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double tinicial = MPI_Wtime();
	execute();
	double tfinal = MPI_Wtime();
	double tiempo = tfinal - tinicial;

	printf("El tiempo de ejecucion es %f.\n", tiempo);
	MPI_Finalize();

	return;
}

