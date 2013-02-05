	# this program checks the put instruction
	#
	# this assumes you passed the addi.asm check
	# this program is the same as addi, except it has puts
	#
	addi	$r0,1	# value is 1
	put	$r0
	addi	$r0,2	# value is 1+2=3
	put	$r0
	addi	$r0,3	# value is 3+3=6
	put	$r0
	# check sign extend
	addi	$r0,0xfe # value is 6+(-2)=4
	put	$r0
	addi	$r0,4	# value is 4+5=9
	put	$r0	
	halt		# you can remove this and it should work