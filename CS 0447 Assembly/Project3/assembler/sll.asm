	# this program tests shift left
	#
	# this program assumes you've passed addi.asm, addui.asm, put.asm
	#
	addi	$r0,0x11
	sll	$r0,0		# should not shift
	put	$r0		# correct output is 0x0011
	sll	$r0,1		# try moving one bit to left
	put	$r0		# correct output is 0x0022
	li	$r0,0x22
	addi	$r2,1
	sllv	$r0,$r2		# shift by a register amount
	put	$r0		# correct output is 0x0044
	sll	$r0,4		# shift by more than one bit
	put	$r0		# correct output is 0x0440
	addi	$r3,4
	sllv	$r0,$r3		# shift by more than one bit in register
	put	$r0		# correct output is 0x4400
	sll	$r0,4		# shift "beyond" left side
	put	$r0		# correct output is 0x4000
	sll	$r0,8
	put	$r0		# correct output is 0x0000
	halt
	
