#include "main.h"


void subtask()
{
#pragma omp parallel num_threads(8)
	{
#pragma omp sections
		{
#pragma omp section
			{
				printf("첫 번째 작업 : %d번 Thread\n", omp_get_thread_num());
			}

#pragma omp section
			{
				printf("두 번째 작업 : %d번 Thread\n", omp_get_thread_num());
			}

#pragma omp section
			{
				printf("세 번째 작업 : %d번 Thread\n", omp_get_thread_num());
			}

#pragma omp section
			{
				printf("네 번째 작업 : %d번 Thread\n", omp_get_thread_num());
			}
		}
	}
}



void single() {
	int i = 0;
	omp_set_num_threads(4);
#pragma omp parallel firstprivate(i)
	{
		#pragma omp single
		{
			while (i++<20) {
				#pragma omp task
				printf("수행할 코드 : %2d, Thread : %d\n", i, omp_get_thread_num());
			}
		}
	}
}
