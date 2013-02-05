#include <stdio.h>
#include <string.h>

int main() {

	short front = 0;
	short back;
	short is_palindrome = 1;
	char in_str[10];

	printf("Gimme a string: ");
	scanf("%s", in_str);
	back = strlen(in_str);

	while (front < back) {
		if (in_str[front] != in_str[back]) {
			is_palindrome = 0;
		}
		front++;
		back--;
	}

	printf("is_palindrome: %d", is_palindrome);

	return 0;
}