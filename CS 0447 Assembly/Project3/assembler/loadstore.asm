	clr	$r0
	clr	$r1
	
loop0:	sw	$r0,$r0
	addi	$r0,1
	mov	$r1,$r0
	addi	$r1,-10
	bn	$r1,loop0
	
	# now load the values from memory
	addi	$r0,-1	# we incremented one past end
loop1:	lw	$r0,$r0
	put	$r0
	addi	$r0,-1
	bp	$r0,loop1
	bz	$r0,loop1

	halt

	