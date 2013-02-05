		# CS/COE 0447 Spring 2009 - Example 11
		#
		# illustrates do-while loop
		# prints a string one character at a time
		# compare this program to mips10.asm
		#
		.data
		str:	.asciiz		"Hello World!"
		.text
		#
		la		$t0,str		# load ptr to stirng
		lbu		$a0,0($t0)	# get 1st character
		beq		$a0,$0,exit	# check for empty string!
loop:	li		$v0,11		# print character
		syscall
		addi	$t0,$t0,1	# go to the next char
		lbu		$a0,0($t0)	# get the character
		bne		$a0,$0,loop	# check for null
exit:	li		$v0,10
		syscall
