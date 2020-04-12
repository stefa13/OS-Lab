#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("The program expects two arguments.\n");
		return 0;
	}

	char* word = argv[1];
	char* filename = argv[2];

	int p2c[2];
	pipe(p2c);

	int childPID = fork();
	if (childPID == 0) {
		close(p2c[0]);
		// redirect the output of grep from stdout to the writing end of the pipe
		dup2(p2c[1], 1);
		execlp("grep", "grep", word, filename, NULL);
		exit(0);
	}

	close(p2c[1]);

	// this will contain the entire results from grep, not individual lines
	char grepResult[MAX_STRING_LEN];
	read(p2c[0], grepResult, MAX_STRING_LEN);

	char* currentLine = strtok(grepResult, "\n");
	while (currentLine != NULL) {
		if (strlen(currentLine) % 3 == 0) {
			printf("%s\n", currentLine);
		}
		currentLine = strtok(NULL, "\n");
	}

	wait(0);
	return 0;
}
