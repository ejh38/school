/* Zach Sadler
 * zps6@pitt.edu
 * Tu/Tu 11am
 * Project 3
 */

#include "mymalloc.h"

int main()
{
	int *ptr_one;
	int *ptr_two;
	double *ptr_three;
	int *d;
	int *e;
	double *f;
	double *g;

	short *i;
	short *j;
	short *k;


	printf("sbrk(0) before : 0x%x\n", sbrk(0));
	ptr_one = (int *)my_worstfit_malloc(sizeof(int));
	ptr_two = (int *)my_worstfit_malloc(sizeof(int));
	ptr_three = (double*)my_worstfit_malloc(sizeof(double));
	f=(double*)my_worstfit_malloc(sizeof(double));
	g = (double*)my_worstfit_malloc(sizeof(double));
	
	printf("So after the allocations, it's : 0x%x\n\n", sbrk(0));

	*ptr_one = 25;		
	*ptr_two = 40;
	*ptr_three=1.434;
	*f = .22;
	*g = 30.1;

	my_free(g);
			my_free(f);
	d = (int*)my_worstfit_malloc(sizeof(int));
	*d = 5;
		e=(int*)my_worstfit_malloc(sizeof(int));
		*e = 4;
	my_free(ptr_one);
		my_free(d);
				printf("last thing to print\n");


		my_free(e);
	my_free(ptr_two);

	my_free(ptr_three);

	

	printf("\nFinally,  it's 0x%x\n", sbrk(0));	
	
	return 0;
}