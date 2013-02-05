	# CS 447 Spring 2009 - Exam 1, Sample problem 8
	#
	# 8. Write MIPS code that prints "The bit is 0" 
	# when bit 15 in $t0 is 0 and prints "The 
	# bit is 1" when bit 15 in $t0 is 1.
	#
	# mips6.asm lecture example is similar, except the
	# answer to this problem needs a little control
	# flow and printing of messages.
	#
	.data
	bit0:	.asciiz		"The bit is 0\n"
	bit1:	.asciiz		"The bit is 1\n"
	#
	.text
	# set a default value in $t0
	#li		$t0,0x000F7F00
	lui		$at, 0x000F
	ori		$t0, $at, 0x8F00
	# 000F7F00
	# 0 0 0 15 7 15 0 0
	# 0000 0000 0000 1111 0111 1111 0000 0000
					#	  ^
	# you might also try the number below
	# (comment line 17, uncomment line 20)
	#li		$t0,0x00008000
	#				1000 0000 0000 0000
	#
	andi	$t1,$t0,0x8000
	srl		$t1,$t1,15
	beq		$t1,$0,L0
	la		$a0,bit1
	j		L1
L0:
	la		$a0,bit0
L1:
	li		$v0,4
	syscall
	li		$v0,10
	syscall
