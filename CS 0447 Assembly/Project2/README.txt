#####################################################################################################
# Zach Sadler
# zps6@pitt.edu
# README for Project 2
# Table of Contents:
# Functions, Registers, Extra Credit, 
# Explanation, and Buglist
# (NOTE: made to be displayed with a window size such that this whole line is displayed with no wrap)
#####################################################################################################

------------------------------------Start of Functions------------------------------------------------

FUNCTIONS WITH NO ARGUMENTS OR RETURN VALUES:

	ensure_direction:	# this makes sure that the direction registers agree
	display_game_over:	# this simply displays the game over messages
	init_queue:		# this initializes the queue with the correct pointers
	init_snake:		# this initializes snake_x with 0 - 7
				# and snake_y with 8 31's
	init_walls:		# this is simply a void function to display 25 random walls
	init_frogs:		# this is simply a void function to display 32 random frogs	

OTHER FUNCTIONS:
	get_rand_int:		# arguments: $a1 has range upper value (exclusive)
				# returns: $v0 has the random int
	insert:			# arguments: $a0 is x coord, $a1 is y coord of the point to insert
				# returns: none
				# note: inserts the coordinates into the queue at the logical end of the queue
	remove:			# arguments: none
				# returns: $v0 has x coord, $v1 has y coord of the front entry
				# note: removes from the logical front of the queue
	peek:			# arguments: none
				# returns: $v0 has x coord, $v1 has y coord of the end entry
				# note: returns, without removing, the (x,y) coord of the end entry
	calculate_end:		# arguments: none
				# returns: $v0 ($v1) has the address of the logical end of the queue x (y)
				# note: this is a private function which is called to 
				# 	help with wrap around, peeking, and inserting
	getLED:			# arguments: $a0 is x, $a1 is y (both 0-63)
				# returns: $v0 has the color (0 black, 1 red, 2 orange, 3 green)
	setLED:			# arguments: $a0 is x, $a1, is y (both 0-63),
				#	     $a2 color (0 black, 1 red, 2 orange, 3 green)
				# returns: none
------------------------------------End of Functions------------------------------------------------

------------------------------------Start of Registers----------------------------------------------

SAVED REGISTERS:
	$s0 - Current length of snake, which also doubles as game score
	$s1 - Used to store x direction (1 means right, -1 means left, 0 means neither)
	$s2 - Used to store y direction (1 means down, -1 means up, 0 means neither)
	$s3 - Initial system time, used to calculate when to step in the current direction
	$s4 - Holds the difference between the initial system time and the current system time
	$s5 - Holds the very initial system time call, to calculate total time played in game
	$s6 - Used to calculate whether or not the snake is stuck when hitting walls

All other registers are typically saved and reloaded during function calls, although occasionally trashed.

------------------------------------End of Registers------------------------------------------------

------------------------------------Start of Extra Credit--------------------------------------------

	I was able to get the first extra credit, the walls, completely finished. I actually was able to successfully make the frogs move, but I wasn't happy with how much it slowed down the program execution (and animation) to do so, so I chose not to implement that part.
	Because of how I chose to implement direction, I am able to very simply move at a right angle (see explanation for more details).
	
------------------------------------End of Extra Credit--------------------------------------------

------------------------------------Start of Explanation--------------------------------------------

Explanation:	
	I feel that my program is extremely thoroughly commented, and formatted very consistently, so it should be easy to read through and figure out how it works, however I will explain the idea all the same.

	My snake is stored logically as a queue, but physically as snake_x and snake_y, two 64-word arrays that hold the x and y coordinates of the segment respectively. There is a pointer to the logical front of each queue (for x and y), but no pointer to the logical end (instead I use a function calculate_end which will wrap around to the physical front of the data if needed).
	I chose to abstract as much of the program away into function calls as I could. For example, to initially display all of the frogs, walls, initialize the snake, and initialize the queue, I simply make four function calls. Displaying the frogs is a simple loop which generates two random numbers [0,63] (which can be done by calling get_rand_int), and calls getLED for that position to see if it is blank or not. If it is not blank, I loop back without incrementing the counter, otherwise I use setLED to turn that position green. Initializing the walls is done in exactly the same way, and I even considered turning init_walls into a function with an argument for color so that both frogs and walls could be turned on with the same code.
	Initializing the queue is simply aligning the two pointers. After this point, the queue can be used to insert, remove, and peek at will.
	The last piece of initialization is taking the system time and saving it for later.
	
	Now for the actual game loop:
	First, I do a polling loop until a keypress is pushed. During this loop I continuously call for the system time and check to see if the current time - initial time >= 200. If this is the case, then I go to time_up. Assuming that a key is pressed, I store it temporarily and then see if 200ms has elapsed. If it hasn't, then I just go back and keep polling until the time has finally passed.
	One time_up is reached, I peek at the current coordinates (for later), check to see which button was pressed, and if none was pressed then just go to 'step'- which simply keeps moving in the current direction. Depending on which button was pressed, I adjust my two direction registers.
	The way I implemented directions is as follows:
	$s0 holds the x direction- with 1 being right, -1 being left, and 0 being neither
	$s1 holds the y direction- with 1 being down, -1 being up, and 0 being neither
	At the end of each step, I simply add $s0 to the x coordinate and $s1 to the y coordinate. I feel that this is a very efficient (and cool) way to implement this, especially since it makes handling walls very easy. Each time I move in a direction, I check to make sure that I haven't hit the end of the physical LED wall boundary, in which case I wrap around.
	By hit_done, $a0 and $a1 have the coordinates of the next space I would like to place the Snake. Now I check that LED. If I get green, then I skip removing the tail so that the snake grows. If I get yellow then I've eaten myself and I go to game_over. If I get red, then I've hit a wall.
	If I hit a wall, I simply switch the x and y directions, then negate each. The effect is awesome. (Example: If I was going right previously then I would have $s0 = 1, $s1 = 0. After switching and negating, I have $s0 = 0, $s1 = -1, which is going up.) Then I check to make sure that the next position in this direction is not another wall or the snake, in which case I try to go in the opposite direction. If I fail in both directions then I am stuck, and display a message and end the game accordingly. Otherwise, I go back to move_done and adjust accordingly.
	The very last things I do before returning to the top of the loop are reinitializing values: I ensure that the direction I'm going matches the $t4 temporary value for that keypress, I reinitialize the 'initial' clock for calculating 200ms, and then I return back to polling for keypresses.

------------------------------------End of Explanation--------------------------------------------	

------------------------------------Start of Buglist----------------------------------------------

Buglist:
	I tested very extensively and really think I've solved all the bugs I've found. I truly think my program is bug free.

------------------------------------End of Buglist------------------------------------------------