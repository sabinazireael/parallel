#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "omp.h"

#define SIZE 1024
#define THREADS 16

double A[SIZE][SIZE];
double A_inv[SIZE][SIZE];

// Функции
void init_matrix();
void invert_matrix(); 
void output_data(); 
void test(); 

#endif /* MAIN_H_ */