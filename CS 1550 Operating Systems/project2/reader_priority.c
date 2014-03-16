#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "asm/unistd.h"
#include "linux/sched.h"
#include <sys/mman.h>
#include <time.h>


struct ProcQ {
	struct task_struct *task;
	struct ProcQ *nextTask;
};

struct RW_Sem {
	int value;
	struct ProcQ *waitingQ;
};

struct RW_Sem * setup_RW_sem();

void readers_loop(struct RW_Sem *readers, struct RW_Sem *writers,
								 struct RW_Sem *critical_section, 
								 int i, int *theValue, int *numReaders,
								 int *j);

void writers_loop(struct RW_Sem *a, struct RW_Sem *b, struct RW_Sem *c, int i, int *d,
									int *j);


/* Expected usage:
 * ./reader_priority x y
 * where x = # of readers
 * and y = # of writers
 */
int main(int argc, char ** argv) {
	// check for the command line argument
	if (argc != 3) {
		printf("Oops, wrong usage. Call me like this\n");
		printf("./reader_priority x y\n");
		printf("if you want x readers and y writers.\n");
		return -1;
	}


	struct RW_Sem *readers = setup_RW_sem();
	struct RW_Sem *writers = setup_RW_sem();
	struct RW_Sem *critical_section = setup_RW_sem();


	int *newValue = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE,
																MAP_SHARED|MAP_ANONYMOUS, 0, 0);


	int *theValue = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE,
																MAP_SHARED|MAP_ANONYMOUS, 0, 0);

	*newValue = 1;
	*theValue = 4;

	int *numReaders = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE,
																MAP_SHARED|MAP_ANONYMOUS, 0, 0);
	int i;
	for (i = 0; i < atoi(argv[1]); i++) {
		if (fork() != 0) {
			// let the children do the reading and waiting
			readers_loop(readers, writers, critical_section, i, theValue, numReaders, newValue);
		}
		// while the parent just loops back around
	}

	for (i = 0; i < atoi(argv[2]); i++) {
		if (fork() != 0) {
			writers_loop(readers, writers, critical_section, i, theValue, newValue);
		}
	}

	// only one parent should print this in the end
	// need to wait for the children!
	while (1) {
		// do nothing
	}
	printf("All done here!\n");

	return 0;
}

void readers_loop(struct RW_Sem *readers, struct RW_Sem *writers,
								 struct RW_Sem *critical_section, int i, int *theValue, int *numReaders,
								 int *newValue) {

	int oldValue = -901328313;
	while (1) {

		if (oldValue == *theValue) {
			continue;
		}
		// wait to increment numReaders
		syscall(__NR_RW_wait, readers);
		*numReaders++;
		// if first one here then wait on the critical section if writers are in
		if (*numReaders == 1) {
			syscall(__NR_RW_wait, critical_section);
			*newValue = 1;
		}
		// let someone else in to adjust numReaders
		syscall(__NR_RW_signal, readers);

		// do the actual reading

		printf("Reader %d read the value %d\n", i+1, *theValue);
		oldValue = *theValue;

		// wait to decrement numReaders
		syscall(__NR_RW_wait, readers);
		*numReaders--;

		// if last one out then tell writer he can write 
		if (*numReaders == 0) {
			*newValue = 1;
			syscall(__NR_RW_signal, critical_section);
			syscall(__NR_RW_signal, writers);
		}
		syscall(__NR_RW_signal, readers);
	}			
}

void writers_loop(struct RW_Sem *a, struct RW_Sem *b, struct RW_Sem *c, int i, int *d,
									int *newValue) {
	struct RW_Sem *readers = a;
	struct RW_Sem *writers = b;
	struct RW_Sem *critical_section = c;
	int *theValue = d;

	srand(time(NULL));

	while (1) {
		if (*newValue == 0) {
			continue;
		}

		// wait for other writers to finish
		syscall(__NR_RW_wait, writers);
		// wait for any readers that would be in the critical section
		syscall(__NR_RW_wait, critical_section);

		// do the writing
		*theValue = rand();
		printf("Writer %d wrote the value %d\n", i+1, *theValue);
		*newValue = 0;
		//random number goes here

		// let in other readers
		syscall(__NR_RW_signal, critical_section);
		syscall(__NR_RW_signal, readers);

		// and let in other writers
		syscall(__NR_RW_signal, writers);
	}
}


struct RW_Sem * setup_RW_sem() {
	struct ProcQ *queue = mmap(NULL, sizeof(struct ProcQ), PROT_READ|PROT_WRITE,
															MAP_SHARED|MAP_ANONYMOUS, 0, 0);
	queue->task = NULL;
	queue->nextTask = NULL;

	struct RW_Sem *rw = mmap(NULL, sizeof(struct RW_Sem), PROT_READ|PROT_WRITE, 
															MAP_SHARED|MAP_ANONYMOUS, 0, 0);

	rw->value = 1;
	rw->waitingQ = queue;

	return rw;
}
