#include <stdio.h>
#include <stdlib.h>

/*
#define RED "\x1B[31m"
#define WHITE "\x1B[37m"
#define MAGENTA "\x1B[35m"
*/

#define RED "\e[1;31m"
#define MAG "\e[1;35m"
#define WHT "\e[1;37m"

void exit_pl(FILE* fptr1, FILE* fptr2) {
	if (fptr1 == NULL)
		printf("Failed to open the first file\n");
	else
		fclose(fptr1);
	if (fptr2 == NULL)
		printf("Failed to open the second file\n");
	else
		fclose(fptr2);
	exit(1);
}

void prettyline(char* file1, char* file2) {
	// create file pointers
	FILE* fptr1;
	FILE* fptr2;

	// open both files
	fptr1 = fopen(file1, "r");
	fptr2 = fopen(file2, "r");

	// start printing if neither file is NULL
	if (fptr1 && fptr2) {
		printf("%sred%s\n", RED, WHT);
		printf("%smagenta%s\n", MAG, WHT);
	} else
		exit_pl(fptr1, fptr2);
}

int main(int argc, char* argv[]) {

	if (argc < 3) {
		printf("Please enter two files to prettyline\n");	
		exit(1);
	}

	prettyline(argv[1], argv[2]);

	return 0;
}
