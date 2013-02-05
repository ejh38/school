############################
# Zach Sadler
# zps6@pitt.edu
# Final version of Project 1
# See README.txt for details,
# or read through the comments.
# A WordSoup game, including
# hints, guessing, and giving up.
############################

.data
	# messages displayed throughout execution
	welcome:		.asciiz "Welcome to WordSoup!\n"
	thinking:		.asciiz "\nI am thinking of a word."
	yes:			.asciiz "\n\nYes! "
	no:				.asciiz "\n\nNo! "
	word_is:		.asciiz "The word is"
	round_score:	.asciiz ". Round score is "
	guess_letter:	.asciiz ".\nGuess a letter? \n(a-z to guess a letter, ! to guess the word, ? for free letter, . to give up)\n"
	won_round:		.asciiz "You won the round!"
	lost_round:		.asciiz "You lost the round!"
	final_guess:	.asciiz " Your final guess was:\n"
	correct_word:	.asciiz "\nCorrect word was:\n"
	rnd_score_was:	.asciiz "\nYour round score was: "
	game_tally:		.asciiz ". The game tally is: "
	play_again:		.asciiz ".\nDo you want to play again (y/n)?\n"
	final_tally:	.asciiz "\nYour final game tally is "
	goodbye:		.asciiz ". Goodbye!"
	space:			.asciiz " "
	newline:		.asciiz "\n"
	forfeit:		.asciiz "\nYou give up on the current word. Your round score is now 0."
	free:			.asciiz "\n\nHere is a free letter. You have "
	free_2:			.asciiz " hints remaining.\n\n"
	no_free:		.asciiz "\nSorry! You have no more free letters.\n"
	guess:			.asciiz "\nGuess the word. If you're right- double the round score,\nif not, you lose double the round score.\n"
	guess_is_wrong:	.asciiz	"\n\nSorry, that guess is wrong.\n"
	guess_is_right:	.asciiz "\n\nGreat guess! You are correct!\n"
	
	# words that will be guessed
	word0:			.asciiz "computer"
	word1:			.asciiz "squid"
	word2:			.asciiz	"gym"
	word3:			.asciiz "puzzle"
	word4:			.asciiz "lightning"
	word5:			.asciiz "trophy"
	word6:			.asciiz "kraken"
	word7:			.asciiz "witch"
	word8:			.asciiz "knife"
	word9:			.asciiz "fork"
	
	# used for the " _" version of the word
	.align 1
	word_replaced:	.space 32
	
	# lookup table of addresses
	.align 2
	word_tbl:		.word word0, word1, word2, word3, word4, word5, word6, word7, word8, word9
	
.text
	la			$a0, welcome
  	jal			print
 	
 # setting up the RNG 	
  	li			$v0, 30				
  syscall							# get system time
	move		$a1, $a0			# move it so it can be used as argument
	li			$a0, 1				# 1 is the i.d. for the rng seed
	li			$v0, 40				
  syscall							# set the seed with that time				
 # finished setting up RNG

first_time:
	lw			$s2, word_tbl		# load 'computer' as word
	move		$a0, $s2
	li			$s0, 0				# set the tally score to 0
	j			word_picked			# skip picking a random word
	
outer_loop:		# main loop that asks if they want to keep playing
 	
 	jal			pick_rand_word		# returns the address of the word to $a0,
 	move		$s2, $a0			# save the word's address to $s2
word_picked: 	
 	li			$s4, 3				# reset the number of free letters
 	
 	jal			get_length			# returns length to $a0
 	move		$s1, $a0			# reset the round score to word's length  	
 	move		$a1, $a0			# move length to $a1 for the replace_word call
 	move		$a0, $s2			# set $a0 to the current word address

  	jal			replace_word		# returns the " _" version to $a2
  	move		$s3, $a2			# store this version to $s3
  	la			$a0, thinking
  	jal			print
