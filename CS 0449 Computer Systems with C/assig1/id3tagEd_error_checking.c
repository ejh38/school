#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {	
	struct id3_tag {
		char tag_id[3];
		char title[30];
		char artist[30];
		char album[30];
		char year[4];
		char comment[28];
		char seperator;
		char track;
		char genre_id;
	} ;

	struct id3_tag tag;		// the tag!
	short i;							// used in for loop

	char value_string[30];
	char field_name[10];
	short char_read;
	short char_to_read;
	short overflow;
	short collect_spaces;		// if 1 then get the spaces from the values

	strncpy(tag.tag_id, "TAG", 3);

	FILE *f = fopen(argv[1], "r+b");
	if (f == NULL) {
		printf("\nImproper formatting! Please use the format:\n");
		printf("\"id3tagEd FILENAME -FIELD VALUE -FIELD VALUE ...\"\n");
		printf("(Couldn't find that filename)\n");
		printf("\nExiting the program, please try again with proper formatting.\n");
	}
	else {

		fread(value_string, 3, 1, f);
		if (strncmp(value_string, "TAG", 3) == 0) {
			printf("FOUND IT AT THE TOP\n");
			fseek(f, -3, SEEK_CUR);
			fread(&tag, sizeof(tag), 1, f);
		}
		else {
			fseek(f, -128, SEEK_END);
			fread(value_string, 3, 1, f);
			if (strncmp(value_string, "TAG", 3) == 0) {
				printf("FOUND IT AT THE BOTTOM\n");
				fseek(f, -3, SEEK_CUR);
				fread(&tag, sizeof(tag), 1, f);
			}
			else {
				printf("Didn't find it\n");
			}
		}

		if (argc == 2) {
			printf("\nTitle: %-.30s\n", tag.title);
			printf("Artist: %-.30s\n", tag.artist);
			printf("Album: %-.30s\n", tag.album);
			printf("Track: %-3d\n", tag.track);
			printf("Year: %-.4s\n", tag.year);
			printf("Comment: %-.28s\n", tag.comment);
		}
		else if (argc > 2) {

			for (i = 2; i < argc; i++) {
				// first, read the -FIELD
				if (strncmp(argv[i], "-", 1) != 0) {			// if no '-' then we don't have a field
					printf("\nImproper formatting! Please use the format:\n");
					printf("\"id3tagEd FILENAME -FIELD VALUE -FIELD VALUE ...\"\n");
					printf("(You missed the '-' before '%s')\n", argv[i]);
					printf("\nExiting the program, please try again with proper formatting.\n");
					break;		// error, so break
				}
				// if here then we have a field name
				// now lets see if it's a valid one
				strcpy(field_name, argv[i]);

				// if here, then you're reading a field name
				if (strcmp(field_name, "-title") == 0) {
					char_to_read = 30;
					collect_spaces = 1;
				}
				else if (strcmp(field_name, "-artist") == 0) {
					char_to_read = 30;
					collect_spaces = 1;
				}
				else if (strcmp(field_name, "-album") == 0) {
					char_to_read = 30;
					collect_spaces = 1;			
				}
				else if (strcmp(field_name, "-track") == 0) {
					char_to_read = 3;
				}
				else if (strcmp(field_name, "-year") == 0) {
					char_to_read = 4;
				}
				else if (strcmp(field_name, "-comment") == 0) {
					char_to_read = 28;
					collect_spaces = 1;			
				}
				else {
					printf("\nImproper formatting! Please use the format:\n");
					printf("\"id3tagEd filename -field value -field value ...\"\n");
					printf("The choices for field are:\n");
					printf("'title', 'artist', 'album', 'track', 'year', 'comment'\n");	
					printf("(You used a field other than one of these: %s)\n", argv[i]);
					printf("\nExiting the program, please try again with proper formatting.\n");

				break;
				}
				if (i + 1 >= argc) {
					printf("\nImproper formatting! Please use the format:\n");
					printf("\"id3tagEd filename -field value -field value ...\"\n");
					printf("(You are missing a value for the field: %s\n", argv[i]);
					printf("\nExiting the program, please try again with proper formatting.\n");
					break;
				}

				char_read = 0;											// reset this counter
				overflow = 0;												// and this flag
				strcpy(value_string, argv[i+1]);		// then read in the first value argument
				char_read = strlen(value_string);		// and increase char_read appropriately
				
				i++;

				if (strncmp(value_string, "-", 1) == 0) {
					// if we're here then there was a -field -field, which is wrong
					printf("\nImproper formatting! Please use the format:\n");
					printf("\"id3tagEd filename -field value -field value ...\"\n");
					printf("(You seem to be missing a value for the field: %s)\n", argv[i - 1]);
					printf("\nExiting the program, please try again with proper formatting.\n");
					break;
				}
				else  {
					// this loop catches any extra input beyond the first value
					// it reads until one of the following: 
					//			1) char_read gets to maximum, 2) run out of values, 3) reach a field
					while ((char_read < char_to_read) && (i + 1 < argc)) {
						if (strncmp(argv[i+1], "-", 1) != 0) {
							if (strlen(value_string) + strlen(argv[i+1]) + collect_spaces > char_to_read) {
								// if we had done the read in, we would've overflowed
								overflow = 1;									// so mark the error code
								char_read = char_to_read;			// and break us out of the while loop
							}
							else {
								if (collect_spaces) {
									strncat(value_string, " ", 1);
									char_read++;
								}
								strncat(value_string, argv[i+1], char_to_read - strlen(value_string));
								char_read = strlen(value_string);
								i++;
							}
						}	// end strncmp(...) != 0
						else {
							break;		// if we get '-' then we're done reading in extra values
						}
					}	// end while loop

					if (i + 1 < argc || overflow) {
						if (strncmp(argv[i+1], "-", 1) != 0 && char_read == char_to_read) {
							// if we're here then we've finished reading in characters but 
							printf("\nImproper formatting! Please use the format:\n");
							printf("\"id3tagEd filename -field value -field value ...\"\n");
							printf("(You seem to have exceeded the maximum number\n");
							printf("of characters allowed for '%s', which is: %d)\n", field_name, char_to_read);
							printf("\nExiting the program, please try again with proper formatting.\n");
							break;
						}
					}	// end overflow error

				}	// end getting the extra values

				if (strcmp(field_name, "-title") == 0) {
					strcpy(tag.title, value_string);
				}
				else if (strcmp(field_name, "-artist") == 0) {
					strcpy(tag.artist, value_string);
				}
				else if (strcmp(field_name, "-album") == 0) {
					strcpy(tag.album, value_string);
				}
				else if (strcmp(field_name, "-track") == 0) {
					tag.track = atoi(value_string);
				}
				else if (strcmp(field_name, "-year") == 0) {
					strcpy(tag.year, value_string);
				}
				else if (strcmp(field_name, "-comment") == 0) {
					strcpy(tag.comment, value_string);		
				}
				if (strcmp(field_name, "") != 0) {
					tag.genre_id = 0;
				}
			}	// end for loop

			fseek(f, -128, SEEK_END);
			fwrite(&tag, 128, 1, f);
			printf("Succesfully changed tag\n");

		}	// end argc > 2

		fclose(f);
	}	// end f != NULL

	return 0;
}
