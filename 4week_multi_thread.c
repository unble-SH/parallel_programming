#include "main.h"

void multi_thread(void) {
    int dotMatrix[HEIGHT][WIDTH];

    // initialize
    memset(dotMatrix, 0, sizeof(dotMatrix));

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            dotMatrix[i][j] = i * WIDTH + j;
        }
    }

    // print value
    omp_set_num_threads(3);

    #pragma omp parallel
    {
        printf("픽셀 값 출력\n");
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                printf("%3d ", dotMatrix[i][j]);
            }
            printf("\n");
        }
    }
}


//Task 1: #pragma omp parallel for
void task1_parallel_for(void) {
    int dotMatrix[HEIGHT][WIDTH];

    omp_set_num_threads(3);

    // 초기화 + 값 채우기
#pragma omp parallel for collapse(2)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int tid = omp_get_thread_num();
            dotMatrix[i][j] = i * WIDTH + j;

            //  (옵션1) 어떤 tid가 채웠는지 로그 확인
            //printf("[Task1] tid=%d -> dotMatrix[%d][%d]=%d\n", tid, i, j, dotMatrix[i][j]);

            //  (옵션2) tid 번호를 값 대신 저장
            //dotMatrix[i][j] = tid;
        }
    }

    // 행렬 출력 (원래 값 출력)
    printf("\n[Task1] parallel for 결과\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%3d ", dotMatrix[i][j]);
        }
        printf("\n");
    }
}



//Task 2: 행 단위 Round-robin
void task2_round_robin_row(void) {
    int dotMatrix[HEIGHT][WIDTH];

    omp_set_num_threads(3);

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        for (int i = tid; i < HEIGHT; i += nthreads) {
            for (int j = 0; j < WIDTH; j++) {
                dotMatrix[i][j] = i * WIDTH + j;

                //  (옵션1) 어떤 tid가 채웠는지 로그 확인
                //printf("[Task2] tid=%d -> dotMatrix[%d][%d]=%d\n", tid, i, j, dotMatrix[i][j]);

                //  (옵션2) tid 번호를 값 대신 저장
                //dotMatrix[i][j] = tid;
            }
        }
    }

    // 행렬 출력
    printf("\n[Task2] round-robin (행 단위) 결과\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%3d ", dotMatrix[i][j]);
        }
        printf("\n");
    }
}



//Task 3: 열 단위 Round-robin
void task3_round_robin_col(void) {
    int dotMatrix[HEIGHT][WIDTH];

    omp_set_num_threads(3);

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        for (int j = tid; j < WIDTH; j += nthreads) {
            for (int i = 0; i < HEIGHT; i++) {
                dotMatrix[i][j] = i * WIDTH + j;

                //  (옵션1) 어떤 tid가 채웠는지 로그 확인
                //printf("[Task3] tid=%d -> dotMatrix[%d][%d]=%d\n", tid, i, j, dotMatrix[i][j]);

                //  (옵션2) tid 번호를 값 대신 저장
                //dotMatrix[i][j] = tid;
            }
        }
    }

    // 행렬 출력
    printf("\n[Task3] round-robin (열 단위) 결과\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%3d ", dotMatrix[i][j]);
        }
        printf("\n");
    }
}