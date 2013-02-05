		# CS/COE 0447 Spring 2009 - Example 10
		#
		# illustrates a while loop
		# the loop prints a null-terminated string one
		# character at a time.
		#
		.data
		str:	.asciiz		"Hello World!"
		.text
		# load address of string to print
		la		$t0,str
		# iterate over the string
loop:	lbu		$a0,0($t0)		# load the 8-bit character
		beq		$a0,$0,exit		# check for a null
		li		$v0,11
		syscall					# print the character
		addi	$t0,$t0,1		# next character
		j		loop			# continue loop
exit:	li		$v0,10			# terminate program
		syscall
