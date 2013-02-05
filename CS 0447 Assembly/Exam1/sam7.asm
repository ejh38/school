	# CS 0447 Spring 2009 - Exam 1, Sample problem 7
	#
	# 7. Write MIPS code that prints "It is negative" 
	# when the value in register $t1 is less than 0.
	#
	.data
	n:	.asciiz 	"It is negative\n"
	p:	.asciiz		"It is positive\n"
	#
	.text
	#
	# put a default value into $t1
	#
	li		$t1,-10
	#####################################################
	# correct answer to question is below
	#####################################################
	slti	$t2,$t1,0	# check if less than 0
	beq		$t2,$0,L0	# $t2==0 when $t1>=0
	la		$a0,n		# fall-thru when negative
	li		$v0,4
	syscall
	#####################################################
	# end of correct answer
	#####################################################
	#
	# although the problem didn't ask for it, here is how
	# you'd also print when the number is positive.
	#
	# note: you can be more space efficient and just load
	# the address for the strings based on the result. see
	# sam8.asm for an example.
	#
	j		L1			# jump around positive
L0:	
	# print message that number is >= 0
	la		$a0,p
	li		$v0,4
	syscall
L1:	
	# terminate the program
	li		$v0,10
	syscall
