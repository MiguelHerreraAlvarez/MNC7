#include <stdio.h>
#include "mpi.h"
#include <cstdlib>

#define TOTAL_SIZE 10000

double suma(double* v, int size) {
	double cont = 0;
	for (int i = 0; i < size; i++) {
		cont +=  v[i];
	}
	return cont;
}

void main(int argc, char* argv[])
{
	int rank, size, length;
	double t_inicial, t_final;
	double processes[4];
	double msgSend[TOTAL_SIZE];
	
	
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	double partRecv[4];
	int partes = 0;
	
	t_inicial = MPI_Wtime();
	if (rank == 0) {
		for (size_t i = 0; i < TOTAL_SIZE; i++) { msgSend[i] = i; }
		double res = suma(msgSend, TOTAL_SIZE);
		t_final = MPI_Wtime();
		printf("El resultado de la suma en serie es: %lf\n Ha tardado %lf\n", res, t_final - t_inicial);
	}
	if (TOTAL_SIZE % size == 0) {
		partes = TOTAL_SIZE / size;
	}
	t_inicial = MPI_Wtime();
	MPI_Scatter(msgSend, partes, MPI_DOUBLE, partRecv, partes, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	double res = suma(partRecv, partes);

	printf("[%d] Mi parte es: %lf\n", rank, res);
	MPI_Gather(&res, 1, MPI_DOUBLE, processes, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Valor final: %lf\n", suma(processes, 4));
		t_final = MPI_Wtime();
		printf("El tiempo total es: %lf\n", t_final - t_inicial);
	}
	
	


	

	MPI_Finalize();


	return;

}
