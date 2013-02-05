	# this program tests jal by itself
	#
	# assumes addi, put work
	#
	addi	$r4,1
	addi	$r3,0xff
	jal	$r5,func
	addi	$r4,10
	put	$r3	# incorrect -- output 0xff
	halt
func:	put	$r4	# correct -- output is 1 (return point)
	halt