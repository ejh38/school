	clr	$r0
	# increment from 0 to 15: lowest hex digit will cycle from '0' to 'F'
loop0:	put	$r0		# output current value
	addi	$r0,1		# increment value by 1
	mov	$r1,$r0		# check for loop end
	addi	$r1,-16		# end of loop?
	bn	$r1,loop0
	
	# shift left four bits: 'F' will move left from one hex digit to next
	addi	$r0,-1		# make $r0 15
	li	$r2,3
loop1:	sll	$r0,4		# left shift by 4 bits
	put	$r0
	addi	$r2,-1
	bp	$r2,loop1

	li	$r0,0x8
	sll	$r0,12		# should be 0x8000
	li	$r4,0xF
	sll	$r4,12		# should be 0xF000
	li	$r2,4
loop2:	put	$r0
	mov	$r3,$r0
	and	$r3,$r4
	srl	$r3,4
	or	$r0,$r3
	srl	$r4,4
	addi	$r2,-1
	bz	$r2,loop3
	bz	$r7,loop2	# $r7 should be 0
	
loop3:	halt
	