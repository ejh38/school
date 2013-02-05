################################
# Zach Sadler
# zps6@pitt.edu
# Lab 5, part 1
# Add 3 stars to a string input by the user
# I realize that my two functions are both leaf
# functions and do not need to use the stack,
# I use it anyways as practice
################################

.data
	input_str:		.space 64
	enter_str:		.asciiz "Enter your string?\n"
	output_str:		.asciiz "Here is your output:\n"
.text
	# setting up the RNG 	
  	li			$v0, 30				
  syscall							# get system time
	move		$a1, $a0			# move it so it can be used as argument
	li			$a0, 1				# 1 is the i.d. for the rng seed
	li			$v0, 40				
  syscall							# set the seed with that time				
    # finished setting up RNG

	li				$v0, 4
	la				$a0, enter_str
  syscall									# display 'enter your string'
    li				$v0, 8
    la				$a0, input_str
    li				$a1, 64	
  syscall									# take in their input (it's in $a0)
 	
    jal				get_length				# returns length of $a0 to $v0
  	move			$a0, $v0				# now the length is in $a0
  	
  	jal				add_stars				# address of starred version is in $v0
  	move			$a2, $v0				# store it to $a2
  
  	li				$v0, 4
  	la				$a0, output_str
  syscall									# display "her is your output"

   	move			$a0, $a2				# move it back from it's stored positions
  	li				$v0, 4
  syscall									# show their starred string

	j exit
  
  
#--------Start of get_length---------#
get_length:		# argument: $a0 as address, return: length in $v0
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
	move		$v0, $t0			# return the argument as $v0

	# put the stack stuff back where it came from
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
	jr			$ra					# go back to the caller
#--------End of get_length-------#


#------Start of add_stars------#                                                                
add_stars:		# argument: $a0 is the length, returns $v0- the address of the starred string                    
	# preamble
	addi		$sp, $sp, -20
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$t3, 12($sp)
	sw			$ra, 16($sp)
	
	# initialize stuff before the loop
	move		$a1, $a0			# length is now the upper bound of the range
	li			$t2, 3				# this will be our counter
	li			$v0, 42				# this is for generating a random number in range
	li			$a0, 1				# seed for the rng
	li			$t1, 0x2A			# load "*"
	addi		$a1, $a1, -1		# subtract 1 from $a1 to get proper range
star_loop:
	# now, need to pick a random number each time, from [0, n-1]
	beq			$t2, $0, star_exit	# if counter is zero, get out
  syscall							# now $a0 has random number from [0, n]
  	
  	la			$t0, input_str		# make $t0 the start of the address
  	add			$t0, $t0, $a0		# add the offset
  	lb			$t3, ($t0)			# load char that's there
  	beq			$t3, $t1, star_loop	# if it's already a star, loop again
  	sb			$t1, 0($t0)			# store it at the right spot
  	
  	addi		$t2, $t2, -1		# decrement the counter
  	j			star_loop
	
star_exit:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    # postamble                   
    la			$v0, input_str  
    
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$t3, 12($sp)
	lw			$ra, 16($sp)          
	addi		$sp, $sp, 20      
	
	jr			$ra
#-------End of add_stars------#	  

exit:
	li			$v0, 10
  syscall