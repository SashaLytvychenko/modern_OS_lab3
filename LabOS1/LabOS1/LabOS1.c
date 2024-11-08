#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>  // Додаємо цю бібліотеку для визначення uint64_t
#include <time.h>

// Розмір масиву для тестування. Змініть для різних розмірів кешу.
#define ARRAY_SIZE 50000000

// Послідовний доступ до масиву
void sequential_access(int* array, size_t size) {
    uint64_t sum = 0;
    clock_t start = clock();

    for (size_t i = 0; i < size; i++) {
        sum += array[i];
    }

    clock_t end = clock();
    printf("Sequential Access: Execution Time = %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

// Випадковий доступ до масиву
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

// Тестування кешу при великих обсягах даних (cache-intensive workload)
void cache_intensive_workload(int* array, size_t size) {
    uint64_t sum = 0;
    clock_t start = clock();

    // Обхід великого масиву для симуляції інтенсивного кеш-навантаження
    for (size_t i = 0; i < size; i += 64) {  // Використовуємо крок для перевищення розміру кешу
        sum += array[i];
    }

    clock_t end = clock();
    printf("Cache-Intensive Workload: Execution Time = %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

// Основна функція
int main() {
    printf("Demonstration of cache efficiency for different access patterns and workload optimizations\n");

    // Виділення пам'яті для масиву
    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (!array) {
        printf("Memory allocation error!\n");
        return 1;
    }

    // Заповнення масиву для тестування
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    // Послідовний доступ до елементів масиву
    sequential_access(array, ARRAY_SIZE);

    // Випадковий доступ до елементів масиву
    random_access(array, ARRAY_SIZE);

    // Cache-intensive workload
    cache_intensive_workload(array, ARRAY_SIZE);

    // Звільнення пам'яті
    free(array);

    return 0;
}
