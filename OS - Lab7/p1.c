#include<stdlib.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<time.h>
void f()
{
	int n;
	scanf("%d", &n);
}

int main() {
	signal(SIGTERM, f);
	
	for(;;) {

	sleep(2);
	}
	
}
