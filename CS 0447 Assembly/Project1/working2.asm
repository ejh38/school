# Zach Sadler
# Working file for project1
# Up to this point it picks a random word,
# makes a " _" version of it,
# and displays a whole bunch of text

.data
	# messages displayed throughout execution
	welcome:		.asciiz "Welcome to WordSoup!\n"
	thinking:		.asciiz "I am thinking of a word."
	yes:			.asciiz "Yes!"
	no:				.asciiz "No!"
	word_is:		.asciiz " The word is"
	round_score:	.asciiz ". Round score is "
	guess_letter:	.asciiz ".\nGuess a letter?\n"
	won_round:		.asciiz "You won the round!"
	lost_round:		.asciiz "You lost the round!"
	final_guess:	.asciiz " Your final guess was:\n"
	correct_word:	.asciiz "\nCorrect word was:\n"
	rnd_score_was:	.asciiz "Your round score was: "
	game_tally:		.asciiz ". The game tally is: "
	play_again:		.asciiz ".\nDo you want to play again (y/n)?\n"
	final_tally:	.asciiz "\nYour final game tally is "
	goodbye:		.asciiz ". Goodbye!"
	space:			.asciiz " "
	newline:		.asciiz "\n"
	
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
	
	# used for the "_ " version of the word
	.align 1
	word_replaced:	.space 25
	
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
 	jal			print
word_picked: 	
	li			$s1, 5				# reset the round score to 5  	
 	
 	jal			get_length			# which is the argument for this, which returns length to $a0
 	move		$a1, $a0			# move length to $a1 for the replace_word call
 	move		$a0, $s2			# set $a0 to the current word address

  	jal			replace_word		# returns the "_ " version to $a2
  	move		$s3, $a2			# store this version to $s3
  	
  	la			$a0, thinking
  	jal			print
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
  	
  	j			exit
 
 
 
 
 
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
	
	# done replacing letter
	la			$t0, word_replaced
	move		$a2, $t0
	
	# postamble      
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
	
	jr			$ra
                                
print:			# argument: $a0 is address to print, returns: void, just does syscall 4
				# leaf function, no pre or postamble
	li			$v0, 4
  syscall
  	jr			$ra
                                                                                                                                
exit:
	li			$v0, 10
  syscall
  
