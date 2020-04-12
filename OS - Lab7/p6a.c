#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    int m,n,s;

    int mkfifoResult = mkfifo("/tmp/pb6", 0600);

    if (mkfifoResult == -1) {
        perror("Failed!\n");
        exit(0);
    }
    int pid = fork();
    if (pid > 0) {
        int p2c = open("/tmp/pb6", O_WRONLY);
        printf("First number: ");
        scanf("%d",&m);
        write(p2c, &m, sizeof(int));
        printf("Second number: ");
        scanf("%d", &n);
        write(p2c, &n, sizeof(int));
        close(p2c);
        wait(0);
	 } else if (pid == 0) {
        int c2p = open("/tmp/pb6", O_RDONLY);
        read(c2p, &m,sizeof(int));
        read(c2p, &n, sizeof(int));
        s = 0;
        s = m + n;
        printf("Sum: %d\n",s);
        close(c2p);
        exit(0);
    }
     unlink("/tmp/pb6");
}
