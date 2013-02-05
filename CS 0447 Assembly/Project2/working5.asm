# Zach Sadler
# Prettied some stuff up with comments,
# and then tested adding and 
# removing a lot of entries
# (it worked)

.data
snake_x:		.word		-1:64
snake_y:		.word		-1:64
queue_x_front:	.word		-1
queue_y_front:	.word		-1

.text

	# this initializes snake_x with 0 - 7
	# and snake_y with 8 31's
initialize_snake:
	la			$a0, snake_x
	la			$a1, snake_y
	li			$t0, 0
	li			$t1, 31
initialize_snake_loop:	
	beq			$t0, 8, initialize_queue
	
	sw			$t0, 0($a0)
	sw			$t1, 0($a1)
	
	addi		$a0, $a0, 4
	addi		$a1, $a1, 4
	addi		$t0, $t0, 1
	
	j			initialize_snake_loop
initialize_queue:
	move		$s0, $t0				# $s0 will store the snake's length
	
	la			$a0, snake_x
	la			$a1, queue_x_front
	sw			$a0, ($a1)				# store the front of the x queue to queue_x_front
	
	la			$a0, snake_y
	la			$a1, queue_y_front
	sw			$a0, ($a1)

	li			$t0, 8					# counter
move_left_to_right_loop:
	beq			$t0, 64, move_exit
	
	move		$a0, $t0
	li			$a1, 31
	jal			insert
	jal			remove

	addi		$t0, $t0, 1
	
	j			move_left_to_right_loop
	
move_exit:	
 
	j			exit


exit:
	li			$v0, 10
	syscall
	

 #--------------------------------#
 #-------Start of Functions-------#
 #--------------------------------#

#--------Start of insert-----------#					
insert:			# arguments: $a0 is x coord, $a1 is y coord of the point to insert
				# returns: none
				# inserts the coordinates into the queue at the logical end of the queue
# preamble
	addi		$sp, $sp, -12
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)
	
	jal			calculate_end			# this does the real work in finding the next blank space
	sw			$a0, ($v0)				# then put the coordinates where they belong
	sw			$a1, ($v1)				# same with y
	
	addi		$s0, $s0, 1				# increment the length!
# postamble	
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
		
	jr			$ra	
#--------End of insert-----------#					

#--------Start of remove-----------#					
remove:			# arguments: none
				# returns: $v0 has x coord, $v1 has y coord of the front entry	
# preamble
	addi		$sp, $sp, -16
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$ra, 12($sp)				
				
	lw			$t0, queue_x_front		# get the pointer
	lw			$v0, ($t0)				# save the x coord for return
	lw			$t1, queue_y_front		# get the pointer
	lw			$v1, ($t1)				# save the y coord for return
		
	li			$t2, -1					# now the remove
	sw			$t2, ($t0)				# overwrite with -1
	sw			$t2, ($t1)				# for both x and y
	
	addi		$s0, $s0, -1			# decrement the length!
	addi		$t0, $t0, 4				# move the pointer forward
	addi		$t1, $t1, 4				# move the pointer forward
	
	la			$t2, snake_y			# load this value for comparison
	blt			$t0, $t2, no_wrap_x		# see if past the end of snake_x
	la			$t0, snake_x			# if need to wrap, then wrap to start
no_wrap_x:
	la			$t2, snake_y + 256		# needed for comparison
	blt			$t1, $t2, remove_exit	# see if past the end of snake_y
	la			$t1, snake_y			# if need to wrap, then wrap to start

remove_exit:
	sw			$t0, queue_x_front
	sw			$t1, queue_y_front		# store the right values for the pointers

# postamble
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$ra, 12($sp)	
	addi		$sp, $sp, 16	
	
	jr			$ra
#-----------End of remove-----------#			
	
#-----------Start of peek-----------#			
peek:					# arguments: none
						# returns: $v0 has x coord, $v1 has y coord of the end entry
	addi		$sp, $sp, -4					
	sw			$ra, 0($sp)
	
	addi		$s0, $s0, -1			# need to adjust since calculate_end gets first blank spot
	jal			calculate_end
	addi		$s0, $s0, 1				# need to adjust back
	lw			$v0, ($v0)				# now load the x coord from the address
	lw			$v1, ($v1)				# same with y
	
	lw			$ra, 0($sp)
	addi		$sp, $sp, 4
	
	jr			$ra
#-----------End of peek----------#								
	
#--------Start of calculate_end-------#		
calculate_end:			# arguments: none
						# returns: $v0 ($v1) has the address of the logical end of the queue x (y)
						# note: this is a private function which is called to 
						# help with wrap around and peeking
# preamble
	addi		$sp, $sp, -16
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$ra, 12($sp)	
	
	lw			$t0, queue_x_front		# load the address of the front of the queue
	sll			$t1, $s0, 2				# multiply length by 4
	add			$t0, $t1, $t0			# add offset to front of the queue
	la			$t2, snake_y
	bge			$t0, $t2, wrap_around_x
	move		$v0, $t0				# if you don't need to wrap_around, then just move it to return
	j			after_wrap_x
wrap_around_x:
	addi		$t0, $t0, -256			# if you need to, then sub 256 to wrap around
	move		$v0, $t0				# and store for return
after_wrap_x:
	lw			$t0, queue_y_front		# load the address of the front of the queue
	sll			$t1, $s0, 2				# multiply length by 4
	add			$t0, $t1, $t0			# add offset to front of the queue
	la			$t2, snake_y + 256
	bge			$t0, $t2, wrap_around_y
	move		$v1, $t0				# if you don't need to wrap_around, then just move it to return
	j			calculate_end_exit
wrap_around_y:
	addi		$t0, $t0, -256			# if you need to, then sub 64 to wrap around
	move		$v1, $t0				# and store for return

calculate_end_exit:		
# postamble	
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$ra, 12($sp)
	addi		$sp, $sp, 16					
	
	jr			$ra
#-------End of calculate_end----------#							
																
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