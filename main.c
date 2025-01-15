#include "main.h" 
#include <mpi.h>

void load_data(char* filename) {
    FILE * fp = fopen(filename, "r"); 
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) { 
            fscanf(fp, "%lf", &matrix[i][j]); 
        } 
    fclose(fp); 
}

void init() {
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            invMatrix[i][j] = 0.0;
    for (int i = 0; i < SIZE; i++) 
        invMatrix[i][i] = 1.0;
}

void invert_matrix(int rank, int num_procs) {
    int start = rank * (SIZE / num_procs); 
    int end = (rank + 1) * (SIZE / num_procs);

    for (int i = start; i < end; i++) { 
        double pivot = matrix[i][i]; 
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] /= pivot;
            invMatrix[i][j] /= pivot;
        }

        for (int j = 0; j < SIZE; j++) {
            if (i != j) {
                double factor = matrix[j][i];
                for (int k = 0; k < SIZE; k++) {
                    matrix[j][k] -= factor * matrix[i][k];
                    invMatrix[j][k] -= factor * invMatrix[i][k];
                }
            }
        }
    }
}

void step(int step, int rank, int num_procs) {
    for (int count = 0; count < step; count++) {
        invert_matrix(rank, num_procs);
    }
}

void outputData() {
    if (rank == 0) {
        printf("Inverted Matrix:\n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%lf ", invMatrix[i][j]);
            }
            printf("\n");
        }
    }
}

int main(int argc, char** argv) {
    int rank, num_procs;
    double time_spent = 0.0; 
    clock_t begin = clock();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (argc != 2) {
        if (rank == 0) {
            printf("Usage: mpirun -n <num_processes> ./prog <data_file>\n");
        }
        MPI_Finalize();
        return -1;
    }

    load_data(argv[1]);  

    init();  

    step(STEP, rank, num_procs);  

    outputData();  
    }

    MPI_Finalize();
    return 0;
}