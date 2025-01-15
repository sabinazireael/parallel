#include "main.h" 

void load_data() {
    FILE * fp = fopen("data.txt", "r"); 
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

void* invert_matrix(void* thread_data) {
    pthrData *data = (pthrData*) thread_data; 
    int start = data->sigment * (SIZE / THREADS); 
    int end = (data->sigment + 1) * (SIZE / THREADS);

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
    pthread_exit(0); 
}

void step(int step) {
    pthread_t threads[THREADS]; 
    pthrData threadData[THREADS]; 

    for (int count = 0; count < step; count++) {
        for(int i = 0; i < THREADS; i++) {
            threadData[i].sigment = i;
            pthread_create(&(threads[i]), NULL, invert_matrix, &threadData[i]); 
        }

        for(int i = 0; i < THREADS; i++) 
            pthread_join(threads[i], NULL);
    }
}

void outputData() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%lf ", invMatrix[i][j]);
        }
    }
}

int main() {
    load_data();
    init();
    step(STEP); 
    outputData();
    return 0;
}