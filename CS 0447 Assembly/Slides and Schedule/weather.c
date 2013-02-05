#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
  int code;

  do {
    printf("Enter a code for the weather (0 to exit, 1-3)?\n");
    scanf("%d", &code);

    if (code == 0) {
      printf("Bye! Try Hawaii!\n");
    }
    else if (code == 1) {
      printf("It is cloudy in Pittsburgh today!\n");
    }
    else if (code == 2) {
      printf("It is flurrying in Pittsburgh today!\n");
    }
    else if (code == 3) {
      printf("It is snowing in Pittsburgh today!\n");
    }
    else {
      printf("You must have the wrong city!! (Wrong code entered.)\n");
    }
  } while (code != 0);
}
