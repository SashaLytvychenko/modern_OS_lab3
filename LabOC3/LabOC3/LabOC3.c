#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000000
#define STRIDE 256  // Крок для випадкового доступу, щоб вийти за межі кешу

// Функція для вимірювання часу доступу до масиву (послідовно)
void sequential_access(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] += 1;  // Зміна значення для генерації доступу до пам'яті
    }
}

// Функція для вимірювання часу доступу до масиву (випадковий доступ)
void random_access(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        int index = (rand() % size);  // Випадковий доступ до елементів
        arr[index] += 1;
    }
}

// Основна програма
int main() {
    // Виділення пам'яті для масиву
    int* arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Error allocating memory\n");
        return -1;
    }

    // Ініціалізація масиву
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = 0;
    }

    // Вимірювання часу виконання для послідовного доступу
    clock_t start_time = clock();
    sequential_access(arr, ARRAY_SIZE);
    clock_t end_time = clock();
    double sequential_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Виведення часу для послідовного доступу
    printf("Sequential access time: %lf seconds\n", sequential_time);

    // Вимірювання часу виконання для випадкового доступу
    start_time = clock();
    random_access(arr, ARRAY_SIZE);
    end_time = clock();
    double random_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Виведення часу для випадкового доступу
    printf("Random access time: %lf seconds\n", random_time);

    // Звільнення пам'яті
    free(arr);

    return 0;
}
