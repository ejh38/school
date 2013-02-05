#include <stdio.h>

int main() {
	short player_wins;
	short ai_wins;
	int player_choice;			// 0 for rock, 1 for paper, 2 for scissors
	int ai_choice;					// and same codes for the computer
	char player_input[10];	// the string for checking yes, rock, paper, scissors
	short done;

	srand((unsigned int)time(NULL));																// seed the rng
	printf("Yeaahhh!!! It's time for Rock, Paper, Scissors!!!\n");	// pump up the crowd

	while (done != 1) {							// loop until 'done'
		printf("\nWant to play? ");		// prompt for playing
		scanf("%s", player_input);		// take in the string

		if (strcmp(player_input, "yes") != 0 && strcmp(player_input, "Yes") != 0 && strcmp(player_input, "YES") != 0) {
			printf("\nOh. Fine. Be that way.\n");
			done = 1;										// set the flag for exiting the outermost loop
		}
		else {																					// if the player wants to play, then loop
			while (player_wins < 3 && ai_wins < 3) {			// while neither player has won

				printf("\n\nMake your choice! Rock, paper, or scissors? ");
				scanf("%s", player_input);

				// I accept lower case, title case, or upper case input, anything else is rejected and the player re-inputs
				if (strcmp(player_input, "rock") == 0 || strcmp(player_input, "Rock") == 0 || strcmp(player_input, "ROCK") == 0) {
					player_choice = 0;
				}
				else if (strcmp(player_input, "paper") == 0 || strcmp(player_input, "Paper") == 0 || strcmp(player_input, "PAPER") == 0) {
					player_choice = 1;
				}
				else if (strcmp(player_input, "scissors") == 0 || strcmp(player_input, "Scissors") == 0 || strcmp(player_input, "SCISSORS") == 0) {
					player_choice = 2;
				}
				else {
					printf("Sorry there, I didn't understand what you just said. Can you try again?");
					continue;			// loop back around and try to get proper input this time
				}
				
				// if we're here, we have valid input, so calculate the computer's choice
				ai_choice = rand() % (3);	// returns 0, 1, or 2 (for rock, paper, scissors)
				switch (ai_choice) {
					case 0:
						printf("The computer rushes in with rock! ");
						break;
					case 1:
						printf("The computer pummels you with paper! ");
						break;
					case 2:
						printf("The computer slashes forward with scissors! ");
						break;
				}

				// then calculate the winner
				if (player_choice == ai_choice) {
					printf("Aw man, it was a tie.\n");
				}
				else if ((player_choice == 0 && ai_choice == 2) || (player_choice == 1 && ai_choice == 0) || (player_choice == 2 && ai_choice == 1)) {
					printf("Woohoo! You beat him!\n");
					player_wins++;
				}
				else {
					printf("Boo! The computer won.\n");
					ai_wins++;
				}

				printf("\nThe score is -- You: %d, Computer: %d\n\n", player_wins, ai_wins);

			}		// end individual game loop

			// announce the winner
			if (player_wins == 3) {
				printf("And the winner, with a score of %d to %d, is... YOU!!\nBravo! Excellent! Fantastic!\n", player_wins, ai_wins);
			}
			else if (ai_wins == 3) {
				printf("And the winner, with a score of %d to %d, is... the computer :(\nAw, no. Sorry. Shucks.\n", ai_wins, player_wins);
			}

			player_wins = 0;		// reset these so we don't immediately re-exit the loop
			ai_wins = 0;
		}			// end the 'want to play' loop
	}

	printf("Thanks for stopping by.\n");
	return 0;
}
