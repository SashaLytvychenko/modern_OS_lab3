#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // ��� ������ � �������� � Windows
#include <time.h>     // ��� ���������� ����

#define NUM_THREADS 4
#define NUM_INCREMENTS 1000000

// ������ ����� ��� ����������� (������������� int)
volatile long shared_counter = 0;

// ������� ��� ������: ������ ������ ����� NUM_INCREMENTS ����
DWORD WINAPI increment_counter(LPVOID arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        InterlockedIncrement(&shared_counter); // �������� ���������
    }
    return 0;
}

int main() {
    HANDLE threads[NUM_THREADS];
    DWORD threadId;
    clock_t start_time, end_time;
    double total_time;

    printf("Concurrent access demonstration with atomic optimization.\n");

    // �������� ��� ��������� ������ �� ������������� �����
    start_time = clock();

    // ��������� ������
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = CreateThread(NULL, 0, increment_counter, NULL, 0, &threadId);
        if (threads[i] == NULL) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    // ���������� ���������� ������
    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    // �������� ��� ���������� ������ ������
    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // ���������� ���������� ���� �������������
    double avg_increment_time = total_time / (NUM_THREADS * NUM_INCREMENTS);

    // ��������� ����������
    printf("Final counter value: %ld (Expected: %ld)\n", shared_counter, NUM_THREADS * NUM_INCREMENTS);
    printf("Total execution time: %lf seconds\n", total_time);
    printf("Average time per increment: %le seconds\n", avg_increment_time);

    // ��������� ������
    for (int i = 0; i < NUM_THREADS; i++) {
        CloseHandle(threads[i]);
    }

    return 0;
}
