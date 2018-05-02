#include <stdio.h>
#include <hermit/syscall.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_THREADS 4

#define KEY_SIZE 1024
#define VAL_SIZE 4096


void* thread_func(void* arg)
{
	int id = *((int*) arg);
	char *key = malloc(KEY_SIZE);
	char *val = malloc(VAL_SIZE);
	char *out_val = malloc(VAL_SIZE);
	unsigned long len = 0;
	char c = 'C' + id;
	int i;
	
	printf("Hello Thread!!! id = %d\n", id);

	memset(key, 'k', KEY_SIZE-2);
	key[KEY_SIZE-2] = c;
	key[KEY_SIZE-1] = '\0';
	
	memset(val, c, VAL_SIZE);

	printf("put returns: %d\n", put(key, val, VAL_SIZE));
	printf("get returns: %d\n", get(key, out_val, &len));
	
	printf("(Thread%d) len:%d, val:", id, len);
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



