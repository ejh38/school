###############################
# Zach Sadler
# zps6@pitt.edu
# Second working progress of 
# Project 2.
# This is trying to get lab8
# working on a 64x64 display,
# with 30 green LEDs
###############################
.data
init_x:			.word	32
init_y:			.word	32
init_color:		.word	1

green_x:		.word	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
green_y:		.word	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
green_color:	.word	3

.text

	li			$s2, 0				# initialize the score to zero

	lw			$a0, init_x			# place the red LED first
	lw			$a1, init_y
	lw			$a2, init_color
	jal			setLED
	
	move		$s0, $a0			# store the x, y
	move		$s1, $a1			# positions for later
	
	# setting up the RNG 	
  	li			$v0, 30				
  syscall							# get system time
	move		$a1, $a0			# move it so it can be used as argument
	li			$a0, 1				# 1 is the i.d. for the rng seed
	li			$v0, 40				
  syscall							# set the seed with that time				
 	# finished setting up RNG
 	
 	# get random numbers for the 32 frogs
	# note: this stores the x positions from last -> first
	li			$t0, 32				# set the counter to 5
init_frogs_loop:
	beq			$t0, 0, init_frogs_exit
	
	li			$a0, 1				# set the seed id	
	li			$a1, 64				# This will give range [0-63]		
	jal			get_rand_int		# the number is in $v0
	move		$t1, $v0			# now it's in $t1
	
	li			$a0, 1				# set the seed id	
	li			$a1, 64				# This will give range [0-63]		
	jal			get_rand_int		# the number is in $v0
	
	move		$a0, $t1
	move		$a1, $v0
	li			$a2, 3
	jal			setLED

	addi		$t0, $t0, -1		# decrement counter

	j			init_frogs_loop	
init_frogs_exit:	
	
	# get random numbers for the five green LEDs
	# note: this stores the x positions from last -> first
	li			$t0, 30				# set the counter to 5
	la			$t1, green_x		# base address we will be storing to
	
	init_green_x_loop:
	beq			$t0, 0, init_green_x_exit
	
	li			$a0, 1				# set the seed id	
	li			$a1, 64				# This will give range [0-63]		
	jal			get_rand_int		# the number is in $v0
	
	addi		$t0, $t0, -1		# decrement counter
	sll			$t2, $t0, 2			# multiply counter by four
	add			$t2, $t1, $t2		# and then add offset to the base adress
	sw			$v0, ($t2)

	j			init_green_x_loop
	
init_green_x_exit:	

# get random numbers for the five green LEDs
# note: this stores the y positions from last -> first		
	li			$t0, 30
	la			$t1, green_y	
init_green_y_loop:
	beq			$t0, 0, init_green_y_exit
	
	li			$a0, 1				# set the seed ID		
	li			$a1, 64				# This will give range [0-63]		
	jal			get_rand_int		# the number is in $v0
	
	addi		$t0, $t0, -1		# decrement counter
	sll			$t2, $t0, 2			# multiply counter by four
	add			$t2, $t1, $t2		# and then add it to the base adress
	sw			$v0, ($t2)
	
	j			init_green_y_loop
	
init_green_y_exit:	
	
	jal			show_green
	
_poll:
	# check for a key press
	la			$t0, 0xffff0000		# status register address	
	lw			$t0, 0($t0)			# read status register
	andi		$t0, $t0, 1			# check for key press
	bne			$t0, $0, _keypress
	
	j	_poll

_keypress:
	# handle a keypress to change snake direction
	la			$t0, 0xffff0004		# keypress register
	lw			$t0, 0($t0)			# read keypress register

	# clear current star
	li			$a2, 0
	jal 		setLED

	# center key
	subi		$t1, $t0, 66			# center key?
	beq			$t1, $0, center_pressed		

	# if here, then not center, so clear current position
	move		$a0, $s0
	move		$a1, $s1
	li			$a2, 0
	jal			setLED
	
	
	# left key
	subi		$t1, $t0, 226				# left key?
	beq			$t1, $0, left_pressed		

	# right key
	subi		$t1, $t0, 227				# right key?
	beq			$t1, $0, right_pressed		

	# up key
	subi		$t1, $t0, 224				# up key?
	beq			$t1, $0, up_pressed			

	# down key
	subi		$t1, $t0, 225				# down key?
	beq			$t1, $0, down_pressed		

	j			_poll

