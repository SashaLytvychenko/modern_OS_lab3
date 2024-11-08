#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ������ �������
#define N 256  // ����� ������� NxN

// ������� ��� ��������� ���������� �����
void generate_matrix(int** mat) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mat[i][j] = rand() % 100;  // ���������� ������� �� 0 �� 99
        }
    }
}

// ���������� �������� �������
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

// ������� �������� ������� (���������� ��� ����)
void block_multiply_matrices(int** A, int** B, int** C, int block_size) {
    for (int i = 0; i < N; i += block_size) {
        for (int j = 0; j < N; j += block_size) {
            for (int k = 0; k < N; k += block_size) {
                // ������� ������� ��� ���������
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
    // �������� �������� ���'�� ��� �������
    int** A = (int**)malloc(N * sizeof(int*));
    int** B = (int**)malloc(N * sizeof(int*));
    int** C = (int**)malloc(N * sizeof(int*));

    // �������� ���'�� ��� ������� ����� �������
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
    }

    // ��������� ���������� ������� ��� �������
    generate_matrix(A);
    generate_matrix(B);

    // ���������� ���� ��� ������������ ��������
    clock_t start_time = clock();
    multiply_matrices(A, B, C);
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Standard matrix multiplication time: %f seconds\n", time_taken);

    // ���������� ���� ��� �������� ��������
    start_time = clock();
    block_multiply_matrices(A, B, C, 32);  // �������� ����� 32
    end_time = clock();
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Block matrix multiplication time: %f seconds\n", time_taken);

    // ��������� ���'��
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
