	# correct output to LED display is 0 (initial value), 1, 0
	li	$r0,1		# $r0 is 1
	bz	$r0,loop2	# $r0 is not 1, so fall through
	put	$r0		# correct output 1 to display 
	addi	$r0,-1		# $r0 = $r0-1 = 0
	bz	$r0,loop3	# $r0 is now 0, so jump to loop 3
	li	$r0,0xf		
	put	$r0		# incorrect output 0xF to display
loop3:
	put	$r0		# output 0 to display 
	halt			# halt
loop2:	li	$r0,0xf		# incorrect output - 1st bz was taken!
	put	$r0
	halt
	