	# CS 0447 Spring 2009 - Exam 1, Sample problem 5
	#
	.data
	msg:	.asciiz	"The answer is: "
	nl:		.asciiz	"\n"
	.text
	li		$t1,78	
	######################################################
	# correct MIPS code for question is on line 11
	#
	addi	$t3,$t1,100	
	#
	######################################################
	#
	# print the number so you can run in MARS 
	li		$v0,4
	la		$a0,msg
	syscall
	li		$v0,1
	move	$a0,$t3
	syscall
	li		$v0,4
	la		$a0,nl
	syscall
	# terminate program
	li		$v0,10
	syscall
	
