#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // Для роботи з потоками в Windows
#include <time.h>     // Для вимірювання часу

#define NUM_THREADS 4
#define NUM_INCREMENTS 1000000

// Спільна змінна для модифікації (використовуємо int)
volatile long shared_counter = 0;

// Функція для потоків: збільшує спільну змінну NUM_INCREMENTS разів
DWORD WINAPI increment_counter(LPVOID arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        InterlockedIncrement(&shared_counter); // Атомарне збільшення
    }
    return 0;
}

int main() {
    HANDLE threads[NUM_THREADS];
    DWORD threadId;
    clock_t start_time, end_time;
    double total_time;

    printf("Concurrent access demonstration with atomic optimization.\n");

    // Вимірюємо час створення потоків та інкрементації змінної
    start_time = clock();

    // Створення потоків
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = CreateThread(NULL, 0, increment_counter, NULL, 0, &threadId);
        if (threads[i] == NULL) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    // Очікування завершення потоків
    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    // Вимірюємо час завершення роботи потоків
    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Розрахунок середнього часу інкрементації
    double avg_increment_time = total_time / (NUM_THREADS * NUM_INCREMENTS);

    // Виведення результатів
    printf("Final counter value: %ld (Expected: %ld)\n", shared_counter, NUM_THREADS * NUM_INCREMENTS);
    printf("Total execution time: %lf seconds\n", total_time);
    printf("Average time per increment: %le seconds\n", avg_increment_time);

    // Закриваємо потоки
    for (int i = 0; i < NUM_THREADS; i++) {
        CloseHandle(threads[i]);
    }

    return 0;
}
