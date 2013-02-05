	# tests bn
	#
	# assumes addi, put, and halt work
	#
	addi	$r0,0x80	# negative value
	addi	$r1,0x1		# positive value
	addi	$r3,0x1
	bn	$r1,failed	# branch not taken b/c $r1 is positive
	put	$r3		# correct output 1
	bn	$r0,correct	# branch taken b/c $r0 is negative
	addi	$r5,0xff	# fall-thru is incorrect
	put	$r5		# incorrect output
	halt
back:
	addi	$r3,1
	put	$r3		# correct output 3
	bn	$r2,failed	# branch not taken b/c $r2 is zero (not negative)
	addi	$r3,1
	put	$r3		# correct output 4
	halt			# reached here: test ran successfully
correct:
	addi	$r3,1		# correct output 2
	put	$r3
	bn	$r0,back	# branch taken backwards b/c $r0 is negative
failed:
	addi	$r5,0xff
	put	$r5		# incorrect output
	halt	
	