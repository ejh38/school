/*
	BASS simple console player
	Copyright (c) 1999-2012 Un4seen Developments Ltd.
*/

#include <stdlib.h>
#include <stdio.h>
#include "bass.h"

#include <sys/time.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

#define Sleep(x) usleep(x*1000)

int main(int argc, char **argv)
{
	DWORD chan[NUM_NOZZLES];
	DWORD act;
	
	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
		printf("An incorrect version of BASS was loaded");
		return;
	}

	if (argc!=2) {
		printf("\tusage: contest <file>\n");
		return;
	}

	// setup output - default device
	if (!BASS_Init(-1,44100,0,0,NULL))
		exit(0);

	// try streaming the file/url
	chan = BASS_StreamCreateFile(FALSE, argv[1], 0, 0, BASS_SAMPLE_LOOP);

	BASS_ChannelPlay(chan,FALSE);

	while (act = BASS_ChannelIsActive(chan)) {

		Sleep(50);
	}

	BASS_Free();

	return 0;
}
