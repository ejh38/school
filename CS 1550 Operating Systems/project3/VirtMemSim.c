/*********************
 * Zach Sadler - zps6
 * CS 1550 - Project 3 
 * 12/10/13
 *********************/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {

	// check for the right usage
	if (argc != 3) {
		printf("Oops, wrong usage. Call me like this\n");
		printf("./VirtMemSim BACKING_STORE.bin addresses.txt\n");
		return -1;
	}
						 /*******************************
							******************************* 
							*    VARIABLE DECLARATIONS    *
							*******************************
							*******************************/

	/******************
	 * FILE  POINTERS *
	 ******************/
	FILE * fp = fopen(argv[2], "r");					// open up addresses.txt
	FILE * backing_fp = fopen(argv[1], "r");	// open up BACKING_STORE.bin

	if (fp == NULL || backing_fp == NULL) {
		printf("Oops, wrong usage. Call me like this\n");
		printf("./VirtMemSim BACKING_STORE.bin addresses.txt\n");
		return -1;
	}

	/******************
	 * DATA STRUCTURES *
	 ******************/
	char physical_memory[256][256];			// rows are frames, 256 bytes in a row
	int page_table[256];								// maps page_numbers to frame_numbers
	int TLB[16][2];											// first column is page_number, second is frame number

	/******************
	 * TEMP VARIABLES *
	 ******************/
	char current_page[256];			// current page temp variable
	char adress_buffer[7];			// what we read the addresses into
	int virtual_address;				// the atoi version of address_buffer
	int page_number;						// the 8 bit chunk from virtual_address
	int offset; 								// the last 8 bits of virtual_address
	int frame = 0;							// because we may have two different values for physical address

	/******************
	 *    COUNTERS    *
	 ******************/
	unsigned char frame_counter = 0;		// a counter of our current frame
	char TLB_tail = 0;									// current position of the tail of our TLB

	int page_faults = 0;								// these three
	int TLB_hits = 0;										// for end program
	int translate_addresses = 0;				// statistics display


	/******************
	 * INITIALIZATION *
	 ******************/
	int i;	// index for loops
	for (i = 0; i < 256; i++) {
		page_table[i] = -1;						// initialize everything to flag value
	}
	for (i = 0; i < 16; i++) {
		TLB[i][0] = -1;
	}
						 /*******************************
							******************************* 
							*    ACTUAL      ALGORITHM    *
							*******************************
							*******************************/

	// go through the whole file, reading in at most 7 characters at a time
	while (fgets(adress_buffer, 7, fp) != NULL) {

		// get the virtual address, offset, and page_number
		virtual_address = atoi(adress_buffer);
		offset = virtual_address & 0xFF;
		page_number = virtual_address >> 8;
		page_number &= 0xFF;

		// set flag to 0 so we can check TLB
		char found = 0;

		// look through the TLB for this page
		for (i = 0; i < 16; i++) {
			if (TLB[i][0] == page_number) {
				frame = TLB[i][1];				// if we find it store physical address
				found = 1;								// set the flag to true
				TLB_hits++;								// and increment counter
				break;
			}
		}

		// if it wasn't in the TLB
		if (found == 0) {
			if (page_table[page_number] == -1) {
				// this means a page fault
				// so seek to the right place, and read it in
				fseek (backing_fp, page_number*256, SEEK_SET);
				fread(current_page, 1, 256, backing_fp);

				// then copy it byte-by-byte into physical memory
				for (i = 0; i < 256; i++) {
					physical_memory[frame_counter][i] = current_page[i];	
				}

				// set the page table at the page_number index to the frame_counter
				page_table[page_number] = frame_counter;
				frame = frame_counter;					// save this for printing
				frame_counter++;								// increment frame_counter
				page_faults++;									// increment counter
			}
			else {
				// not a page fault, so read the value from there
				frame = page_table[page_number];
			}

			// update the TLB with the page we got, whether page fault or not
			TLB[TLB_tail][0] = page_number;			// index 0 is page number
			TLB[TLB_tail][1] = frame;						// index 1 is frame number
			TLB_tail = (TLB_tail + 1) % 16;			// pick a legal TLB index in FIFO
		}

		// now print an answer for this virtual address
		printf("Virtual address: %d Physical address: %d Value: %d\n",
						virtual_address,  frame*256 + offset, 
						physical_memory[frame][offset]);

		translate_addresses++;	// increment this counters
	}
						 /*******************************
							******************************* 
							*   END PRINT OF STATISTICS   *
							*******************************
							*******************************/

	printf("Number of Translated Addresses = %d\n", translate_addresses);
	printf("Page Faults = %d\n", page_faults);
	printf("Page Fault Rate = %.3f\n", (float)page_faults/translate_addresses);
	printf("TLB Hits = %d\n", TLB_hits);
	printf("TLB Hit Rate = %.3f\n", (float)TLB_hits/translate_addresses);

	return 0;
}