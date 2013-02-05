	li	$t0,0x40		# RED in leftmost LED for this group of 4 LEDs controlled by byte
	la	$t1,0xFFFF0008		# base address of LED display
	sb	$t0,0($t1)
	sb	$t0,32($t1)
	sb	$t0,64($t1)
	sb	$t0,96($t1)
	sb	$t0,128($t1)
	sb	$t0,160($t1)
	sb	$t0,192($t1)
	sb	$t0,224($t1)
	li	$v0,10
	syscall
