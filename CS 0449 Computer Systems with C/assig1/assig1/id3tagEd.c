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

	struct id3_tag tag;			// the tag!
	short i;								// used in for loop

	char field_name[10];		// for reading in the 'field'
	char value_string[30];	// for reading in the 'value'

	short char_to_read;			// to read in 4/28/30, whatever number of characters
	short no_tag_found;			// a flag for a file without tag3
	short found_top;				// a flag to know to write in place instead of the end

	strncpy(tag.tag_id, "TAG", 3);			// load this value, since it won't be otherwise

	FILE *f = fopen(argv[1], "r+b");		// try to open the filename given on cmd line	
	if (f == NULL) {
		printf("Couldn't find that filename.\n");
		printf("\nExiting the program, please try again with proper formatting.\n");
	}
	else {
		printf("Opened: %s\n", argv[1]);

		fread(value_string, 3, 1, f);		// found the filename, so let's look for the tag
		if (strncmp(value_string, "TAG", 3) == 0) {
			// found the tag at the beginning of the file
			fseek(f, -3, SEEK_CUR);						// so move back the three bytes we read
			fread(&tag, sizeof(tag), 1, f);		// and read in the tag
			found_top = 1;
		}
		else {																// didn't see it at the beginning, so try end 
			fseek(f, -sizeof(tag), SEEK_END);						// change where we'll read
			fread(value_string, 3, 1, f);				// and look for the tag again
			if (strncmp(value_string, "TAG", 3) == 0) {
				// found the tag at the end of the file
				fseek(f, -3, SEEK_CUR);						// move back the three bytes we read
				fread(&tag, sizeof(tag), 1, f);		// and read in the tag
			}
			else {
				printf("No id3tag found.\n");
				no_tag_found = 1;
			}
		}

		if (argc == 2 && no_tag_found != 1) {
			// just the filename given, there's a tag present, so show it
			printf("\nTitle: %-.30s\n", tag.title);			// I can just display the max lengths
			printf("Artist: %-.30s\n", tag.artist);			// and it won't keep looking until
			printf("Album: %-.30s\n", tag.album);				// it hits a null-terminator
			printf("Year: %-.4s\n", tag.year);					// attached to it, and such.
			if (tag.track >= 0 )								// so the year won't have the comment
				printf("Track: %-3d\n", tag.track);					
			else {
				printf("Track: \n");
			}
			printf("Comment: %-.28s\n", tag.comment);
		}
		else if (argc > 2) {
			// if we're here then we want to overwrite or create a new tag
			
			if (no_tag_found) {
				strncpy(tag.title, "", 30);
				strncpy(tag.artist, "", 30);
				strncpy(tag.album, "", 30);
				strncpy(tag.year, "", 4);
				strncpy(tag.comment, "", 28);
			}


			for (i = 2; i < argc; i += 2) {		// increment by 2 for field and value

				strcpy(field_name, argv[i]);								// read in the field name

				if (strcmp(field_name, "-title") == 0) {		// check if it's "-title"
					strncpy(tag.title, argv[i+1], 30);			// then read in 30 bytes
				}
				else if (strcmp(field_name, "-artist") == 0) {
					strncpy(tag.artist, argv[i+1], 30);			// then read in 30 bytes
				}
				else if (strcmp(field_name, "-album") == 0) {
					strncpy(tag.album, argv[i+1], 30);			// then read in 30 bytes
				}
				else if (strcmp(field_name, "-track") == 0) {
					strncpy(value_string, argv[i+1], 3);		// then read in 3 bytes (digits)
					if (atoi(value_string) >= 0 )
						tag.track = atoi(value_string);					// and convert the digits to an int
				}
				else if (strcmp(field_name, "-year") == 0) {
					strncpy(tag.year, argv[i+1], 4);			// then read in 4 bytes
				}
				else if (strcmp(field_name, "-comment") == 0) {
					strncpy(tag.comment, argv[i+1], 28);			// then read in 28 bytes
				}

			}	// end for loop
			if (no_tag_found) {
				fseek(f, 0, SEEK_END);
			}
			else {
				// there was a tag, we just have to overwrite in the correct spot
				if (found_top) {								// if we found it at the beginning
					fseek(f, 0, SEEK_SET);				// then go to the beginning
				}
				else {																	// otherwise we found it at the end
					fseek(f, -sizeof(tag), SEEK_END);			// so go back 128 from the end
				}
			}
			fwrite(&tag, sizeof(tag), 1, f);	// then write at that location

			// display an appropriate message
			if (no_tag_found) {
				printf("Created a new tag and appended it to the end!\n");
			}
			else {
				printf("Succesfully changed tag\n");
			}
		}	// end argc > 2

		fclose(f);					// close the file that we opened
	}	// end f != NULL

	return 0;
}