right_pressed:
	addi		$s0, $s0, 1
	bge			$s0, 64, RIGHT_SIDE
	j			move_done
	RIGHT_SIDE:
	li			$s0, 0
	j			move_done

left_pressed:
	subi		$s0, $s0, 1
	# if a0<0, a0=127
	blt			$s0, $zero, LEFT_SIDE
	j			move_done
	LEFT_SIDE:
	li			$s0, 63
	j			move_done

up_pressed:
	subi		$s1, $s1, 1
	blt			$s1, $zero, DOWN_SIDE
	j			move_done
	DOWN_SIDE:
	li			$s1, 63
	j			move_done

down_pressed:
	addi		$s1, $s1, 1
	bge			$s1, 64, UP_SIDE
	j			move_done
	UP_SIDE:
	li			$s1, 0
	j			move_done

center_pressed:
	#$a0 = 0 => check x, $a0 = 1 => check y, $a1 has value to check
	move		$a2, $a0
	move		$a3, $a1			# save values
	
	li			$a0, 0				# check x
	move		$a1, $s0			# x value to check
	jal			check_for_match
	
	beq			$v0, -1, move_done	# if no match, then just loop again
	move		$t0, $v0			# if here then x matches, so store it to $t0
	
	li			$a0, 1				# check y
	move		$a1, $s1			# y value to check
	jal			check_for_match
	
	beq			$v0, -1, move_done	# if no match, then just loop again
	move		$t1, $v0			# if here then both x and y match, y is now in $t1
	
	li			$t2, -1
	sw			$t2, ($t0)
	sw			$t2, ($t1)			# store -1 at the right x and y positions
	
	addi		$s2, $s2, 1
	
	beq			$s2, 30, _exit		# if the score is 5, then exit!

move_done:
	# place code
	jal			show_green
	move		$a0, $s0
	move		$a1, $s1
	lw			$a2, init_color
	jal			setLED
			
j	_poll

_exit:
#	la			$a0, win_message
#	li			$v0, 4
 # syscall
	
	li			$v0, 10 
  syscall
	
get_rand_int:		# argument: $a1 has range upper value (exclusive), return: $v0 has the random int
	# preamble
	addi		$sp, $sp, -12
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)
	
	li			$v0, 42				# random number within range
	li			$a0, 1				# set the i.d. to 1
  syscall							# generates a random int 0-range	
  
  	move		$v0, $a0			# move it to $v0
	
	# postamble
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
	
	jr			$ra	
	
check_for_match:	# argument: $a0 = 0 => check x, $a0 = 1 => check y, $a1 has value to check
					# returns: address of match in $v0, or -1 if no match
# preamble	
	addi		$sp, $sp, -16
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$ra, 12($sp)
	
	li			$t0, 30				# set the counter
	beq			$a0, 0, check_for_match_x			# check the argument
	
	la			$t1, green_y		# if you're here, you want y
	j			check_for_match_loop
	
check_for_match_x:
	la			$t1, green_x		# otherwise you want x
	
check_for_match_loop:	
	beq			$t0, 0, check_for_match_fail		# if the counter hits 0, no match
	
	addi		$t0, $t0, -1		# decrement counter
	sll			$t2, $t0, 2			# multiply counter by four
	add			$t2, $t1, $t2		# and then add it to the base adress
	lw			$v0, ($t2)			# load the value to $v0
	
	beq			$v0, $a1, check_for_match_success	# $v0 = value to check => found a match
	
	j			check_for_match_loop
	
check_for_match_success:
	move		$v0, $t2			# now $v0 has the address of the match (for return)
	j			check_for_match_exit

check_for_match_fail:
	li			$v0, -1				# load the fail value

check_for_match_exit:
# postamble
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$ra, 12($sp)
	addi		$sp, $sp, 16
	
	jr			$ra

win:
	li			$a0, 200
	li			$v0, 1
  syscall
  
  	j			_exit
  
  
