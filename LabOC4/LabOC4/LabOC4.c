#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Розміри матриць
#define N 256  // Розмір матриці NxN

// Функція для генерації випадкових чисел
void generate_matrix(int** mat) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mat[i][j] = rand() % 100;  // Заповнюємо числами від 0 до 99
        }
    }
}

// Стандартне множення матриць
void multiply_matrices(int** A, int** B, int** C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Блокове множення матриць (оптимізація для кешу)
void block_multiply_matrices(int** A, int** B, int** C, int block_size) {
    for (int i = 0; i < N; i += block_size) {
        for (int j = 0; j < N; j += block_size) {
            for (int k = 0; k < N; k += block_size) {
                // Блочний множник для підвекторів
                for (int ii = i; ii < i + block_size && ii < N; ii++) {
                    for (int jj = j; jj < j + block_size && jj < N; jj++) {
                        for (int kk = k; kk < k + block_size && kk < N; kk++) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Динамічне виділення пам'яті для матриць
    int** A = (int**)malloc(N * sizeof(int*));
    int** B = (int**)malloc(N * sizeof(int*));
    int** C = (int**)malloc(N * sizeof(int*));

    // Виділення пам'яті для кожного рядка матриць
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
    }

    // Генерація випадкових значень для матриць
    generate_matrix(A);
    generate_matrix(B);

    // Вимірювання часу для стандартного множення
    clock_t start_time = clock();
    multiply_matrices(A, B, C);
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Standard matrix multiplication time: %f seconds\n", time_taken);

    // Вимірювання часу для блочного множення
    start_time = clock();
    block_multiply_matrices(A, B, C, 32);  // Блоковий розмір 32
    end_time = clock();
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Block matrix multiplication time: %f seconds\n", time_taken);

    // Звільнення пам'яті
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
