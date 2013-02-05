/**************************************
FILE: Readme.txt
AUTHOR: Zach Sadler
EMAIL: zps6@pitt.edu
PLATFORM: macosx
HOMEWORK: 3
**************************************/

Known bugs (if any): 
	- As in the last hw, I'm not sure but my vertex normals may be off. Because I didn't receive my grade for the last hw I wasn't sure if they needed fixing or not, so I did not change them.
	- My cube and house perform as described, without errors, but I had to do a few hardcoded hacks to get them working. Who knew that relatively 'simple' shapes would be so much harder to work with than spheres and cones?

Extra credit (describe what you did, if any):
	I included a lot of the same extra credit as last hw
	0. A top to the cone.
	1. A 'slowmo' mode, activated by pressing '0'.
	2. Pushing 'd' changes the shape sizes to my preferred default sizes.

Comments:  
	- I'm sure you've been getting this a lot, but it would have been helpful to know how I did on hw2, since this was a direct sequel.
	- There were a few spots where the example code seemed to conflict with the project description:
		- The example code mentioned hooking up the '+', '-', '<', '>' buttons, as before, so I did this.
		- The example code has right-clicking toggle the render mode between wire-frame and polygon, while the description asks for right-clicking to toggle normals appearance. So I did both.
	- I included a 'stack' matrix which just gets multiplied as the transforms happen. I figured I'd use it for doing a non-uniform scaling (just invert the stack, apply it to the current matrix, then do the scaling and reapply the normal stack), but I couldn't come up with a simple and efficent way to invert 4x4 matrices. I found code online that could do the trick, but I chose not to copy code or even the idea of that code. So, as of right now my 'stack' goes unused.
	- Thanks for reading! Not as much fun/unique extra credit as the last two, but I'll try to ramp it up next time.