game_loop:  	
  	# display a big block of text, including the " _" version
  	jal			check_win
  	beq			$s1, $0, round_lost
  	
  	la			$a0, word_is
  	jal			print
  	move		$a0, $s3
  	jal			print
  	la			$a0, round_score
  	jal			print
  	li			$v0, 1
  	move		$a0, $s1
  syscall
  	la			$a0, guess_letter
  	jal			print
  	
  	li			$v0, 12
  syscall							# read a character to $v0
  	
  	# three special cases to check
  	beq			$v0, 0x21, guess_word			# !
  	beq			$v0, 0x3F, free_letter			# ?
  	beq			$v0, 0x2E, forfeit_round		# .
  	
  	jal			check_guess			# check their guess of a letter
  	
  	beq			$s1, $0, round_lost
  	
	j game_loop  
	
		 	 
 #------------------------------#
 #-----Start of beq Labels------#
 #------------------------------#
 
#------Start of forfeit_round----# 
forfeit_round:
	la			$a0, forfeit		# tell them they gave up
	jal			print
	li			$s1, 0				# set round score to zero
	j			round_over
#-----End of forfeit_round-------# 
 
#-----Start of free_letter-------# 
free_letter:
	beq			$s4, $0, have_none	# if they have none, jump
	
	addi		$s4, $s4, -1		# decrement free letters remaining
	addi		$s1, $s1, -1		# decrement round score
	la			$a0, free
	jal			print			# tell them how many they have
	li			$v0, 1
	move		$a0, $s4
  syscall	
	la			$a0, free_2		# left
	jal			print
	
	jal			add_free_letter
	
	j			game_loop
	
have_none:	
	la			$a0, no_free		# tell them they're out
	jal			print
	j			game_loop
 
#-------End of free_letter-------#  


#---------Start of round_over----# 
round_won:
	la			$a0, won_round
	jal			print
 	j			round_over
 	
round_lost: 
 	la			$a0, lost_round
 	jal			print
 	j			round_over
 
 round_over:
 	# large chunk of output to display all their stats
 	la			$a0, correct_word	# 'correct word was'
 	jal			print
 	move		$a0, $s2			# the actual correct word
 	jal			print
 	la			$a0, rnd_score_was	# 'your round score was'
  	jal			print
 	li			$v0, 1
 	move		$a0, $s1
  syscall							# print the round score
  	la			$a0, game_tally		# 'total score is'
  	jal			print
  	
  	add			$s0, $s1, $s0		# add round score to total score
  	
  	li			$v0, 1
  	move		$a0, $s0
  syscall							# print total score
  	la			$a0, play_again		# 'want to play again?'
  	jal			print
  
 	# see if they want to play again
 	li			$v0, 12
  syscall							# their character is in $v0
  	move		$a1, $v0			# move the character to $a1 to be compared to later
  	la			$a0, newline		# so we can print this newline
  	jal			print
  	
  	li			$a0, 0x79			# value for 'y'
	beq			$a0, $a1, outer_loop
	
	# if you're here, you don't want to play again
	j			exit
#---------End of round_over-------#


#-------Start of guess_word-------#
guess_word:
	la			$a0, guess
	jal			print

	move		$a0, $s2
	jal			get_length			# now the length is in $a0
	move		$t0, $a0			# move it to $t0 so it's saved
	
	addi		$a1, $t0, 1			# move it to $a1 (and +1) for the read-in-length argument of the syscall
	li			$v0, 8
	la			$a0, word_replaced	# we'll reuse this space since the round is over
  syscall							# take in their string

  	move		$a1, $s2			# move the current word address to a1
guess_loop:
	beq			$t0, $0, guess_right
	lb			$t1, 0($a1)			# load a byte of the correct word
	lb			$t2, 0($a0)			# load a byte of their string
	bne			$t1, $t2, guess_wrong
	
	addi		$a0, $a0, 1			# move one byte down the address
	addi		$a1, $a1, 1			# move one byte down the address
	addi		$t0, $t0, -1		# decrement the counter
	j			guess_loop
	
