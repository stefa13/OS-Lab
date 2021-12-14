#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex;
int count_2 = 0;
int count_5 = 0;

void* function(void* param) {
	char* s = (char*)param;
	int n = atoi(s);
	int n_2 = 0;
	int	n_5 = 0;
	if ( n%2 == 0) {
		n_2 += 1;
	}
	if (n % 5 == 0) {
		n_5 += 1;
	}
	pthread_mutex_lock(&mutex);
	count_2 += n_2;
	count_5 += n_5;
	pthread_mutex_unlock(&mutex);
	return 0;
}

int main(int argc, char** argv) {
	pthread_mutex_init(&mutex,NULL);
	pthread_t threads[argc];
	for (int i = 1; i < argc; ++i) {
		pthread_create(&threads[i], NULL, function, (void*)argv[i]);
	}
	
	for (int i = 1; i < argc; ++i) {
		pthread_join(threads[i],NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of numbers divisible by 2: %d\n", count_2);
	printf("Number of numbers divisible by 5: %d\n", count_5);
	return 0;
}	
