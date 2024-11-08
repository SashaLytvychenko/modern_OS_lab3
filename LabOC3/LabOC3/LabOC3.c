#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000000
#define STRIDE 256  // ���� ��� ����������� �������, ��� ����� �� ��� ����

// ������� ��� ���������� ���� ������� �� ������ (���������)
void sequential_access(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] += 1;  // ���� �������� ��� ��������� ������� �� ���'��
    }
}

// ������� ��� ���������� ���� ������� �� ������ (���������� ������)
void random_access(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        int index = (rand() % size);  // ���������� ������ �� ��������
        arr[index] += 1;
    }
}

// ������� ��������
int main() {
    // �������� ���'�� ��� ������
    int* arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Error allocating memory\n");
        return -1;
    }

    // ����������� ������
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = 0;
    }

    // ���������� ���� ��������� ��� ����������� �������
    clock_t start_time = clock();
    sequential_access(arr, ARRAY_SIZE);
    clock_t end_time = clock();
    double sequential_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // ��������� ���� ��� ����������� �������
    printf("Sequential access time: %lf seconds\n", sequential_time);

    // ���������� ���� ��������� ��� ����������� �������
    start_time = clock();
    random_access(arr, ARRAY_SIZE);
    end_time = clock();
    double random_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // ��������� ���� ��� ����������� �������
    printf("Random access time: %lf seconds\n", random_time);

    // ��������� ���'��
    free(arr);

    return 0;
}
