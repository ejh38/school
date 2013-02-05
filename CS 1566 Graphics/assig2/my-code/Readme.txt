/**************************************
FILE: Readme.txt
AUTHOR: Zach Sadler
EMAIL: zps6@pitt.edu
PLATFORM: macosx
HOMEWORK: 2
**************************************/

Known bugs (if any): I believe my vertex normals are off. On the torus especially, it seems they aren't quite going where they should be.

Extra credit (describe what you did, if any):
	0. I added a top to the cone. It's not perfect, but it works.
	1. Pushing '1' turns on 'Slowmo' mode. 
		-	It's a pretty funny hack- I just call glutSwapBuffers() a few times to slow down the computer as it's drawing and show the current progress.
		- It works a lot better when you're drawing a more complex shape (greater rs and vs values).
	2. Pushing '2' changes the shape sizes to my preferred default sizes.
	3. Pushing '3' toggles the shape rotating in the x direction.
	4. Pushing '4' toggles the shape rotating in the y direction.
	5. Pushing '5' toggles the 'play_rs' feature, which continuously iterates rs from 3-50.
	6. Pushing '6' toggles the 'play_vs' feature, which continuously iterates vs from 3-50.
	7. Pushing '7' adjusts the timer_speed.
		- The timer_speed controls 3, 4, 5, and 6. 

Comments:  
	- I'm sorry I didn't use header files (again). You mentioned this is a problem with visual studio but I still haven't encountered any issues using g++. I promise I'll ask for help with this before submitting assignment 3.
	- Wow, this was a lot harder than assignment 1.
	- Note that you can combine the toggles above, so that you can rotate in both x and y direction (and also be playing with rs and vs, and potentially also in Slowmo).
		- Combining all of these effects, and having a physically larger shape (like the ones when you push '2') will definitely put a toll on slower systems. This is partially why I added the timer_speed, so that you can have it run at a speed you feel comfortable with.
	- The cone *is* centered at the origin, but the top of the cone is not accounted for in that centering. So if you rotate it along the x axis (like by pressing '3') it looks slightly off. Before I added the top of the cone, it was centered at the origin and appeared that way during rotations.
	- I'd reccomend pushing 2, then 's', then 'v', then 3, 4, 5, and 6, and enjoying!
	- Thanks for your help via email!