guess_wrong:
	la			$a0, guess_is_wrong
	jal			print
	sll			$s1, $s1, 1			# multiply round score by 2
	neg			$s1, $s1			# then negate
	li			$t0, 0				# $t0 = 0 means guess is wrong
	j			guess_exit
	
guess_right:
	la			$a0, guess_is_right
	jal			print
	sll			$s1, $s1, 1			# multiply round score by 2
	li			$t0, 1				# $t0 = 1 means guess is right
	
guess_exit:
	beq			$t0, 0, round_lost
	beq			$t0, 1, round_won

#--------End of guess_word--------#



 #--------------------------------#
 #-------End of beq Labels--------#
 #--------------------------------#


 #--------------------------------#
 #-------Start of Functions-------#
 #--------------------------------#

#------Start of pick_rand_word-------#
pick_rand_word:		# no arguments, return: address of random word in $a0
	# preamble
	addi		$sp, $sp, -12
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)
	
	li			$v0, 42				# random number within range
	li			$a0, 1				# set the i.d. to 1
	li			$a1, 10
  syscall							# generates a random int 0-9	
  
  	move		$t0, $a0			# move it to $t0
  	sll			$t0, $t0, 2			# multiply by 4 to make it into a word offset
	la			$t1, word_tbl		# load base address of data table
	add			$t1, $t1, $t0		# add offset to base
	
	# postamble
	lw			$a0, ($t1)			# word's address in $a0 for return
	
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
	
	jr			$ra
#--------End of pick_rand_word--------#

#--------Start of get_length---------#
get_length:		# argument: $a0 as address, return: length in $a0
	# preamble
	addi		$sp, $sp, -12		# make room for the three variables used
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)			# store the variables we'll be using

	li			$t0, 0				# $t0 is the running counter to find the length
get_length_loop:
	lb			$t1, ($a0)			# loads one charactar from the current string index
	addi		$a0, $a0, 1			# move to the next character
	addi		$t0, $t0, 1			# increment the counter
	bne			$t1, $0, get_length_loop	# check if the byte is a NULL charactar (0)
	
	# postamble
	subi		$t0, $t0, 1			# have to correct the length, since it's one higher than it should be
	move		$a0, $t0			# return the argument as $a0

	# put the stack stuff back where it came from
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
	jr			$ra					# go back to the caller
#--------End of get_length-------#


#--------Start of replace_word---------#                
replace_word:	#arguments: $a0 is address of word, $a1 is word length,
				# returns: $a2, adress of word with all " _"
	# preamble
	addi		$sp, $sp, -12
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)
	
	la			$t0, word_replaced
	li			$t1, 0x5F20			# load the hex value for " _"
replace_loop:
	sh			$t1, ($t0)			# store " _"
	addi		$t0, $t0, 2			# add 2 bytes to the address
	addi		$a1, $a1, -1		# decrement the lengthLeft
	bne			$a1, $0, replace_loop		# if lengthLeft is > 0, keep looping
	
	# done replacing letters
	
	# now need to replace any extra " _" leftover from previous rounds
extra_letters:
	lh			$t1, ($t0)
	beq			$t1, $0, no_more_extra	
	sh			$0, ($t0)
	addi		$t0, $t0, 2
	j			extra_letters		
	
no_more_extra:						# there are now no leftover " _"
	la			$a2, word_replaced	# for the return value
	move		$a0, $a2
	jal			add_stars			# add the stars
	# postamble      
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
	
	jr			$ra
