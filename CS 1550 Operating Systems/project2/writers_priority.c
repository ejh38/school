// writers priority

int main(int argc, char ** argv) {

	// writers in the queue should all be allowed to write as soon as possible
	// to the queue, without waiting or caring if readers have read it or not

	// writer loop:
		// wait for the other writers
		// wait for the critical section
		// do the writing
		// signal cs
		// signal other writers

	// reader loop:
		// wait for the other readers
		// 

}