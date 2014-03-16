#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "asm/unistd.h"
#include "linux/sched.h"
#include <sys/mman.h>

struct ProcQ {
	struct task_struct *task;
	struct ProcQ *nextTask;
};

struct RW_Sem {
	int value;
	struct ProcQ *waitingQ;
};

// our function
// it requires a command line argument
// for the number of iterations of our syscall
int main(int argc, char ** argv) {
	// check for the command line argument
	if (argc != 3) {
		printf("Oops, wrong usage. Call me like this\n");
		printf("./testsystemcall x y\n");
		printf("if you want x readers and y writers.\n");
		return -1;
	}

	printf("Making structs... \n");

	struct RW_Sem *test = mmap(NULL, sizeof(struct RW_Sem), PROT_READ|PROT_WRITE, 
															MAP_SHARED|MAP_ANONYMOUS, 0, 0);

	test->value = 4;

	struct ProcQ *queue = mmap(NULL, sizeof(struct ProcQ), PROT_READ|PROT_WRITE,
															MAP_SHARED|MAP_ANONYMOUS, 0, 0);
	queue->task = NULL;
	queue->nextTask = NULL;

	test->waitingQ = queue;

	printf("Make it here?\n");
	if (fork() == 0) {
		fork();
		fork();
		syscall(__NR_RW_wait, test);
		printf("Done with the parent!\n");	
	}
	else {
		fork();
		fork();
		syscall(__NR_RW_signal, test);
	}

	printf("All done here!\n");


	return 0;
}
