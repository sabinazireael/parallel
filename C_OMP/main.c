#include "main.h"

void init_matrix() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = (rand() % 1000) / 1000.0;
        }
    }
}


void invert_matrix() {
    int i, j, k;
    double temp;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            A_inv[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (i = 0; i < SIZE; i++) {
        temp = A[i][i];
        for (j = 0; j < SIZE; j++) {
            A[i][j] /= temp;
            A_inv[i][j] /= temp;
        }
        for (j = i + 1; j < SIZE; j++) {
            temp = A[j][i];
            for (k = 0; k < SIZE; k++) {
                A[j][k] -= A[i][k] * temp;
                A_inv[j][k] -= A_inv[i][k] * temp;
            }
        }
    }
}

void output_data() {
    printf(A_inv[0][0]);
}

void test() {
    double product = 0.0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            product += A[i][j] * A_inv[j][i];
        }
    }
    if (fabs(product - SIZE) < 0.01) {
        printf("Test pass\n");
    } else {
        printf("Test fail\n");
    }
}

int main() {
    omp_set_num_threads(THREADS);

    double time_spent = 0.0;
    clock_t begin = clock();

    init_matrix(); 

    invert_matrix(); 

    output_data(); 

    test(); 

    return 0;
}