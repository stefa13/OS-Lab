#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main() {
	int p1[2],p2[2],len1 = 0,len2 = 0;
	char s[100] ;
	pipe(p1);
	int pid1 = fork();
	if (pid1 == 0) {
		close(p1[1]);
		
		while (read(p1[0],s,100)) {
			len1 += strlen(s);
		}
		printf("Child 1 received %d characters from strings with 'oa'\n",len1);
		close(p1[0]);
		exit(0);
	}
	pipe(p2);
	int pid2 = fork();  
	if (pid2 == 0) {
		close(p2[1]);
		while (read(p2[0],s,100)) {
			len2 += strlen(s);	
		}
		printf("Child 2 received %d characters from the other strings\n",len2);
		close(p2[0]);
		exit(0);
	} 
	close(p1[0]);
	close(p2[0]);
	while (1) {
		fgets(s,100,stdin);
		s[strlen(s)-1] = 0;
		if (strlen(s) == 0) {
			break;
		}
		if (strstr(s, "oa")) {
			write(p1[1],s, (strlen(s)+1)*sizeof(char));
		} else {
			write(p2[1],s,(strlen(s)+1)*sizeof(char));
		}
	
	}
	close(p1[1]);
	close(p2[1]);
	wait(0);
	wait(0);
}	
