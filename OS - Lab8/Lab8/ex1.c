#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

int v = 0;
int n = 0;
pthread_mutex_t mutex;

void* function(void* param) {
	char* s = (char*) param;
	int v_l = 0;
	int n_l = 0;
	for (int i = 0; i < strlen(s); ++i) {
		if ( strchr("aeiouAEIOU", s[i])) {
			v_l += 1;
		}
		if (strchr("0123456789",s[i])) {
			n_l += 1;
		}
	}
	pthread_mutex_lock(&mutex);
	v += v_l;
	n += n_l;
	pthread_mutex_unlock(&mutex);
	free(s);
	return 0;
}

int main() {
	pthread_t threads[5];
	pthread_mutex_init(&mutex, NULL);
	char* s;
	for (int i = 0; i < 5; ++i) {
		s = (char*) malloc(sizeof(char) * 100);
		scanf("%s", s);	
		pthread_create(&threads[i], NULL, function, (void*) s);
	}
	for ( int i = 0; i < 5 ; ++i ) {
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("v = %d\n",v);
	printf("n = %d\n",n);

	return 0;
}
