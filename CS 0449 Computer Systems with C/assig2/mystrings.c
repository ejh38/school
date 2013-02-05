/*************************
 * Zach Sadler - zps6@pitt.edu
 * Lab Thursday 3pm
 * Project 2 - mystrings.c
 * Displays the strings (4+ ASCII characters in a row)
 * one per line, to the terminal. Works with abritrary-sized strings.
 ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	char input;					// used for byte-by-byte checking
	short counter;			// used to see if we've gotten at least 4
	int eof_checker;		// to see if we succesfully read a byte

	// need to specify a command-line filename
	if (argc < 2) {
		printf("\nYou're missing a filename! Please run again with a filename.\n");
		return 1;
	}

	// open the file specified, or quit if that doesn't work
	FILE *f = fopen(argv[1], "rb");	
	if (f == NULL) {
		printf("\nCouldn't find that filename.");
		printf("\nExiting the program, please run again with a real file.\n");
		return 2;
	}

	printf("These are the strings I found in %s:\n\n", argv[1]);

	// while the EOF has not been consumed
	while (!feof(f)) {
		
		counter = 0;	// reset the counter
		
		do {
			eof_checker = fread(&input, 1, 1, f);	// read in a byte
			counter++;														// increment the counter
		} while (input >= 32 && input <= 126 && eof_checker != 0);	
		// if we're here then we either hit a non-readable character
		// which is EOF if eof_checker != 0

		// if we got at least four characters, then go back and print them
		if (counter >= 4) {
			char *ptr = malloc(counter);		// this gives arbitrary size
			fseek(f, -counter, SEEK_CUR);		// rewind the file pointer	
			fread(ptr, 1, counter, f);			// and read in the string
			printf("%s", ptr);							// so you can print it out
		}
	}
	fclose(f);		// close the file that we opened
	printf("\n");	// for nice formatting

	return 0;
}