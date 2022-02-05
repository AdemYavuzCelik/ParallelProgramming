#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define  N 5
#define COMM MPI_COMM_WORLD
#define TAG 777

int main(void) {

	MPI_Init(NULL, NULL);  // starts parallel environment
	bool b = true;
	int rank, size, i;
	MPI_Comm_rank(COMM, &rank);
	MPI_Comm_size(COMM, &size);
	MPI_Status* stat = (MPI_Status*)malloc(sizeof(MPI_Status));
	int sayi = 1;
	double localvar = 2.0;
	double gelen = 0.0;
	double startTime = MPI_Wtime();
	for (i = 0; i < N; i++) {
		if (b) {
			if (rank % 2 == 1 && i < 1) { 
				MPI_Send(&localvar, 1, MPI_DOUBLE, rank - sayi, TAG, COMM);
				b = false;
			}
			else if (rank % 2 == 0 && i < 1) {
				MPI_Recv(&gelen, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, COMM, stat);
				localvar += gelen;
				sayi = sayi * 2;
			}
			else {
				if ((rank / sayi) % 2 == 0) {
					MPI_Recv(&gelen, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, COMM, stat);
					localvar += gelen;
					sayi = sayi * 2;
				}
				else if ((rank / sayi) % 2 == 1) {
					MPI_Send(&localvar, 1, MPI_DOUBLE, rank - sayi, TAG, COMM);
					b = false;
				}
			}
		}

	}
	MPI_Barrier(COMM);
	double finishTime = MPI_Wtime();
	double elapsedTime = finishTime - startTime;
	if (rank == 0) {
		printf("Toplam %f -> %f saniye surdu", localvar, elapsedTime);

	}
	MPI_Finalize();

}

