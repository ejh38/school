	# CS 447 Spring 2009 - Exam 1, Sample problem 6
	#
	# Write MIPS code that does the following:
	# F = A + (((B - C) + D) - E)
	# Assume:
	# $t0 has A
	# $t1 has B
	# $t2 has C
	# $t3 has D
	# $t4 has E
	# $t5 will have F
	#
	# so, we're really doing the computation:
	# $t5 = $t0 + ((($t1 - $t2) + $t3) - $t4)
	#
	.data
	msg:	.asciiz		"The answer is: "
	nl:		.asciiz		"\n"
	.text
	#
	# let's set some default values for A, B, C, D, and E
	li	$t0,10
	li	$t1,20
	li	$t2,30
	li	$t3,40
	li	$t4,50
	# with these values, the numeric result should be:
	# 10 + (((20-30) + 40) - 50)
	# 10 + ((-10) + 40) - 50
	# 10 + 30 - 50
	# 10 + -20
	# = -10
	#
	##################################################
	# correct MIPS code for question is on lines 37-40
	# 
	sub		$t5,$t1,$t2
	add		$t5,$t5,$t3
	sub		$t5,$t5,$t4
	add		$t5,$t5,$t0
	#
	##################################################
	# print the result to run in MARS and check ourselves
	la		$a0,msg
	li		$v0,4
	syscall
	move	$a0,$t5
	li		$v0,1
	syscall
	la		$a0,nl
	li		$v0,4
	syscall
	# terminate the program
	li		$v0,10
	syscall
	