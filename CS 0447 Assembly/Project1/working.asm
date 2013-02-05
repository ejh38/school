# Zach Sadler
# Working file for project1
# loops ten times through, picking a random int,
# then finding the corresponding word,
# then printing the length of that word

.data
	welcome:		.asciiz "Welcome to WordSoup!\n"
	thinking:		.asciiz "I am thinking of a word."
	yes:			.asciiz "Yes!"
	no:				.asciiz "No!"
	word_is:		.asciiz " The word is "
	round_score:	.asciiz " Round score is "
	guess_letter:	.asciiz ".\nGuess a letter.\n"
	newline:		.asciiz "\n"
	debug_2:		.asciiz " corresponding word is: "
	debug_3:		.asciiz " length: "
	
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
	
	# lookup table of addresses
	.align 2
	word_tbl:		.word word0, word1, word2, word3, word4, word5, word6, word7, word8, word9
	
.text
	li			$v0, 4
	la			$a0, welcome
  syscall
 	
 # setting up the RNG 	
  	li			$v0, 30				
  syscall							# get system time
	move		$a1, $a0			# move it so it can be used as argument
	li			$a0, 1				# 1 is the i.d. for the rng seed
	li			$v0, 40				
  syscall							# set the seed with that time				
 # finished setting up RNG
 
 	li			$s0, 10				# debugging: loops 10 times
pick_word:
	beq			$s0, $0, exit		# debug
	
	li			$v0, 42				# random number within range
	li			$a0, 1				# set the i.d. to 1
	li			$a1, 10
  syscall							# generates a random int 0-9	
  
   	li			$v0, 1
  syscall							# print the random number
  
  	move		$t0, $a0			# move it to $t0
  	sll			$t0, $t0, 2			# multiply by 4 to make it into a word offset
	la			$t1, word_tbl		# load base address of data table
	add			$t1, $t1, $t0		# add offset to base
	
	la			$a0, debug_2
	li			$v0, 4
  syscall
	lw			$a0, 0($t1)			# load the asciiz word
	li			$v0, 4				# print the word
	syscall
  
  	move		$s1, $a0			# this is a saved address of the word
  
  	la			$a0, debug_3
  	li			$v0, 4
  syscall
  
  	move		$a0, $s1
  	jal	get_length
  	
  	move		$a0, $v0
  	li			$v0, 1
  syscall	
  
    addi		$s0, $s0, -1		# debug
    j pick_word						# debug
    



get_length:		# takes $a0 as address, returns it's length in $a0
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

	move		$v0, $t0			# because, we agreed to return the length in $v0 :(

	# put the stack stuff back where it came from
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
	jr			$ra					# go back to the caller
                
exit:
	li			$v0, 10
  syscall
  
