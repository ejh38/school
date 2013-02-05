#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *do_stuff(void *p) {

	while (1) {
		pthread_mutex_lock(&mutex);
		printf("Hello from thread %d - A\n", *(int *)p);
		pthread_yield_np();
		printf("Hello from thread %d - B\n", *(int *)p);
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, char **argv) {

	pthread_t thread; 
	int id, arg1, arg2;

	arg1 = 1; 
	id = pthread_create(&thread, NULL, do_stuff, (void *)&arg1);

	arg2 = 2;
	do_stuff((void *)&arg2); 
	return 0;	
}
