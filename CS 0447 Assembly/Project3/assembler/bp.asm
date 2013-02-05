	# tests bp
	#
	# assumes addi, put work
	#
	addi	$r0,0x80	# negative value
	addi	$r1,0x1		# positive value
	addi	$r3,0x1
	bp	$r0,failed	# branch not taken b/c $r0 is negative
	put	$r3		# correct output 1
	bp	$r1,correct	# branch taken b/c $r1 is positive
	addi	$r5,0xff	# fall-thru is incorrect
	put	$r5		# incorrect output
	halt
back:
	addi	$r3,1
	put	$r3		# correct output 3
	bp	$r2,failed	# branch not taken b/c $r2 is zero (not positive)
	addi	$r3,1
	put	$r3		# correct output 4
	halt			# reached here: test ran successfully
correct:
	addi	$r3,1		# correct output 2
	put	$r3
	bp	$r1,back	# branch taken backwards b/c $r1 is positive
failed:
	addi	$r5,0xff
	put	$r5		# incorrect output
	halt	
	