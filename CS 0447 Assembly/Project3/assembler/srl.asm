	li	$r0,0x000f	# set $r0 t0 0x000F
	sll	$r0,12		# shift 0xf so $r0=0xF000
	put	$r0		# correct output 0xF000
	srl	$r0,4		# shift right by 4
	put	$r0		# correct output 0x0F00
	srl	$r0,4
	put	$r0		# correct output 0x00F0
	srl	$r0,4
	put	$r0		# correct output 0x000F
	halt