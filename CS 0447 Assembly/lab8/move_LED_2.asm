# navigates the RED star
# trail cleared

.data

init_x:		.word	64
init_y:		.word	3
init_color:		.word	1

.text
	# init LED
	lw	$a0, init_x
	lw	$a1, init_y
	lw	$a2, init_color
	jal	setLED
	
_poll:
	# check for a key press
	la	$t0,0xffff0000	# status register address	
	lw	$t0,0($t0)	# read status register
	andi	$t0,$t0,1		# check for key press
	bne	$t0,$0,_keypress
	
	j	_poll

_keypress:
	# handle a keypress to change snake direction
	la	$t0,0xffff0004	# keypress register
	lw	$t0,0($t0)	# read keypress register

	# clear current star
	li	$a2, 0
	jal 	setLED

	# center key
	subi	$t1, $t0, 66				# center key?
	beq	$t1, $0, center_pressed		# 

	# left key
	subi	$t1, $t0, 226				# left key?
	beq	$t1, $0, left_pressed		# 

	# right key
	subi	$t1, $t0, 227				# right key?
	beq	$t1, $0, right_pressed		# 

	# up key
	subi	$t1, $t0, 224				# up key?
	beq	$t1, $0, up_pressed			# 

	# down key
	subi	$t1, $t0, 225				# down key?
	beq	$t1, $0, down_pressed		# 

	j	_poll

right_pressed:
	addi	$a0, $a0, 1
	bge	$a0, 128, RIGHT_SIDE
	j	move_done
	RIGHT_SIDE:
	li	$a0, 0
	j	move_done

left_pressed:
	subi	$a0, $a0, 1
	# if a0<0, a0=127
	blt	$a0, $zero, LEFT_SIDE
	j	move_done
	LEFT_SIDE:
	li	$a0, 127
	j	move_done

up_pressed:
	subi	$a1, $a1, 1
	blt	$a1, $zero, DOWN_SIDE
	j	move_done
	DOWN_SIDE:
	li	$a1, 7
	j	move_done

down_pressed:
	addi	$a1, $a1, 1
	bge	$a1, 8, UP_SIDE
	j	move_done
	UP_SIDE:
	li	$a1, 0
	j	move_done

center_pressed:
	j	_exit

move_done:
	# place code
	lw	$a2, init_color
	jal	setLED
		
j	_poll

_exit:
	li	$v0, 10
	syscall

setLED:
	subi	$sp, $sp, 20
	sw	$t0, 0($sp)
	sw	$t1, 4($sp)
	sw	$t2, 8($sp)
	sw	$t3, 12($sp)
	sw	$ra, 16($sp)

	jal	_setLED

	lw	$t0, 0($sp)
	lw	$t1, 4($sp)
	lw	$t2, 8($sp)
	lw	$t3, 12($sp)
	lw	$ra, 16($sp)
	addi	$sp, $sp, 20
	
	jr	$ra


	# void _setLED(int x, int y, int color)
	#   sets the LED at (x,y) to color
	#   color: 0=off, 1=red, 2=orange, 3=green
	#
	# arguments: $a0 is x, $a1 is y, $a2 is color
	# trashes:   $t0-$t3
	# returns:   none
	#
_setLED:
	# byte offset into display = y * 32 bytes + (x / 4)
	sll	$t0,$a1,5      # y * 32 bytes
	srl	$t1,$a0,2      # x / 4
	add	$t0,$t0,$t1    # byte offset into display
	li	$t2,0xffff0008	# base address of LED display
	add	$t0,$t2,$t0    # address of byte with the LED
	# now, compute led position in the byte and the mask for it
	andi	$t1,$a0,0x3    # remainder is led position in byte
	neg	$t1,$t1        # negate position for subtraction
	addi	$t1,$t1,3      # bit positions in reverse order
	sll	$t1,$t1,1      # led is 2 bits
	# compute two masks: one to clear field, one to set new color
	li	$t2,3		
	sllv	$t2,$t2,$t1
	not	$t2,$t2        # bit mask for clearing current color
	sllv	$t1,$a2,$t1    # bit mask for setting color
	# get current LED value, set the new field, store it back to LED
	lbu	$t3,0($t0)     # read current LED value	
	and	$t3,$t3,$t2    # clear the field for the color
	or	$t3,$t3,$t1    # set color field
	sb	$t3,0($t0)     # update display
	jr	$ra
	



