#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
int main() {
    int p[2],m,n,s;
    pipe(p);
    int pid = fork();
    if (pid > 0) {
		close(p[0]);
        printf("First number: ");
        scanf("%d",&m);
        write(p[1], &m, sizeof(int));
        printf("Second number: ");
        scanf("%d", &n);
        write(p[1], &n, sizeof(int));
        close(p[1]);
		wait(0);
    } else if (pid == 0) {
		close(p[1]);
        read(p[0], &m,sizeof(int));
        read(p[0], &n, sizeof(int));
        s = 0;
        s = m + n;
		printf("Sum: %d\n",s);
        close(p[0]);
        exit(0);
    }
}
