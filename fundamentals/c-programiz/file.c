/*
 *
 * Learn C Programming
 * C File Input and Output
 * https://www.programiz.com/c-programming
 *
 */

#include <stdio.h>
#include <stdlib.h>

// C File Handling

FILE *fptr;

void read(){
	fptr = fopen("sample-file.txt", "r+");
	if(fptr == NULL){
		printf("File not found.");
		return;
	}

	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	while((read = getline(&line, &len, fptr)) != -1){
		printf("Retrieved line of length %zu:\n", read);
		printf("%s\n", line);
	}

	fclose(fptr);
	if(line) free(line);
}

// Main 	

int main(){
	read();
	return 0;
}