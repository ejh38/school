	# CS 447 Spring 2009 - Exam 1, Sample problem 16
	# 
	# 16. Write MIPS code that prompts the user to enter 
	# two numbers, adds the numbers, and prints the result. 
	# The prompts should be "Number 1?" and "Number 2?". 
	# When the code prints the number, it should print 
	# "The result is X", where "X" is the sum. 
	#
	.data
	num1:	.asciiz		"Number 1?\n"
	num2:	.asciiz		"Number 2?\n"
	res:	.asciiz		"The result is "
	.text
	# 
	##########################################################
	# answer is below
	##########################################################	
	#
	# print prompt for number 1
	li		$v0,4
	la		$a0,num1
	syscall
	# read number 1 from user
	li		$v0,5
	syscall
	move	$t0,$v0		# save read value
	# print prompt or number 2
	li		$v0,4
	la		$a0,num2
	syscall
	# read number 2 from user
	li		$v0,5
	syscall
	# add the two numbers
	add		$t0,$t0,$v0
	# print the result message
	li		$v0,4
	la		$a0,res
	syscall
	# print the result
	li		$v0,1
	move	$a0,$t0
	syscall
	###########################################################
	# end of answer
	###########################################################
	li		$v0,10
	syscall