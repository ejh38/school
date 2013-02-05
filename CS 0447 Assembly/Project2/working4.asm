# Zach Sadler
# This is ONLY
# trying to get the queue to work
# Have insert working perfectly
# WITH wrap-around!! Wooooo!!
# AND with remove and peek! Got it!!

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

	li			$a0, 100
	li			$a1, 101
	jal			insert
	
	jal			peek
	move		$t0, $v0
	move		$t1, $v1
	li			$v0, 1
	move		$a0, $t0
  syscall
  	move		$a0, $t1
  syscall
  
 	li			$a0, 37
	li			$a1, 64
	jal			insert
	
	jal			peek
	move		$t0, $v0
	move		$t1, $v1
	li			$v0, 1
	move		$a0, $t0
  syscall
  	move		$a0, $t1
  syscall
  
  	jal			remove
  	jal			remove
  	jal			remove
  	
  	li			$a0, 1
  	li			$a1, 1
  	jal			insert
  	
	jal			peek
	move		$t0, $v0
	move		$t1, $v1
	li			$v0, 1
	move		$a0, $t0
  syscall
  	move		$a0, $t1
  syscall
  	
  	jal 		remove
 
	j			exit


insert:			# arguments: $a0 is x coord, $a1 is y coord
				# returns: none- void function
				# inserts the coordinates into the queue at the logical end of the queue
# preamble
	addi		$sp, $sp, -12
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$ra, 8($sp)
	
	jal			calculate_end
	sw			$a0, ($v0)
	sw			$a1, ($v1)
	
	addi		$s0, $s0, 1				# increment the length!
# postamble	
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$ra, 8($sp)
	addi		$sp, $sp, 12
		
	jr			$ra	
	
remove:			# arguments: none
				# returns: $v0 has x, $v1 has y of the front entry	
# preamble
	addi		$sp, $sp, -16
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$ra, 12($sp)				
				
	lw			$t0, queue_x_front
	lw			$v0, ($t0)				# save for return
	lw			$t1, queue_y_front
	lw			$v1, ($t1)				# save for return
		
	li			$t2, -1					# now the remove
	sw			$t2, ($t0)				# overwrite with -1
	sw			$t2, ($t1)				# for both x and y
	
	addi		$s0, $s0, -1			# decrement the length
	addi		$t0, $t0, 4				# move the pointer forward
	addi		$t1, $t1, 4				# move the pointer forward
	
	la			$t2, snake_y

	blt			$t0, $t2, no_wrap_x
	la			$t0, snake_x			# if need to wrap, then wrap to start
no_wrap_x:
	la			$t2, snake_y + 256
	blt			$t1, $t2, remove_exit
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
	
peek:					# arguments: none
						# returns: $v0 has x, $v1 has y of the end entry
	addi		$sp, $sp, -4					
	sw			$ra, 0($sp)
	
	addi		$s0, $s0, -1
	jal			calculate_end
	addi		$s0, $s0, 1

	lw			$v0, ($v0)
	lw			$v1, ($v1)
	
	lw			$ra, 0($sp)
	addi		$sp, $sp, 4
	
	jr			$ra
						
	
	
calculate_end:			# arguments: none
						# returns: $v0 ($v1) has the address of the logical end of the queue x (y)
						#	24 + 48	= 72 - 64 = 8
						#	7th					3rd
						# if > 64 then - 64, store there, this is the wrap around
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
	j			after_wrap_y
wrap_around_y:
	addi		$t0, $t0, -256			# if you need to, then sub 64 to wrap around
	move		$v1, $t0				# and store for return
after_wrap_y:		
# postamble	
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$ra, 12($sp)
	addi		$sp, $sp, 16					
	
	jr			$ra
						
																
exit:
	li			$v0, 10
	syscall