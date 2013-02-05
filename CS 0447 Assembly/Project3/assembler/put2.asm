	# this is a better test for put (than put.asm) since it checks all four LEDs
	#
	# the test assumes addi works correctly, including sign extension
	#
	addi	$r0,0x1
	put	$r0		# output 0x0001
	addi	$r1,0x10
	put	$r1		# output 0x0010
	addi	$r2,0x7f
	addi	$r2,1	
	addi	$r2,0x7f
	addi	$r2,1
	put	$r2		# output 0x0100
	addi	$r3,0x80
	put	$r3		# output 0xFF80
	halt

	