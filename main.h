#ifndef MAIN_H
#define MAIN_H

// 라이브러리
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>      // OpenMP

// 전역 상수
#define WIDTH  20
#define HEIGHT 30

// 함수 선언
void parallel_pro(void);
void multi_thread(void);
void task1_parallel_for(void);
void task2_round_robin_row(void);
void task3_round_robin_col(void);

#endif
