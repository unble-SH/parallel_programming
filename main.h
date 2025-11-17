#ifndef MAIN_H
#define MAIN_H

// 라이브러리
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>      // OpenMP
#include <time.h>
#include <math.h>


// 전역 상수
/*3week*/
#define WIDTH  20
#define HEIGHT 30

/*4week*/
#define SIZE 20
#define THREADS 4

/*9week*/
#define MAX 5000000

/*11week*/
#define SIZE 8000
#define ROWS 4
#define COLS 1000000

// 함수 선언
void parallel_pro(void);
void multi_thread(void);
void task1_parallel_for(void);
void task2_round_robin_row(void);
void task3_round_robin_col(void);
void dependency(void);
void swap(int* a, int* b);

void memory_model(void);
void reduction(void);
void inner_product(void);

//9주차
void prac_single(void);
void prac_master(void);
void prac_ordered(void);

//11week
void matrix_double(float(*matrix_d)[SIZE]);
void do_prac8_code1(void);

void mxv(float (*matrix_d)[COLS], float* vector, float* result, int nocol, int norow);				//false sharing 해결X 병렬
void do_prac8_code2(void);																			//false sharing 해결X 병렬
void mxv_serial(float (*matrix_d)[COLS], float* vector, float* result, int nocol, int norow);		//false sharing 해결X 직렬
void do_prac8_code2_serial(void);																	//false sharing 해결X 직렬
void mxv_clear(float (*matrix_d)[COLS], float* vector, float* result, int nocol, int norow);		//false sharing 해결O 병렬
void do_prac8_code2_clear(void);																	//false sharing 해결O 병렬

//12week
void prac9(void);
void prac9_sch(void);
void run_test(const char* name, const char* sched_type, int chunk, double* x, double* y);
void assignment_main(void);

#endif
