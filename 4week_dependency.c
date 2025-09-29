#include "main.h"

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void dependency(void) {
    int arr[SIZE];
    double start, end;

    srand(time(NULL));

    // 랜덤 데이터 배열 생성 (0~99 범위)
    printf("Original array:\n");
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    omp_set_num_threads(THREADS);
    start = omp_get_wtime();

    // Parallel Bubble Sort (Odd-Even Transposition Sort)
    for (int i = 0; i < SIZE; i++) {
        if (i % 2 == 0) {
#pragma omp parallel for
            for (int j = 0; j < SIZE - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
        else {
#pragma omp parallel for
            for (int j = 1; j < SIZE - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }

    end = omp_get_wtime();

    // 결과 출력
    printf("\nSorted array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Execution time = %f seconds\n", end - start);

}
