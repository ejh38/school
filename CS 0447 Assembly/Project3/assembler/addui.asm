	# this program checks the addui instruction
	#
	# assumes you've passed addi.asm, put.asm
	#
	addui	$r0,1
	put	$r0		# corect output 1
	addui	$r0,0xfe	# 254 but -2 when sign extended
	put	$r0		# correct output is 0xFF (255)
	