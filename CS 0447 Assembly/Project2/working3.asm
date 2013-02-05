###############################
# Zach Sadler
# zps6@pitt.edu
# Second working progress of 
# Project 2.
# This is the start of turning
# lab8 into Snake
# NOTE THIS IS MOSTLY BROKEN
###############################

.data						
snake_x:			.word	1, 2, 3, 4, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 
snake_y:			.word	31, 31, 31, 31, 31, 31, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
head_x:				.word	7
head_y:				.word	31
tail_x:				.word	0
tail_y:				.word	31
	
.text
	
	# get random numbers for the 32 frogs
	# note: this stores the x positions from last -> first
	li			$t0, 32				# set the counter to 5
init_frogs_loop:
	beq			$t0, 0, show_snake
	
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
	
show_snake:	
	# load the initial values for the queue front and end, x and y.
	la			$t0, snake_x + 28
	sw			$t0, queue
	la			$t0, snake_y + 28
	sw			$t0, queue + 4
	la			$t0, snake_x
	sw			$t0, queue + 8
	la			$t0, snake_y
	sw			$t0, queue + 12
	
	li			$t0, 8				# initialize counter
	la			$t1, snake_x
	la			$t2, snake_y
	li			$a2, 2
show_snake_loop:
	beq			$t0, 0, show_snake_exit
	
	lw			$a0, ($t1)
	lw			$a1, ($t2)
	jal			setLED
	
	addi		$t0, $t0, -1
	addi		$t1, $t1, 4
	addi		$t2, $t2, 4
	
	j			show_snake_loop

show_snake_exit:
	# setting up the RNG 	
  	li			$v0, 30				
  syscall							# get system time
	move		$a1, $a0			# move it so it can be used as argument
	li			$a0, 1				# 1 is the i.d. for the rng seed
	li			$v0, 40				
  syscall							# set the seed with that time				
 	# finished setting up RNG	
	
_poll:
	# check for a key press
	la			$t0, 0xffff0000		# status register address	
	lw			$t0, 0($t0)			# read status register
	andi		$t0, $t0, 1			# check for key press
	bne			$t0, $0, move_done
	
	j	_poll

move_done:

snake_step:
	
	# add a new one to the end
#	lw			$t0, queue + 8		# pointer to the x end address
#	lw			$a0, ($t0)			# store the curr x value to $a0
	li			$a0, 31
	lw			$t0, queue + 12		# pointer to the y end address
	lw			$t1, ($t0)			# load the actual y value
	addi		$a1, $t1, 1			# add 1, and store it to $a1
	li			$a2, 2
	jal			setLED
	
	lw			$t0, queue + 4		# pointer to the y front address
	lw			$t1, ($t0)			# load the actual y value
	addi		$a1, $t1, 1			# add 1, and store it to $a1
	li			$a2, 0
	jal			setLED
	
	jal			insert

	jal			remove
	move		$a0, $v0
	move		$a1, $v1
	li			$a2, 0
	
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

win:
	li			$a0, 200
	li			$v0, 1
  syscall
  
  	j			_exit

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

#-----------Start of insert-----------#
insert:			# argument: $a0 is x, $a1 is y (coordinates of pos to insert)
				# returns: none
				# note: inserts into the END of the queue
# preamble
	addi		$sp, $sp, 12
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)	
	
	# first, we move the tail address back one position, so we insert it to a blank spot
	
	la			$t0, snake_x
	lw			$t1, queue + 8				# if this is the case, then we need to push the end
	beq			$t1, $t0, insert_skip_x		# around from the physical start to the physical end
	addi		$t1, $t1, -4				# otherwise, go back one word
	j			insert_y
insert_skip_x:
	la			$t1, snake_x + 156			# load the physical end address

insert_y:
	# either way, insert the actual x into the right spot
	sw			$t1, queue + 8				# and store it back
	sw			$a0, ($t1)
	
	la			$t0, snake_y + 4
	lw			$t1, queue + 12				# if this is the case, then we need to push the end
	blt			$t1, $t0, insert_skip_y		# around from the physical start to the physical end
	addi		$t1, $t1, -4				# otherwise, go back one word
	sw			$t1, queue + 12				# and store it back
	j			insert_exit
insert_skip_y:
	la			$t1, snake_y + 156			# load the physical end address
	sw			$t1, queue + 12				# and store that as the new end x pos	
	
insert_exit:
	# either way, insert the actual y into the right spot
	lw			$t1, queue + 12
	sw			$a1, ($t1)
	
# postamble
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, -12
	
	jr			$ra
#-----------End of insert-----------#

#-----------Start of remove-----------#
remove:			# argument: none)
				# returns: $v0 the x pos, $v1 the y pos of the FRONT of the queue

# preamble
	addi		$sp, $sp, 12
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)	
	
	la			$t0, snake_x + 4
	lw			$t1, queue					# if this is the case, then we need to push the end
	blt			$t1, $t0, remove_skip_x		# around from the physical start to the physical end
	
	addi		$t1, $t1, -4				# otherwise, go back one word
	sw			$t1, queue					# and store it back
	j			remove_y
remove_skip_x:
	la			$t1, snake_x + 156			# load the physical end address
	sw			$t1, queue					# and store that as the new end x pos

remove_y:
# either way, remove the actual x into the right spots
	lw			$t0, queue + 8
	lw			$v0, ($t0)					# for the return value
	li			$a0, -1
	sw			$a0, ($t0)					# and overwrite it with -1 (removed)
	
	la			$t0, snake_y + 4
	lw			$t1, queue + 4				# if this is the case, then we need to push the end
	blt			$t1, $t0, remove_skip_y		# around from the physical start to the physical end
	addi		$t1, $t1, -4				# otherwise, go back one word
	sw			$t1, queue + 4				# and store it back
	j			remove_exit
remove_skip_y:
	la			$t1, snake_y				# load the physical end address
	addi		$t1, $t1, 156
	sw			$t1, queue + 4				# and store that as the new end x pos	
	
remove_exit:
	lw			$t0, queue + 12
	lw			$v1, ($t0)					# for the return value
	li			$a0, -1
	sw			$a0, ($t0)					# and overwrite it with -1 (removed)

# postamble
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, -12

	jr			$ra
#-----------End of remove-----------#
