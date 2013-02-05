# Zach Sadler
# Reads keypresses and moves
# the snake accordingly!
# With wraparound working for
# all sides!

.data
snake_x:		.word		-1:64
snake_y:		.word		-1:64
queue_x_front:	.word		-1
queue_y_front:	.word		-1

.text

# setting up the RNG 	
  	li			$v0, 30				
  syscall							# get system time
	move		$a1, $a0			# move it so it can be used as argument
	li			$a0, 1				# 1 is the i.d. for the rng seed
	li			$v0, 40				
  syscall							# set the seed with that time				
# finished setting up RNG

	jal			init_frogs			# display the 32 random frogs
	jal			init_snake			# initialize the snake x and y 
	jal			init_queue			# initialize the queue pointers to the front of x and y

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

	jal			peek				# get the end coordinates
	
	# center key
	subi		$t1, $t0, 66			# center key?
	beq			$t1, $0, center_pressed		
	
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

# directions: $s1 for x: -1 left, 1 right, 0 neither
#			  $s2 for y: -1 up, 1 down, 0 neither
right_pressed:
	li			$s1, 1
	li			$s2, 0
	beq			$v0, 63, hit_right
	j			move_done
left_pressed:
	li			$s1, -1
	li			$s2, 0
	beq			$v0, 0, hit_left
	j			move_done
up_pressed:
	li			$s1, 0
	li			$s2, -1
	beq			$v1, 0, hit_top
	j			move_done
down_pressed:
	li			$s1, 0
	li			$s2, 1
	beq			$v1, 63, hit_bottom
	j			move_done
center_pressed:	
 
	j	exit

hit_right:
	li			$a0, 0
	move		$a1, $v1
	j			hit_done
hit_left:
	li			$a0, 63
	move		$a1, $v1	
	j			hit_done
hit_top:
	li			$a1, 63
	move		$a0, $v0	
	j			hit_done
hit_bottom:
	li			$a1, 0
	move		$a0, $v0	
	j			hit_done			
move_done:
	jal			peek					# get the end coordinates
	add			$a0, $s1, $v0			# then add the appropriate offset to
	add			$a1, $s2, $v1			# the x and y values, storing them in
hit_done:	
	jal			insert					# $a0 and $a1 for easy insert
	li			$a2, 2					# and displaying access
	jal			setLED
	jal			remove
	move		$a0, $v0
	move		$a1, $v1
	li			$a2, 0
	jal			setLED
	
			
	j	_poll


exit:
	li			$v0, 10
	syscall
	

 #--------------------------------#
 #-------Start of Functions-------#
 #--------------------------------#

#----Start of init_queue------# 	
init_queue:				# arguments: none
						# returns: none
						# this initializes the queue with the correct pointers
# preamble						
	addi		$sp, $sp, -4
	sw			$ra, 0($sp)

	li			$s0, 8					# $s0 will store the snake's length
	
	la			$a0, snake_x
	la			$a1, queue_x_front
	sw			$a0, ($a1)				# store the front of the x queue to queue_x_front
	
	la			$a0, snake_y
	la			$a1, queue_y_front
	sw			$a0, ($a1)				# store the front of the y queue to queue_y_front

# postamble	
	lw			$ra, 0($sp)
	addi		$sp, $sp, 4
	
	jr			$ra
#------End of init_queue------# 	
	
#----Start of init_snake------# 
init_snake:				# arguments: none
						# returns: none
						# this initializes snake_x with 0 - 7
						# and snake_y with 8 31's
#preamble
	addi		$sp, $sp, -4
	sw			$ra, 0($sp)

	li			$t0, 0
	li			$t1, 31		
	la			$t2, snake_x
	la			$t3, snake_y
	
	li			$a2, 2
initialize_snake_loop:	
	beq			$t0, 8, initialize_snake_exit
	
	sw			$t0, 0($t2)
	sw			$t1, 0($t3)
	
	move		$a0, $t0
	move		$a1, $t1
	jal			setLED					# display the position too
	
	addi		$t2, $t2, 4
	addi		$t3, $t3, 4
	addi		$t0, $t0, 1
	
	j			initialize_snake_loop
	
initialize_snake_exit:
# postamble	
	lw			$ra, 0($sp)
 	addi		$sp, $sp, 4
 	
 	jr			$ra
#--------End of init_snake------# 	



#----Start of init_frogs------# 
init_frogs:				# arguments: none
						# returns: none
						# this is simply a void function to display 32 random frogs
# preamble
	addi		$sp, $sp, -12
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)

	li			$t0, 32				# set the counter to 32
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
# postamble	
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
 	addi		$sp, $sp, 12
 	
 	jr			$ra
#--------End of init_frogs------# 	
 	
#------Start of get_rand_int------#					 
get_rand_int:				# arguments: $a1 has range upper value (exclusive), 
							# returns: $v0 has the random int
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
#--------End of get_rand_int-----------#					

#--------Start of insert-----------#					
insert:					# arguments: $a0 is x coord, $a1 is y coord of the point to insert
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
remove:					# arguments: none
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
