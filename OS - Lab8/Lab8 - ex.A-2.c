#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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

typedef struct {
	int left;
	int right;
} Interval;

void* getPrimesForInterval(void* arg) {
	Interval* interval = (Interval*) arg;
	int counter = 0;
	for (int i = interval->left; i <= interval->right; ++i) {
		counter += isPrime(i);
	}
	int* result = (int*) malloc(sizeof(int));
	*result = counter;
	return result;
}

int getNumberOfPrimes(int left, int right, int threads) {
	int numberOfElements = right - left + 1;
	int elementsPerThread = numberOfElements / threads;

	pthread_t thread_ids[threads];
	Interval intervals[threads];

	for (int i = 0; i < threads; ++i) {
		intervals[i] = (Interval) {
			.left = i * elementsPerThread + left,
			.right = (i + 1) * elementsPerThread + left - 1
		};
	}
	intervals[threads - 1].right = right;

	for (int i = 0; i < threads; ++i) {
		pthread_create(&thread_ids[i], NULL, getPrimesForInterval, (void*) &intervals[i]);
	}

	int result = 0;

	for (int i = 0; i < threads; ++i) {
		int* partial_sum = NULL;
		pthread_join(thread_ids[i], (void**) &partial_sum);
		result += *partial_sum;
		free(partial_sum);
	}

	return result;
}

int main(int argc, char** argv) {
	if (argc != 4) {
		printf("Expected 4 arguments.\n");
		exit(1);
	}
	int left = atoi(argv[1]);
	int right = atoi(argv[2]);
	int threads = atoi(argv[3]);
	int numberOfPrimes = getNumberOfPrimes(left, right, threads);
	printf("There are %d primes in the interval [%d, %d].\n", numberOfPrimes, left, right);
	return 0;
}
