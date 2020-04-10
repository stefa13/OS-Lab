#include<stdlib.h>
#include<signal.h>
#include<stdio.h>
#include<time.h>
#include<sys/syscall.h>
#include<sys/types.h>
#include<unistd.h>

void date() {
	time_t currentTime;
	time(&currentTime);
	printf("%s", ctime(&currentTime));
}

int main() {
	signal(SIGHUP, date);
	for (;;) {
		sleep(2);
	}
}
