#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
int currentNumber;
int numberOfPrimes;

char isPrime(int n) {
    if (n <= 3) {
        return n > 1;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

void* threadWorker(void* arg) {
	int lastElement = *(int*) arg;
	char lastWasPrime = 0;
	while (1) {
		pthread_mutex_lock(&mutex);
		numberOfPrimes += lastWasPrime;
		++currentNumber;
		lastWasPrime = isPrime(currentNumber);
		if (currentNumber > lastElement) {
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int getNumberOfPrimes(int left, int right, int threads) {
	pthread_t thread_ids[threads];

	for (int i = 0; i < threads; ++i) {
		pthread_create(&thread_ids[i], NULL, threadWorker, (void*) &right);
	}

	for (int i = 0; i < threads; ++i) {
		pthread_join(thread_ids[i], NULL);
	}
	
	return numberOfPrimes;
}

int main(int argc, char** argv) {
	if (argc != 4) {
		printf("Expected 4 arguments.\n");
		exit(1);
	}
	
	int left = atoi(argv[1]);
	int right = atoi(argv[2]);
	int threads = atoi(argv[3]);

	pthread_mutex_init(&mutex, NULL);
	int totalNumberOfPrimes = getNumberOfPrimes(left, right, threads);
	pthread_mutex_destroy(&mutex);	

	printf("There are %d primes in the interval [%d, %d].\n", totalNumberOfPrimes, left, right);

	return 0;
}