show_green:							# void function- simply displays all non -1 green LEDs
# preamble
	addi		$sp, $sp, -16
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$ra, 12($sp)

	la			$t0, green_x
	la			$t1, green_y
	lw			$a2, green_color
	
	li			$t2, 30				# initialize counter
show_green_loop:	
	beq			$t2, 0, show_green_exit
	
	lw			$a0, ($t0)
	lw			$a1, ($t1)

	beq			$a0, -1, skip_showing	# if the x position is -1, then don't display the dot
	beq			$a1, -1, skip_showing	# if for some reason x is != -1 but y is, same thing
	
	jal			setLED

skip_showing:		
	addi		$t0, $t0, 4
	addi		$t1, $t1, 4			# add after the fact
	addi		$t2, $t2, -1		# decrement counter
	
	j			show_green_loop
	
show_green_exit:
# postamble
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$ra, 12($sp)
	addi		$sp, $sp, 16
	
	jr			$ra


#-----------Start of getLED-----------#
getLED:			# arguments: $a0 is x, $a1 is y (both 0-63)
				# returns: $v0 has the color (0 black, 1 red, 2 orange, 3 green)
# preamble
	addi		$sp, $sp, -16
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$ra, 12($sp)
			
_getLED:	
	# byte offset into display = y * 16 bytes + (x / 4)
	sll  		$t0, $a1, 4			# y * 16 bytes
	srl  		$t1, $a0, 2      	# x / 4
	add  		$t0, $t0, $t1    	# byte offset into display
	la   		$t2, 0xffff0008
	add  		$t0, $t2, $t0    	# address of byte with the LED
	
	# now, compute bit position in the byte and the mask for it
	andi 		$t1, $a0, 0x3    	# remainder is bit position in byte
	neg  		$t1, $t1       		# negate position for subtraction
	addi 		$t1, $t1, 3      	# bit positions in reverse order
    sll  		$t1, $t1, 1	      	# led is 2 bits
	
	# load LED value, get the desired bit in the loaded byte
	lbu  		$t2, 0($t0)
	srlv 		$t2, $t2, $t1    	# shift LED value to lsb position
	andi 		$v0, $t2, 0x3    	# mask off any remaining upper bits
	
getLED_exit:
# postamble
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$ra, 12($sp)
	addi		$sp, $sp, 16	
	
	jr   $ra
#-----------End of getLED-----------#




#-----------Start of setLED-----------#
setLED:			# arguments: $a0 is x, $a1, is y (both 0-63),
				#			 $a2 color (0 black, 1 red, 2 orange, 3 green)
				# returns: none
# preamble
	addi		$sp, $sp, -20		
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$t3, 12($sp)
	sw			$ra, 16($sp)	
		
_setLED:
	# byte offset into display = y * 16 bytes + (x / 4)
	sll			$t0, $a1, 4      	# y * 16 bytes
	srl			$t1, $a0, 2 	    # x / 4
	add			$t0, $t0, $t1   	# byte offset into display
	li			$t2, 0xffff0008		# base address of LED display
	add			$t0, $t2, $t0    	# address of byte with the LED
	
	# now, compute led position in the byte and the mask for it
	andi		$t1, $a0, 0x3    	# remainder is led position in byte
	neg			$t1, $t1        	# negate position for subtraction
	addi		$t1, $t1, 3      	# bit positions in reverse order
	sll			$t1, $t1, 1      	# led is 2 bits
	
	# compute two masks: one to clear field, one to set new color
	li			$t2, 3		
	sllv		$t2, $t2, $t1
	not			$t2, $t2       		# bit mask for clearing current color
	sllv		$t1, $a2, $t1    	# bit mask for setting color
	
	# get current LED value, set the new field, store it back to LED
	lbu			$t3, 0($t0)     	# read current LED value	
	and			$t3, $t3, $t2    	# clear the field for the color
	or			$t3, $t3, $t1    	# set color field
	sb			$t3, 0($t0)     	# update display
	
setLED_exit:
# postamble	
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$t3, 12($sp)
	lw			$ra, 16($sp)	
	addi		$sp, $sp, 20		
	
	jr	$ra
#-----------End of setLED-----------#

 #---------------------------#  	
 #-------End Functions-------#
 #---------------------------#  
