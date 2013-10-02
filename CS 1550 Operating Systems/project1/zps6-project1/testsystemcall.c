#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "asm/unistd.h"
#include <time.h>
#include <math.h>
#include <sys/time.h>

// function prototypes!
double average(long * array, int iterations);
double stddev(long * array, int iterations);

// our function
// it requires a command line argument
// for the number of iterations of our syscall
int main(int argc, char ** argv) {
	// check for the command line argument
	if (argc != 2) {
		printf("Oops, wrong usage. Call me like this\n");
		printf("./testsystemcall 100\n");
		printf("if you want to test 100 iterations\n");
		return -1;
	}

	int iterations = atoi(argv[1]);	// parse the number of iterations
	// set up our time difference array
	long * time_diffs;
	time_diffs = (long *)malloc(sizeof(long) * iterations);

	printf("Calling... \n");
	struct timeval init_time;	// setup our beginning
	struct timeval  end_time;	// and end time structs

	int i;
	for (i = 0; i < iterations; i++) {
		gettimeofday(&init_time,  NULL);	// before time
		syscall(__NR_hellokernel, 42);		// syscall!
		gettimeofday(&end_time, NULL);		// after time
		
		// this calculates the actual time difference
		time_diffs[i] = (end_time.tv_sec - init_time.tv_sec)*1000000 + end_time.tv_usec - init_time.tv_usec;	
	}

	// display the average and standard deviation
	printf("\n\nThe average time to execute syscall is: %f\n", average(time_diffs, iterations));
	printf("The standard deviation is: %f\n", stddev(time_diffs, iterations));	
	printf("Thanks for playing!\n");
	free(time_diffs);	// free our pointer

	return 0;
}

// sum up the values in the array
// then divide by how many values were in it
double average(long * array, int iterations) {
	double avg = 0;
	int i;
	for (i = 0; i < iterations; i++) {
		avg += array[i];
	}
	avg /= iterations;
	return avg;
}

// standard deviation formula, straight from a stats book
double stddev(long * array, int iterations) {
	double avg = 0, deviation_total = 0;
	int i;
	avg = average(array, iterations);

	// stddev formula
	for (i = 0; i < iterations; i++) {
		deviation_total += (array[i]-avg)*(array[i]-avg);
	}

	deviation_total /= iterations; // now we have the average of our squared sums

	return sqrt(deviation_total);
}
