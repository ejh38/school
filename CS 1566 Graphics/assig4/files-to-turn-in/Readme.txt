/**************************************
FILE: Readme.txt
AUTHOR: Zach Sadler
EMAIL: zps6@pitt.edu
PLATFORM: macosx
HOMEWORK: 4
**************************************/

Known bugs (if any): 
	- I did not turn on normals, since I still don't think they're totally right
	- My scene draws backwards, as if the camera is on the wrong side of the z axis
	- I am not sure if I implemented the height angle correctly
	- I did not do anything with the lighting, although I've seen some other students who did and I'm pretty jealous
	- I have 'zooming' (with L/l) work exactly the same as changing the height angle (H/h), because I don't understand the difference
	- My keyboard combinations are slightly different, although this is an intended design choice.
		- I don't require use of T/t or +/-, just capital or lowercase letters. Capital is positive, lowercase is negative.
	- I had near and far clipping working perfectly fine, but after adjusting to my own camera and having everything flipped backwards, I think the clipping got screwed up.
		- You can see that I update near and far's values correctly in my_keyboard, and then re-call gluPerspective with those new values, but I think the way I have my own camera it's messed up.
		- If you replace the my_display() code with the code below it, it 'unflips' the world, yet the near and far are still slightly messed up.


Extra credit (describe what you did, if any):
	- No fun extra credit this time.
		- I know. I'm upset too. But I'm bringing it back for HW5.

Comments:  
	- Yikes.
	- I am turning this in one day late.
		- It wasn't as much the difficulty of the assignment that is causing me to be late, but other circumstances. Exams and projects due for other classes, my personal life, and Halloween.
	- The example code was very difficult to work with at first, since it's C's attempt at being object oriented. I am not a very good C/C++ coder yet, so it was difficult for me to work with my C++ classes and the C 'objects'.
	- My code is slightly jumbled and hardly commented. I would understand if you took off some points for poor code style.