#include "main.h"


void parallel_pro(void) {
	int sec = 0;

#pragma omp parallel
	{
		if (omp_get_thread_num() == 0) {
			printf("The number of Threads = %d\n\n", omp_get_num_threads());
		}
	}

#pragma omp parallel
	{
		printf("Hello! tid is %d\n", omp_get_thread_num());
	}
	printf("\n\n");



	omp_set_num_threads(4);
#pragma omp parallel
	{
		if (omp_get_thread_num() == 0) {
			printf("Set the number of Threads = %d\n\n", omp_get_num_threads());
		}
	}
#pragma omp parallel
	{
		printf("Hello! tid is %d\n", omp_get_thread_num());
	}

}