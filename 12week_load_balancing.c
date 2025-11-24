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

void assignment_main(void)
{
    double x[MAX], y[MAX];
    double dot_product;
    double start_time, end_time, elapsed_time;
    int i;

    /* 1. 벡터 초기화 (입력 데이터 고정) */
    for (i = 0; i < MAX; i++) {
        x[i] = (double)i + 10.0;      /* 증가하는 패턴 */
        y[i] = (double)MAX - i;       /* 감소하는 패턴 */
    }

    /* 사용할 스레드 수 고정 */
    omp_set_num_threads(4);

    /* =========================
       1. static (기본 스케줄)
       ========================= */
    dot_product = 0.0;

    start_time = omp_get_wtime();

#pragma omp parallel for reduction(+:dot_product) schedule(static)
    for (i = 0; i < MAX; i++) {
        double xi = sqrt(x[i]);
        double yi = sqrt(y[i]);
        dot_product += (xi + yi);
    }

    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;

    printf("===== 1. static =====\n");
    printf("1. static time = %f sec\n", elapsed_time);
    printf("1. static dot_product = %.0f\n\n", dot_product);

    /* =========================
       2. dynamic (기본 chunk)
       ========================= */
    dot_product = 0.0;
    start_time = omp_get_wtime();

#pragma omp parallel for reduction(+:dot_product) schedule(dynamic)
    for (i = 0; i < MAX; i++) {
        double xi = sqrt(x[i]);
        double yi = sqrt(y[i]);
        dot_product += (xi + yi);
    }

    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;

    printf("===== 2. dynamic =====\n");
    printf("2. dynamic time = %f sec\n", elapsed_time);
    printf("2. dynamic dot_product = %.0f\n\n", dot_product);

    /* =========================
       3. auto
       ========================= */
    dot_product = 0.0;
    start_time = omp_get_wtime();

#pragma omp parallel for reduction(+:dot_product) schedule(auto)
    for (i = 0; i < MAX; i++) {
        double xi = sqrt(x[i]);
        double yi = sqrt(y[i]);
        dot_product += (xi + yi);
    }

    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;

    printf("===== 3. auto =====\n");
    printf("3. auto time = %f sec\n", elapsed_time);
    printf("3. auto dot_product = %.0f\n\n", dot_product);

    /* =========================
       4. runtime
       - omp_set_schedule로
         dynamic, 100 설정 후 사용
       ========================= */
    omp_set_schedule(omp_sched_dynamic, 100);

    dot_product = 0.0;
    start_time = omp_get_wtime();

#pragma omp parallel for reduction(+:dot_product) schedule(runtime)
    for (i = 0; i < MAX; i++) {
        double xi = sqrt(x[i]);
        double yi = sqrt(y[i]);
        dot_product += (xi + yi);
    }

    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;

    printf("===== 4. runtime (dynamic,100) =====\n");
    printf("4. runtime time = %f sec\n", elapsed_time);
    printf("4. runtime dot_product = %.0f\n\n", dot_product);

    /* =========================
       5. guided(100)
       ========================= */
    dot_product = 0.0;
    start_time = omp_get_wtime();

#pragma omp parallel for reduction(+:dot_product) schedule(guided, 100)
    for (i = 0; i < MAX; i++) {
        double xi = sqrt(x[i]);
        double yi = sqrt(y[i]);
        dot_product += (xi + yi);
    }

    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;

    printf("===== 5. guided(100) =====\n");
    printf("5. guided(100) time = %f sec\n", elapsed_time);
    printf("5. guided(100) dot_product = %.0f\n\n", dot_product);

}
