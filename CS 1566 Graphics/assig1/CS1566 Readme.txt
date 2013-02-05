/**************************************
FILE: CS1566 Readme.txt
AUTHOR: Zach Sadler
EMAIL: zps6@pitt.edu
PLATFORM: macosx
HOMEWORK: 1
**************************************/

Known bugs (if any): None

Extra credit (describe what you did, if any):
	1. 'Throwing' objects up, down, left, or right before releasing the mouse button will result in the shapes having initial velocity (x, y, or both).
	2. Pressing the 'c' key will clear the screen of shapes.
	3. Pressing the 't' key toggles the ability to have the current shape follow the mouse cursor.
		- You can see the shape you are going to drop before clicking the mouse
	4. Pressing the 'i,j,k,l' buttons adjust the width and height of the current shape (rectangle or circle).
		- 'i' increases the height (or radius)
		- 'j' decreases the width (or radius)
		- 'k' decreases the height (or radius)
		- 'l' increases the width (or radius)
		- The width/height are stored seperately for circles and radius, and will affect all future shapes of that type.
	5. Pressing the 'e' key will 'explode' the shapes, setting them off with random x and y velocity.
		- This could have very little effect or a large effect, and pressing 'e' multiple times quickly can be fun.
	6. Pressing the 's' key will turn on the 'strobe' effect.
		- From that point on, all shapes which have already been placed will begin getting darker and darker until they 'pop' back to full brightness.
		- In addition, shapes placed from then on will begin their darkening stage as soon as they're placed.
		- Because of this, hitting 's' and then placing multiple shapes can produce a cool effect of shapes 'popping' in and out of brightness (it's cool).

Comments:  
I made a few design choices that I'll highlight here so you don't consider them bugs:
	- I chose to make shapes be created on mouse release, not mouse click, to make it easier to throw shapes.
	- Rectangles and circles bounce at a different rate. I have the rectangles deaccelerate more when they hit the ground because it looks better in my eyes to have them be less 'bouncy' then the round balls.
	- Reducing the width or height has no effect on the bounciness, although there is an apparent visual effect (since the shapes are then smaller and appear to go higher, or bigger and seem to bounce less).
	- 'Throwing' shapes to the left and right has more of an effect than up or down.
	- Objects do not deaccelerate in the x direction until they hit a wall, or are motionless in the y direction (because of this, shapes tend to clump up towards the left or right wall after many explosions).
	- At large radii, the un-roundedness of circles is more apparent. I chose a smaller amount of lines to make my circle (60 v 360) and this is a consequence.
	- Lastly, clear the screen, turn on strobe, make some shapes of different size, then explode a few times to watch a pretty neat screensaver-type image. Thanks!