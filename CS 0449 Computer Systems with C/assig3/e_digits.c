

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "e.h"

int main(int argc, char **argv) {

	char *return_string;						// to be malloc'd later
	int start_val = atoi(argv[1]);	// the first argument
	int end_val = atoi(argv[2]);		// and second argument
	int amount = end_val - start_val + 1;

	if (argc != 3) {
		printf("You need to enter exactly two command-line arguments.\n");
		printf("Exiting program.\n");
		return 1;			// return error code 1
	}

	if (start_val < 0 || end_val < 0) {
		printf("Please enter a proper range:\n");
		printf("Both the start and end values must be non-negative.\n");
		return 2;			// return error code 2
	}

	if (start_val > end_val) {
		printf("Please enter a proper range:\n");
		printf("The start value must be <= than the end value.\n");
		return 3;			// return error code 3
	}

	FILE *f = fopen("e.txt", "rt");	// open up the file
	if (f == NULL) {
		printf("\nCouldn't find the file to open.\n");
		printf("Exiting the program, please run again with a valid file.\n");
		return 4;			// return error code 4
	}

	return_string = MALLOC(amount);	// get the space needed
/*
	fseek(f, start_val, SEEK_SET);		// go to where they want the first digit
	fread(return_string, 1, amount, f);
*/

	e(return_string, amount);

	printf("Here's what you wanted:\n%s", return_string);
	fclose(f);

	printf("\nAll done.\n");

	FREE(return_string);		// give back the memory


	return 0;
}