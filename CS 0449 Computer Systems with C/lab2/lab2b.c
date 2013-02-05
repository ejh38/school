#include <stdio.h>

int main(void)
{
	int weight;

	printf("Hey, tell me what weight you would like to convert: ");
	scanf("%d", &weight);
	
	printf("\n\nHere's your weight on some other planets:\n\n");
	printf("Mercury\t\t%4.2f lbs\n", weight*.38);
	printf("Venus\t\t%4.2f lbs\n", weight*.91);
	printf("Mars\t\t%4.2f lbs\n", weight*.38);
	printf("Jupiter\t\t%4.2f lbs\n", weight*2.54);
	printf("Saturn\t\t%4.2f lbs\n", weight*1.08);
	printf("Uranus\t\t%4.2f lbs\n", weight*.91);
	printf("Nepune\t\t%4.2f lbs\n", weight*1.19);
	printf("Pluto\t\t%4.2f lbs\n", weight*.06);
	
}
