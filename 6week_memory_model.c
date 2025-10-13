#include "main.h"

void memory_model(void) {
    float Data[5] = { 1, 2, 3, 4, 5 };

    printf("Serial Area Data : %.1f, %.1f, %.1f, %.1f, %.1f\n",
           Data[0], Data[1], Data[2], Data[3], Data[4]);

    #pragma omp parallel default(shared)
    {
        Data[0] = 7;
        Data[1] = 7;
        printf("Parallel Area Data : %.1f, %.1f, %.1f, %.1f, %.1f\n",
               Data[0], Data[1], Data[2], Data[3], Data[4]);
    }

    printf("Serial Area Data : %.1f, %.1f, %.1f, %.1f, %.1f\n",
           Data[0], Data[1], Data[2], Data[3], Data[4]);

}

//shared는 병렬 구간 안이나 밖이나 공유하고 private 하면 인덱스 2, 3, 4 중 쓰레기 값.
//default(shared)는 shared랑 동일
//default(none)은 필수적으로 private인지 shared인지 명시를 해야함. 슬라이드 29장이 특히 중요. none할 시 블럭 내의 모든 변수에 대해 선언을 해야 함.

//reduction = 축약. 그 온라인 강의에 병목현상 줄이려고 2개 쓰레드씩 더하고 마스터 코어에 최종적으로 주는 그 기억나지.35슬라이드 보면 기억날거야.
void reduction(void) {
    int sum = 0, i = 0;
    int Data[1000] = { 0 };

    for (i = 0; i < 1000; i++) {
        Data[i] = i + 1;
    }
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < 1000; i++) {
        sum += Data[i];
    }
    printf("총합 = %d\n", sum);
}


//Task
void inner_product(void) {
    int i;
    
    double A[10000], B[10000], sum = 0.0;
    double start, end;

    // 초기 값
    for (i = 0; i < 10000; i++) {
        A[i] = (i + 1) / 10000.0;
        B[i] = (i + 1) / 10000.0;
    }




    sum = 0.0;
    // 시간 측정 시작
    start = omp_get_wtime();

    omp_set_num_threads(1);   // 몇개의 스레드로 실행

    // 병렬 영역
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < 10000; i++) {
        sum += A[i] * B[i];
    }

    // 시간 측정 종료
    end = omp_get_wtime();

    printf("1개 스레드 Inner Product (A·B) = %f\n", sum);
    printf("Execution Time = %f seconds\n", end - start);
    printf("\n");


    for (int eoeo = 1; eoeo <= 4; eoeo++) {
        sum = 0.0;
        // 시간 측정 시작
        start = omp_get_wtime();

        omp_set_num_threads(eoeo *2);   // 몇개의 스레드로 실행

        // 병렬 영역
#pragma omp parallel for reduction(+:sum)
        for (i = 0; i < 10000; i++) {
            sum += A[i] * B[i];
        }

        // 시간 측정 종료
        end = omp_get_wtime();

        printf("%d개 스레드 Inner Product (A·B) = %f\n", eoeo*2, sum);
        printf("Execution Time = %f seconds\n", end - start);
        printf("\n");

    }
        
}
