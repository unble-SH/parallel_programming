#include "main.h"

void prac_single(void) {
#pragma omp parallel num_threads(4)
    {
        printf("병렬 영역 single 전 : %d번 Thread 동작\n", omp_get_thread_num());
        #pragma omp single
        {
            printf("병렬 영역 single   : %d번 Thread 동작\n", omp_get_thread_num());
        }
        printf("병렬 영역 single 후 : %d번 Thread 동작\n", omp_get_thread_num());
    }
}

void prac_master(void) {
    float* data;
    int i = 0;
    data = (float*)malloc(sizeof(float) * MAX);

    for (i = 0; i < MAX; i++)
        data[i] = i;

#pragma omp parallel
    {
#pragma omp for
        for (i = 0; i < MAX; i++)
            data[i] = sqrt(data[i]);

#pragma omp for
        for (i = 0; i < 5; i++)
            printf("before master, tid=%d, data[%d] = %.4f\n", omp_get_thread_num(), i, data[i]);

#pragma omp master
        {
            for (i = 0; i < 5; i++)
                printf("master, tid=%d, data[%d] = %.4f\n", omp_get_thread_num(), i, data[i]);
        }

#pragma omp for
        for (i = 0; i < 5; i++)
            printf("after master, tid=%d, data[%d] = %.4f\n", omp_get_thread_num(), i, data[i]);

#pragma omp for
        for (i = 0; i < MAX; i++)
            data[i] = log(data[i]);
    }

    free(data);
}

void prac_ordered(void) {
    int data[12];

    for (int i = 0; i < 12; i++) {
        data[i] = i;
    }

#pragma omp parallel for num_threads(4) ordered
    for (int i = 0; i < 11; i++) {
#pragma omp ordered
        {
            data[i] += data[i + 1];
            printf("tid: %d, %d\n", omp_get_thread_num(), data[i]);
        }
    }
}

/*
serial에서 병렬 처리하고 serial로 다시 돌아온다고 배웠었지.
스레드의 순서가 명시 돼있지 않다는 문제점 발생!! 출력문 같은 경우엔 크게 문제 없겠지만 계산 문제일 시 계산 결과가 엉뚱하게 나올 수도 있겠지.
어떻게 스레드 순서를 동기화 할 것인지를 배울거야

<첫번째 지시어> single_directive
#pragma omp single [보조 지시어][보조 지시어][........
동기 문제가 발생되는 부분은 하나의 thread를 사용. 확실하겠지만 병렬이 아닌 serial으로 수행된다는 문제가 있겠지
20p 예제를 보면되는데 단 sigle_directive는 single 쓰기 전에 등장할 순 있지만 그 후엔 나타나지 않는다(22p, 23p 참고)

<두 번째 지시어> master_directive
#pragma omp master
master thread에서만 코드 실행
master랑 다른 thread랑 데이터 의존성이 있다면동기화 문제 발생가능하다는 문제가 있겠지.
master는 암시적 베리어가 없음.(29, 30p를 보면 signle은 암묵적 베리어가 있다는 걸 알 수 있지)

<세번째 지시어> ordered_directive
#pragma omp ordered
쓰레드 오름차 순으로 순차 실행(p33, 34 참고)
*/