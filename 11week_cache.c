#include "main.h"


//Data Access Parttern
void matrix_double(float (*matrix_d)[SIZE]) {
#pragma omp parallel for num_threads(4)
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			matrix_d[x][y] = matrix_d[x][y] + 2;
		}
	}
}
void do_prac8_code1(void) {
	float matrix[SIZE][SIZE] = { 0.0 };
	double start_time, end_time, elapsed_time;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			matrix[i][j] = (((float)i) * SIZE + j) / ((float)1000.0);
		}
	}

#pragma omp barrier
	start_time = omp_get_wtime();
	matrix_double(matrix);
	end_time = omp_get_wtime();

	printf("\nExe. Time = %f msec\n", (end_time - start_time) * 1000.0);
}



//False Sharing


void mxv(float (*matrix_d)[COLS], float* vector, float* result, int nocol, int norow) {
#pragma omp parallel for num_threads(4)
	for (int y = 0; y < norow; y++) {
		for (int x = 0; x < nocol; x++) {
			result[y] += matrix_d[y][x] * vector[x];
		}
	}
}

void do_prac8_code2(void)
{
	float matrix[ROWS][COLS], results[ROWS], vec[COLS];
	int i, j;
	double start_time, end_time;

	/* initialize data */
	for (j = 0; j < ROWS; j++) {
		for (i = 0; i < COLS; i++) {
			matrix[j][i] = (((float)j) * COLS + (float)i) / (float)1000.;
		}
	}
	for (i = 0; i < COLS; i++) {
		vec[i] = ((float)i) / (float)1000.0;
	}
	for (i = 0; i < ROWS; i++) {
		results[i] = 0.0f;
	}

#pragma omp barrier
	start_time = omp_get_wtime();
	mxv(matrix, vec, results, COLS, ROWS);
	end_time = omp_get_wtime();

	for (i = 0; i < ROWS; i++) {
		printf("res[%d]=%f\n", i, results[i]);
	}

	printf("Exe. Time = %f msec\n", (end_time - start_time) * 1000.0);

}

void mxv_serial(float (*matrix_d)[COLS], float* vector, float* result, int nocol, int norow) {
	for (int y = 0; y < norow; y++) {
		for (int x = 0; x < nocol; x++) {
			result[y] += matrix_d[y][x] * vector[x];
		}
	}
}

void do_prac8_code2_serial(void)
{
	float matrix[ROWS][COLS], results[ROWS], vec[COLS];
	int i, j;
	double start_time, end_time;

	/* initialize data */
	for (j = 0; j < ROWS; j++) {
		for (i = 0; i < COLS; i++) {
			matrix[j][i] = (((float)j) * COLS + (float)i) / (float)1000.;
		}
	}
	for (i = 0; i < COLS; i++) {
		vec[i] = ((float)i) / (float)1000.0;
	}
	for (i = 0; i < ROWS; i++) {
		results[i] = 0.0f;
	}

	start_time = omp_get_wtime();  // 시간 측정은 그대로 사용
	mxv_serial(matrix, vec, results, COLS, ROWS);
	end_time = omp_get_wtime();

	for (i = 0; i < ROWS; i++) {
		printf("res[%d]=%f\n", i, results[i]);
	}

	printf("Exe. Time (serial) = %f msec\n", (end_time - start_time) * 1000.0);
}


void mxv_clear(float (*matrix_d)[COLS], float* vector, float* result, int nocol, int norow) {
	float local_result = 0.0;

#pragma omp parallel for num_threads(4) private(local_result)
	for (int y = 0; y < norow; y++) {
		local_result = 0.0;
		for (int x = 0; x < nocol; x++) {
			local_result += matrix_d[y][x] * vector[x];
		}
		result[y] += local_result;
	}
}
void do_prac8_code2_clear(void)
{
	float matrix[ROWS][COLS], results[ROWS], vec[COLS];
	int i, j;
	double start_time, end_time;

	/* initialize data */
	for (j = 0; j < ROWS; j++) {
		for (i = 0; i < COLS; i++) {
			matrix[j][i] = (((float)j) * COLS + (float)i) / (float)1000.;
		}
	}
	for (i = 0; i < COLS; i++) {
		vec[i] = ((float)i) / (float)1000.0;
	}
	for (i = 0; i < ROWS; i++) {
		results[i] = 0.0f;
	}

#pragma omp barrier
	start_time = omp_get_wtime();
	mxv_clear(matrix, vec, results, COLS, ROWS);
	end_time = omp_get_wtime();

	for (i = 0; i < ROWS; i++) {
		printf("res[%d]=%f\n", i, results[i]);
	}

	printf("Exe. Time = %f msec\n", (end_time - start_time) * 1000.0);

}