#-------End of replace_word------#
                                
 
#------Start of add_stars------#                                                                
add_stars:		# argument: $a0 is address to add stars to, returns $a1- the starred version 
   				# assumption: $a0 is the " _" version                                 
	# preamble
	addi		$sp, $sp, -20
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$a0, 12($sp)
	sw			$ra, 16($sp)
	
	# first, need to pick a random number [0, n/2]
	# get the length of the current word
	move		$t0, $a0			# move the address to $t0 so we can alter it
	move		$a0, $s2			# set up argument for get_length
	jal			get_length			# now the length is in $a0
	move		$t2, $a0			# store the length (n) in $t2
	srl			$a1, $t2, 1			# $a1 has n/2
	addi		$a1, $a1, 1			# add one so we can pick up the upper bound itself
	# next, get the random number
	li			$v0, 42
	li			$a0, 1				# set seed i.d. to 1
  syscall							# now $a0 has a random number in [0, n/2]
	# done
	move		$t1, $a0			# this will be our counter
	li			$v0, 42				# only need to load
	move		$a1, $t2			# now $a1 has the length (n) from $t2
	li			$a0, 1				# these values once
star_loop:
	# now, need to pick a random number each time, from [0, $t2]
	beq			$t1, $0, star_exit	# if counter is zero, get out
  syscall							# now $a0 has random number from [0, n]
  	sll			$a0, $a0, 1			# multiply it by 2 to adjust for the halfword (_ <- adds one)
  	
  	move		$t2, $t0			# make $t2 the start of the " _" address
  	add			$t2, $t2, $a0		# add the offset
  	li			$a0, 0x2A20			# load " *"
  	sh			$a0, ($t2)			# store it at the right spot
  	
  	addi		$t1, $t1, -1		# decrement the counter
  	j			star_loop
	
star_exit:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    # postamble                   
    la			$a2, word_replaced  
    
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$a0, 12($sp)
	lw			$ra, 16($sp)          
	addi		$sp, $sp, 20         
	
	jr			$ra
#-------End of add_stars------#	  

#-------Start of add_free_letter------#	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
 add_free_letter:					# void function, needs no input, has no output
 # preamble
 	addi		$sp, $sp, -20
 	sw			$t0, 0($sp)
 	sw			$t1, 4($sp)
 	sw			$t2, 8($sp)
 	sw			$t3, 12($sp)
 	sw			$ra, 16($sp)
 
 	move		$a0, $s2
 	jal			get_length
 	move		$t0, $a0			# $t0 has the length
 	la			$a0, word_replaced	# $a0 will be the address we look at
 	addi		$a0, $a0, 1			# add one to the address first to skip " "
	li			$t1, 0x0			# this will be the register we load the byte into
	li			$t2, 0x5F			# load value of "_"
  	li			$t3, 0				# make sure $t3 is not already 0x5F
  add_free_letter_loop:
 	beq			$t0, $t3, add_free_letter_exit	# if working length = 0, exit		
 	lb			$t1, 0($a0)			# load character
 	beq			$t1, $t2, found_spot 			# if character = "_", we found it
 	
 	addi		$t3, $t3, 1			# increment length counter
 	addi		$a0, $a0, 2			# add 2 bytes to the address
 	j			add_free_letter_loop

found_spot:
	# assuming the spot is $a0
	add			$t0, $t3, $s2		# move down the actual word
	lb			$t1, 0($t0)
	sb			$t1, 0($a0)

 add_free_letter_exit:
  # postamble
  	
 	lw			$t0, 0($sp)
 	lw			$t1, 4($sp)
 	lw			$t2, 8($sp)
 	lw			$t3, 12($sp)
 	lw			$ra, 16($sp)
  	addi		$sp, $sp, 20
  	
 	jr			$ra
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
#-------End of add_free_letter--------#                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
#--------Start of print-------#                                                                                                                                
print:			# argument: $a0 is address to print, returns: void, just does syscall 4
				# leaf function, no pre or postamble
	li			$v0, 4
  syscall
  	jr			$ra
#------End of print----------#


