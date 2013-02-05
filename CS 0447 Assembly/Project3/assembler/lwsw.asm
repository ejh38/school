	# tests lw and sw
	#
	# assumes addi, put and halt work
	#
	addi	$r2,1
	addi	$r4,5
	sw	$r2,$r4
	lw	$r7,$r4
	put	$r7		# correct output is 1
	addi	$r7,1
	sw	$r7,$r4
	lw	$r6,$r4
	put	$r6		# correct output is 2
	addi	$r4,1
	addi	$r6,1
	sw	$r6,$r4
	addi	$r4,1
	addi	$r6,1
	sw	$r6,$r4
	addi	$r3,6
	lw	$r7,$r3
	put	$r7		# correct output is 3
	addi	$r3,1
	lw	$r7,$r3
	put	$r7		# correct output is 4
	halt
	
