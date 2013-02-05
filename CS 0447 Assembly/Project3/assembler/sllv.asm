	# a simple test of sllv
	#
	# assumes addui, addi, put, and halt work
	#
	addui	$r0,0x22
	addi	$r2,1
	sllv	$r0,$r2		# use $r2 to make sure we're shifting by contents!
	put	$r0		# output 0x44
	halt