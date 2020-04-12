#include <stdio.h>
#include <string.h>

#define MAX_STRING_LEN 4096

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("The program expects two arguments.\n");
		return 0;
	}

	char* word = argv[1];
	char* filename = argv[2];

	// first, build the command string
	// "grep word filename"
	char someString[MAX_STRING_LEN] = "grep ";
	strcat(someString, word);
	strcat(someString, " ");
	strcat(someString, filename);		

	FILE* fp = popen(someString, "r");
	
	while(fgets(someString, MAX_STRING_LEN, fp)) {
		someString[strlen(someString) - 1] = 0;
		if (strlen(someString) % 3 == 0) {
			printf("%s\n", someString);
		}
	}

	pclose(fp);
	return 0;
}
