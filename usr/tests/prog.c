#include <stdio.h>
#include <hermit/syscall.h>
//#include <hermit/stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_THREADS 4

void* thread_func(void* arg)
{
	int id = *((int*) arg);
	char key[100];
	char val[100];
	char out_val[100];
	unsigned long len = 0;
	char c = 'C' + id;
	int i;
	//char *val = palloc(100, VMA_USER);
	printf("Hello Thread!!! id = %d\n", id);

	memset(val, c, 100);
	strcpy(key, "KEY");
	strcat(key, (char *)&c);

	printf("put returns: %d\n", put(key, val, 100));
	printf("get returns: %d\n", get(key, out_val, &len));
	
	printf("(Thread%d) key:%s, len:%d, val:", id, key, len);
	for (i = 0; i < len; i++)
	{
		printf("%c", out_val[i]);
	}
	printf("\n");

	printf("delete returns: %d\n", put(key, NULL, 0));

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



