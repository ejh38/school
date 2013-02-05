	li	$a1,2		# green LED
	la	$a0,2
	jal	_setcol_led
	la	$a0,3
	jal	_setcol_led
	la	$a0,126
	jal	_setcol_led
	la	$a0,127
	jal	_setcol_led
	li	$v0,10
	syscall


_setcol_led:
	# $a0 holds the column number to set 0-127
	# $a1 holds the code to output
	li	$t0,4
	move	$t1,$a0

	# first, we determine the byte that has the column with integer division
	# the result of the division is the byte number
	# the remainder of the division is the two-bit position in the byte
	# e.g., suppose we want to set column 9
	#    col 9 / 4 leds per column = byte 2 holds the column
	#    remainder is 1, so we need to set bits 5,4
	#
	andi	$t0,$t1,0x3	# remainder from integer division by 4 (power of 2)
	sll	$t0,$t0,1	# multiple remainder by 2 to get bit position from left
	srl	$t1,$t1,2	# integer divide by 4 (power of 2)
	sll	$t2,$a1,6	# put color value into leftmost LED position
	srlv	$t2,$t2,$t0	# shift the LED value to the right (i.e., from the left)
	# now, $t1 has the byte offset into the LED
	# $t2 has the correct mask to write to the LEDs
	#
	# next, we loop through the 8 rows to set their output
	li	$t0,8		# 8 rows - count down!
	la	$t3,0xFFFF0008	# LED base address
	add	$t1,$t1,$t3	# $t1 has start address for column x, row 0
_setcol_led2:
	lb	$t3,0($t1)	# get current LED value
	or	$t3,$t3,$t2	# set new LED column
	sb	$t3,0($t1)	# update LED display
	addi	$t1,$t1,32	# next row down is +32 bytes beyond current address
	addi	$t0,$t0,-1	# decrement count
	bne	$t0,$0,_setcol_led2
	# and, we're done!
	jr	$ra
