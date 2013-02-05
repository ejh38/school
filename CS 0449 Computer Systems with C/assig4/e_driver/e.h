#ifndef _E_H
#define _E_H

//I define malloc as a macro so you can test out the code without building 
//it into the kernel module, just to get your feet wet.
#ifdef GFP_KERNEL
#define MALLOC(s) kmalloc(s, GFP_KERNEL)
#define FREE(s) kfree(s)
#else
#define MALLOC(s) malloc(s)
#define FREE(s) free(s)
#endif

//This is a spigot algorithm for generating the digits of e without
//floating point math.

void e(char *buffer, int m)
{
	int i, j, q;
	int *A;
	A = MALLOC(m * sizeof(int));
	buffer[0] = '2';
	int next = 1;

	for ( j = 0; j < m; j++ )
		A[j] = 1;

	for ( i = 0; i < m - 2; i++ ) {
		q = 0;
		for ( j = m - 1; j >= 0; ) {
			A[j] = 10 * A[j] + q;
			q = A[j] / (j + 2);
			A[j] %= (j + 2);
			j--;
		}
		buffer[next++] = (q + '0');
	}
	FREE(A);
}

#endif
