#include <mpi.h>
#include <stdio.h>

#define MSGSIZE 100000

void main(int argc, char** argv) {
	int rank, size;
	char msgSend[MSGSIZE];
	char msgRecv[MSGSIZE];
	const int root = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	double ti_PaP = MPI_Wtime();
	
	if (rank == root) {
		sprintf_s(msgSend, "Hello there General Kenobi\n");
		for (int i = 1; i < size; i++) {
			MPI_Send(msgSend, MSGSIZE, MPI_CHAR, i, 1, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(msgRecv, MSGSIZE, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
		printf("[%d](PaP): El mensaje es: %s", rank, msgRecv);
	}
	double tf_PaP = MPI_Wtime();
	if (rank == root) printf("Tiempo Punto a Punto: %lf\n", tf_PaP - ti_PaP);


	
	MPI_Barrier(MPI_COMM_WORLD);
	double ti_Bcast = MPI_Wtime();
	
	MPI_Bcast(&msgSend, MSGSIZE, MPI_CHAR, root, MPI_COMM_WORLD);
	
	if(rank != root) printf("[%d](Broadcast): El mensaje es: %s", rank, msgSend);	
	
	MPI_Barrier(MPI_COMM_WORLD);
	double tf_Bcast = MPI_Wtime();
	if (rank == root) printf("Tiempo Broadcast: %lf\n", tf_Bcast - ti_Bcast);
	MPI_Finalize();
	
	return;
}
