#include <stdio.h>
#include <hermit/syscall.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_THREADS 1

void* thread_func(void* arg)
{
	int id = *((int*) arg);
	char key[100];
	char val[3000];
	char out_val[3000];
	unsigned long len = 0;

	printf("Hello Thread!!! id = %d\n", id);

	memset(val,'C', 3000);
	strcpy(key, "mincheol");

	printf("put returns: %d\n", put(key, val, 3000));
	printf("get returns: %d\n", get(key, out_val, &len));
	printf("put returns: %d\n", put(key, val, 0));
	printf("put returns: %d\n", put(key, val, 0));
	return 0;
}

int main(int argc, char** argv)
{
	pthread_t threads[MAX_THREADS];
	int i, ret, param[MAX_THREADS];

	for(i=0; i<MAX_THREADS; i++) {
		param[i] = i;
		ret = pthread_create(threads+i, NULL, thread_func, param+i);
		if (ret) {
			printf("Thread creation failed! error =  %d\n", ret);
			return ret;
		} else printf("Create thread %d\n", i);
	}

	/* wait until all threads have terminated */
	for(i=0; i<MAX_THREADS; i++)
		pthread_join(threads[i], NULL);

	return 0;
}



