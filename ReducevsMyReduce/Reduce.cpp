#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

#define COMM MPI_COMM_WORLD

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    double localvar = 2.0;
    double toplam = 0.0;
    double startTime = MPI_Wtime();
    MPI_Reduce(&localvar, &toplam, 1, MPI_DOUBLE, MPI_SUM, 0, COMM);
    MPI_Barrier(COMM);
    double finishTime = MPI_Wtime();
    double elapsedTime = finishTime - startTime;

    if (rank == 0) {
        printf("Toplam %f -> %f saniye surdu", toplam,elapsedTime);
        
    }


    MPI_Finalize();

    return 0;
}