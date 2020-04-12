#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>

int main() {
	int m, n, s;
	int mkfifoResult = mkfifo("/tmp/pb6", 0600);
	int pid = fork();
	if (pid == 0) {
		int c2p_r = open("/tmp/pb6", O_RDONLY);
		read(c2p_r, &m, sizeof(int));
		read(c2p_r, &n, sizeof(int));
		close(c2p_r);
		int c2p_w = open("/tmp/pb6", O_WRONLY);
		s = 0;
		s = m + n;
		write(c2p_w, &s, sizeof(int));
		close(c2p_w);
		exit(0);
	}
	int p2c_w = open("/tmp/pb6", O_WRONLY);
	printf("First number: ");
	scanf("%d", &m);
	write(p2c_w, &m, sizeof(int));
	printf("Second number: ");
	scanf("%d", &n);
	write(p2c_w, &n, sizeof(int));
	close(p2c_w);
	int p2c_r = open("/tmp/pb6", O_RDONLY);
	read(p2c_r, &s, sizeof(int));
	printf("Sum: %d\n", s);
	close(p2c_r);
	wait(0);
	unlink("/tmp/pb6");
}
