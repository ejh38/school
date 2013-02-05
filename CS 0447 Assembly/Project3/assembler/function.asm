	# $r7 is used as stack pointer
	# $r6 is used as return address register
	
	li	$r7,255		# stack start at end of memory
	li	$r4,0xff
	put	$r4
	# function call
	li	$r0,9
	jal	$r6,func
	# return point
	li	$r4,0xAA
	put	$r4
	halt

	# $r0 holds the argument
func:	addi	$r7,-1
	sw	$r6,$r7
	put	$r0
	bz	$r0,func1
	addi	$r0,-1
	jal	$r6,func
func1:	lw	$r6,$r7
	addi	$r7,1
	jr	$r6
	
	
	
	

	
