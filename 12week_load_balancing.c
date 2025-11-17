#include "main.h"

void prac9(void)
{
    double x[MAX], y[MAX];
    double dot_product = 0.0;

    double start_time, end_time, elapsed_time;
    int i;

    for (i = 0; i < MAX; i++) {
        x[i] = (double)i + 10.0;
        y[i] = (double)MAX - i;
    }

    start_time = omp_get_wtime();

    for (i = 0; i < MAX; i++) {
        x[i] = sqrt(x[i]);
        y[i] = sqrt(y[i]);
        dot_product += (x[i] + y[i]);
    }

    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;

    printf("Ex time = %f \n", elapsed_time);
    printf("dot_product = %f \n", dot_product);

}

void prac9_sch(void)
{
    double x[MAX], y[MAX];
    double dot_product = 0.0;

    double start_time, end_time, elapsed_time;
    int i;

    for (i = 0; i < MAX; i++) {
        x[i] = (double)i + 10.0;
        y[i] = (double)MAX - i;
    }

#pragma omp parallel num_threads(4) private(start_time, end_time)
    {
#pragma omp barrier

        start_time = omp_get_wtime();

#pragma omp for reduction(+:dot_product) schedule(guided, 100)
        for (i = 0; i < MAX; i++) {
            x[i] = sqrt(x[i]);
            y[i] = sqrt(y[i]);
            dot_product += (x[i] + y[i]);
        }

        end_time = omp_get_wtime();
        elapsed_time = end_time - start_time;

#pragma omp single
        printf("Ex time = %f\n", elapsed_time);
    }

    printf("dot-product = %f\n", dot_product);
}





//assignment. compare 5 case
void run_test(const char* name, const char* sched_type, int chunk, double* x, double* y)
{
    double dot_product = 0.0;
    double start_time, end_time;

    // 스케줄 설정 문자열 생성
    printf("\n===== %s =====\n", name);

    start_time = omp_get_wtime();

#pragma omp parallel num_threads(4) reduction(+:dot_product)
    {
        if (chunk == 0) {
#pragma omp for schedule(static)
            for (int i = 0; i < MAX; i++) {
                x[i] = sqrt(x[i]);
                y[i] = sqrt(y[i]);
                dot_product += x[i] + y[i];
            }
        }
        else {
            // chunk 포함한 schedule 방식
            if (sched_type == "static") {
#pragma omp for schedule(static, chunk)
                for (int i = 0; i < MAX; i++) {
                    x[i] = sqrt(x[i]);
                    y[i] = sqrt(y[i]);
                    dot_product += x[i] + y[i];
                }
            }
            else if (sched_type == "dynamic") {
#pragma omp for schedule(dynamic, chunk)
                for (int i = 0; i < MAX; i++) {
                    x[i] = sqrt(x[i]);
                    y[i] = sqrt(y[i]);
                    dot_product += x[i] + y[i];
                }
            }
            else if (sched_type == "guided") {
#pragma omp for schedule(guided, chunk)
                for (int i = 0; i < MAX; i++) {
                    x[i] = sqrt(x[i]);
                    y[i] = sqrt(y[i]);
                    dot_product += x[i] + y[i];
                }
            }
        }
    }

    end_time = omp_get_wtime();
    printf("%s time = %f sec\n", name, end_time - start_time);
    printf("%s dot_product = %.0f\n", name, dot_product);
}

void assignment_main(void)
{
    static double x[MAX], y[MAX];

    // 초기화
    for (int i = 0; i < MAX; i++) {
        x[i] = (double)i + 10.0;
        y[i] = (double)MAX - i;
    }

    // 5가지 실험 자동 수행
    run_test("1. static(default)", "static", 0, x, y);

    // 초기화 다시 (값 변경되니까!)
    for (int i = 0; i < MAX; i++) { x[i] = (double)i + 10.0; y[i] = (double)MAX - i; }
    run_test("2. static(100)", "static", 100, x, y);

    for (int i = 0; i < MAX; i++) { x[i] = (double)i + 10.0; y[i] = (double)MAX - i; }
    run_test("3. dynamic(default)", "dynamic", 1, x, y);

    for (int i = 0; i < MAX; i++) { x[i] = (double)i + 10.0; y[i] = (double)MAX - i; }
    run_test("4. dynamic(100)", "dynamic", 100, x, y);

    for (int i = 0; i < MAX; i++) { x[i] = (double)i + 10.0; y[i] = (double)MAX - i; }
    run_test("5. guided(100)", "guided", 100, x, y);

}
