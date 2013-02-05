#include <stdio.h>

int main(void)
{
	printf("int:\t\t%lu\n", sizeof(int));
	printf("short:\t\t%lu\n", sizeof(short));
	printf("long:\t\t%lu\n", sizeof(long));
	printf("long long:\t%lu\n", sizeof(long long));
	printf("unsigned int:\t%lu\n", sizeof(unsigned int));
	printf("char:\t\t%lu\n", sizeof(char));
	printf("float:\t\t%lu\n", sizeof(float));
	printf("double:\t\t%lu\n", sizeof(double));
	printf("long double:\t%lu\n", sizeof(long double));
}
