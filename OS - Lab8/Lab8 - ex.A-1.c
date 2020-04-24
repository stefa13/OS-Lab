#include <stdio.h>
#include <stdlib.h>

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

int getNumberOfPrimes(int left, int right) {
	int counter = 0;
	for (int i = left; i <= right; ++i) {
		counter += isPrime(i);
	}
	return counter;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Expected 3 arguments.\n");
		exit(1);
	}
	int left = atoi(argv[1]);
	int right = atoi(argv[2]);
	int numberOfPrimes = getNumberOfPrimes(left, right);
	printf("There are %d primes in the interval [%d, %d].\n", numberOfPrimes, left, right);
	return 0;
}