#-----Start of check_guess----#			
check_guess:							# argument: $v0 has the guess
# preamble
	addi		$sp, $sp, -24
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$t3, 12($sp)
	sw			$t4, 16($sp)
	sw			$ra, 20($sp)


	move		$t0, $v0				# move the guess to $t0
	move		$a0, $s2				# load the current word
	jal			get_length				# now length is in $a0
	move		$t1, $a0				# now length is in $t1
	move		$a0, $s2				# $a0 has the address of the word
	li			$t2, 0					# $t2 will be used for position in word
	li			$t4, 0					# set flag to false (guess is wrong)
check_loop:
	beq			$t1, $t2, check_exit	# if currPosition = length, exit ** only way to get out
	lb			$t3, 0($a0)				# load the next byte
	beq			$t3, $v0, check_success	# if byte = their guess, we're good


	addi		$a0, $a0, 1				# move a byte down the address
	addi		$t2, $t2, 1				# increment currPosition
	j			check_loop
	
check_success:
	move		$a2, $t2				# store value of $t2
	move		$a3, $a0				# store value of $a0
	li			$t4, 1					# flag to let us know they got it right
	sll			$t2, $t2, 1				# multiply the position by 2 (since " _"
	addi		$t2, $t2, 1				# then add one to get to the "_"
	add			$a0, $t2, $s3			# add that offset to the address of the " _" version
	lb			$t3, 0($a0)
	beq			$t3, 0x2A, check_loop_star
	sb			$v0, 0($a0)				# store their guess to the string
check_loop_star:
	move		$t2, $a2				# move back
	move		$a0, $a3				# move back
	addi		$a0, $a0, 1				# move a byte down the address
	addi		$t2, $t2, 1				# increment currPosition
	j			check_loop				# jump back in to keep looking


check_exit:
	beq			$t4, 1, good_guess		# if they're right, tell them
	beq			$t4, 0, bad_guess		# if they're wrong, tell them too
	
good_guess:
	la			$a0, yes
	jal			print
	j			check_return
bad_guess:
	la			$a0, no
	jal			print
	addi		$s1, $s1, -1
		
	
check_return:
# postamble	

	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$t3, 12($sp)
	lw			$t4, 16($sp)
	lw			$ra, 20($sp)	
	addi		$sp, $sp, 24

	jr			$ra
#------End of check_guess-----#

#------Start of check_win-----#
check_win:							# void function, no arguments or return
# preamble
	addi		$sp, $sp, -20
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$t3, 12($sp)
	sw			$ra, 16($sp)


	la			$a0, word_replaced	# get length of the " _" version
 	jal			get_length
 	move		$t0, $a0			# $t0 has the length
 	la			$a0, word_replaced	# $a0 will be the address we look at
 	addi		$a0, $a0, 1			# add one to the address first to skip " "
	li			$t1, 0x0			# this will be the register we load the byte into
	li			$t2, 0x5F			# load value of "_"
  	li			$t3, 0				# reset $t3
  	li			$v0, 1				# start out as win
check_win_loop:
 	beq			$t0, $t3, check_win_exit	# if reach the end, get out		
 	lb			$t1, 0($a0)					# load character
 	beq			$t1, $t2, no_win	 		# if character = "_", haven't won yet
 	
 	addi		$t3, $t3, 1			# increment length counter
 	addi		$a0, $a0, 2			# add 2 bytes to the address
 	j			check_win_loop

no_win:
	li			$v0, 0				# no win
check_win_exit:
	beq			$v0, 1, round_won
# postamble

	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$t3, 12($sp)
	lw			$ra, 16($sp)
	addi		$sp, $sp, 20
	
	jr			$ra
#------End of check_win-------#

 #---------------------------#  	
 #-------End Functions-------#
 #---------------------------#  	
                                                                                                                                
exit:
	la			$a0, final_tally
	jal			print
	li			$v0, 1
	move		$a0, $s0			# print final score
  syscall
	la			$a0, goodbye		# say goodbye!
	jal			print

	li			$v0, 10				# exit! all went well!
  syscall