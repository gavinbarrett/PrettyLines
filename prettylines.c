#include <stdio.h>
#include <stdlib.h>

// define ANSI color codes
#define RED "\e[1;31m"
#define MAG "\e[1;35m"
#define WHT "\e[1;37m"

void exit_pl(FILE* fptr1, FILE* fptr2) {
	//exit the prettylines program

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

char* allocate_mem(int stream_sz) {
	return (char*)malloc(stream_sz*sizeof(char));
}

char* realloc_mem(char* stream, int length) {
	return (char*)realloc(stream, length*2);
}

void finish_stream(FILE* fptr, char* stream, int length, char c) {
	// Finish reading file, appending colored
	// characters to the stream
	do {
		length += snprintf(stream+length, 10, "\e[1;31m%c", c);
		c = fgetc(fptr);
		if (feof(fptr)) {
			snprintf(stream+length, 9, "\e[0;37m");
			return;
		}
	} while(1);
}

void read_stream(FILE* fptr1, FILE* fptr2) {
	// create variables for characters
	char c1;
	char c2;
	int stream_sz1 = 500;
	int stream_sz2 = 500;
	// allocate memory for char streams
	char* cstream1 = allocate_mem(stream_sz1);
	char* cstream2 = allocate_mem(stream_sz2);
	if ((cstream1 == NULL) || (cstream2 == NULL)) {
		printf("Cannot allocate memory for charstreams\nExiting prettylines...");
		// close file pointers
		fclose(fptr1); fclose(fptr2);
		// free memory
		free(cstream1); free(cstream2);
		exit(1);
	}
	int length1 = 0;
	int length2 = 0;
	do {
		c1 = fgetc(fptr1);
		c2 = fgetc(fptr2);
		if (feof(fptr1)) {
			// file 1 is done; keep reading from file 2
			if (feof(fptr2))
				break;
			finish_stream(fptr2, cstream2, length2, c2);
			break;
		} else if (feof(fptr2)) {
			// file 2 is done; keep reading from file 1
			if (feof(fptr1))
				break;
			finish_stream(fptr1, cstream1, length1, c1);
			break;
		}
		if (length1 == (stream_sz1-1)) {
			realloc_mem(cstream1, stream_sz1);
			stream_sz1 *= 2;
		}
		if (length2 == (stream_sz2-1)) {
			realloc_mem(cstream2, stream_sz2);
			stream_sz2 *= 2;
		}
		if (c1 == c2) {
			length1 += snprintf(cstream1+length1, 2, "%c", c1);
			length2 += snprintf(cstream2+length2, 2, "%c", c2);
		} else {
			length1 += snprintf(cstream1+length1, 18, "\e[1;31m%c\e[0;37m", c1);
			length2 += snprintf(cstream2+length2, 18, "\e[1;31m%c\e[0;37m", c2);
		}
	} while(1);

	printf("%s\n", cstream1);
	printf("%s\n", cstream2);
	
	free(cstream1); free(cstream2);
}

void prettyline(char* file1, char* file2) {
	// run the prettylines program on file1 and file2

	// create file pointers
	FILE* fptr1;
	FILE* fptr2;

	// open both files
	fptr1 = fopen(file1, "r");
	fptr2 = fopen(file2, "r");

	// start printing if neither file is NULL
	if (fptr1 && fptr2) {
		read_stream(fptr1, fptr2);
		//printf("%sred%s\n", RED, WHT);
		//printf("%smagenta%s\n", MAG, WHT);
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
