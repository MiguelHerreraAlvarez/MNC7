#include <mpi.h>
#include <stdio.h>
#include <chrono>

void main(int argc, char** argv) {
	int rank;
	char buf[100];
	const int root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Barrier(MPI_COMM_WORLD);
	
	auto start = std::chrono::high_resolution_clock::now();
	if (rank == root) {
		sprintf_s(buf, "Hello there General Kenobi\n");
	}

	
	MPI_Bcast(&buf, 100, MPI_CHAR, root, MPI_COMM_WORLD);
	
	printf("[%d]: El mensaje es: ", rank);
	printf(buf);	
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	printf("Ha tardado %lf",elapsed.count());
	return;
}
