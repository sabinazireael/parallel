#ifndef MAIN_H_ 
#define MAIN_H_ 

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h> 
#include <pthread.h> 

#define SIZE 512
#define THREADS 32

double matrix[SIZE][SIZE]; 
double invMatrix[SIZE][SIZE]; 

//структура для данных потока 
typedef struct { 
    int sigment; 
} pthrData; 

void load_data(); 
void init(); 
void* invert_matrix(void* thread_data); 
void step(int step); 
void outputData(); 

#endif /* MAIN_H_ */