####################
# Zach Sadler
# zps6@pitt.edu
# README for Project 1
# Functions, Registers, Notes, 
# Important, Explanation, and Buglist
# (NOTE: made to be displayed with a window size such that this whole line is displayed with no wrap)
####################

Functions:
	pick_rand_word:		# no arguments, return: address of random word in $a0
	get_length:			# argument: $a0 as address, return: length in $a0		
	print:				# argument: $a0 is address to print, returns: void, just does syscall 4
						# leaf function, no pre or postamble
	replace_word:		# arguments: $a0 is address of word, $a1 is word length,
						# returns: $a2, adress of word with all " _"
	add_stars:			# argument: $a0 is address to add stars to, returns $a1- the starred version 
   						# assumption: $a0 is the " _" version          
	add_free_letter:	# void function- needs no input, has no output
	check_guess:		# argument: $v0 has the guess
	check_win:			# void function, no arguments or return


Registers:
  Temporary:
	$a0 - addresses, specifically for arguments dealing with addresses
	$a1 - arguments of functions
	$t0, $t1, $t2, $t3, $t4 - various temporary arguments, used for a large variety of tasks
  Saved:
	$s0 - total score / game tally
	$s1 - round score
	$s2 - current word address
	$s3 - " _" version of the word address
	$s4 - number of free letters left


Notes:
	0x5F20 is " _"
	ASCII:		* - 2A	  ! - 21  	? - 3F	  . - 2E	A - 41	  Z - 5A  	 a - 61 	 z - 7A
	
	
Important:	I assumed that the player gets three free letters per round, not total. It would be trivial to switch this, as I would just not li $s4, 3 at the start of each round (under word_picked), and instead set $s4 to 3 a single time, when I welcome the player to WordSoup
	
	
Explanation:	
	My program is generally very well documented in the comments, but here is an overall view of the way it works.  I have my ten words stored as .asciiz strings, labeled word0-word9. There is a word table / vocabulary connected to this, with the addresses of each word. The first time through, I load 'computer' (word0) and skip ahead to the round initialization. Every other time, I pick a random word (through a function call), then continue to the initialization. 
	As part of the initialization, I prep the 'output string,' which I call the " _" version throughout my comments, and add stars to it. Both of these tasks are accomplished via function calls. In each case, I loop through the string (until I reach the end as specified by the get_length function) and store either a halfword (" _") or byte ("*") when appropriate. Once the " _" version is readied with a random number of stars, I go to the game loop.
	In the actual game loop I display some text (using my very simple print function), take in a character from the user, and check what they typed. If it's one of the special cases, I go to the appropriate label, which is not strictly a function (or if anything, a void function). If it's not a special case, then I treat it as a guess and call a function to check if it is a correct guess.
	To check if their guess is correct, I keep their guess loaded into $v0 and then walk through the correct word string, comparing at each byte. If the bytes match then I set a flag so I know to display 'Yes!', then store their guess to the current position of the working string (which is twice the current position, plus one, plus the address of word_replaced). If the bytes match but there is a * in that spot, then I skip the storing of the byte and keep walking through. In this way, words like "banana" would be covered, even if one of the 'a's or 'n's were *'ed, as the loop continues until it reaches the end of the string each time, regardless of if there is a match or not. 
	The game_loop itself is very short, as most of the real content of the program is done in the functions and labels. I feel this is very good style, especially since I 'clean up' after myself by using the $sp and having preambles and postambles for each functon.
	A few other notes about my code: I try to use as few registers as possible, often overwriting registers whose values are no longer important/will be immediately reset. To improve readability and save a few lines of code, I created a print function which simply does li $v0, 4, syscall, jr $ra. Although this may be slightly inefficient, I find it tremendously useful for making the code easier to understand.
	
	
Buglist:
	Using the 'Clear' button while at an input prompt can cause the program to infinite loop.
		- I think this is more of a problem with MIPS in general and not a true bug, since the syscall is probably being interrupted by the 'Clear' button press.
	When guessing, the user's input is taken after they enter n characters, where n is the length of the word. Entering n+1 characters will likely exit the program.
		- This is also not truly a bug in my eyes, but if the user types an extra character (ex: 's-q-u-i-d' for a 4 character word) then the extra character (in the squid case, the 'd') will be taken as input for the 'play again?' prompt, oftentimes ending the program prematurely. This bug can be avoided as long as the user types slowly and enters valid input.
	I found no other bugs while testing. My program handles all of the special cases I can think of.	