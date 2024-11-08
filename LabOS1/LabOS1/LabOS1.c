#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // ������ �� �������� ��� ���������� uint64_t
#include <time.h>

// ����� ������ ��� ����������. ����� ��� ����� ������ ����.
#define ARRAY_SIZE 50000000

// ���������� ������ �� ������
void sequential_access(int* array, size_t size) {
    uint64_t sum = 0;
    clock_t start = clock();

    for (size_t i = 0; i < size; i++) {
        sum += array[i];
    }

    clock_t end = clock();
    printf("Sequential Access: Execution Time = %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

// ���������� ������ �� ������
void random_access(int* array, size_t size) {
    uint64_t sum = 0;
    clock_t start = clock();

    for (size_t i = 0; i < size; i++) {
        size_t index = rand() % size;
        sum += array[index];
    }

    clock_t end = clock();
    printf("Random Access: Execution Time = %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

// ���������� ���� ��� ������� ������� ����� (cache-intensive workload)
void cache_intensive_workload(int* array, size_t size) {
    uint64_t sum = 0;
    clock_t start = clock();

    // ����� �������� ������ ��� ��������� ������������ ���-������������
    for (size_t i = 0; i < size; i += 64) {  // ������������� ���� ��� ����������� ������ ����
        sum += array[i];
    }

    clock_t end = clock();
    printf("Cache-Intensive Workload: Execution Time = %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

// ������� �������
int main() {
    printf("Demonstration of cache efficiency for different access patterns and workload optimizations\n");

    // �������� ���'�� ��� ������
    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (!array) {
        printf("Memory allocation error!\n");
        return 1;
    }

    // ���������� ������ ��� ����������
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    // ���������� ������ �� �������� ������
    sequential_access(array, ARRAY_SIZE);

    // ���������� ������ �� �������� ������
    random_access(array, ARRAY_SIZE);

    // Cache-intensive workload
    cache_intensive_workload(array, ARRAY_SIZE);

    // ��������� ���'��
    free(array);

    return 0;
}
