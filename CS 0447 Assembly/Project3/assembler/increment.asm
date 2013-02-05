	clr	$r0
	# increment from 0 to 15: lowest hex digit will cycle from '0' to 'F'
loop0:	put	$r0,0		# output current value
	addi	$r0,1		# increment value by 1
	mov	$r1,$r0		# check for loop end
	addi	$r1,-16		# end of loop?
	bn	$r1,loop0
	halt
	