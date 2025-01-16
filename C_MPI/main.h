#ifndef MAIN_H_ 
#define MAIN_H_ 

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h> 
#include <mpi.h> 

#define SIZE 256 

double matrix[SIZE][SIZE]; 
double invMatrix[SIZE][SIZE]; 

void load_data(char* filename); 
void init(); 
void invert_matrix(int rank, int num_procs); 
void step(int step, int rank, int num_procs); 
void outputData(); 

#endif /* MAIN_H_ */