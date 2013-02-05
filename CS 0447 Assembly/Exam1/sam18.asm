	# CS 447 Spring 2009 - Exam 1, Sample problem 18
	# 
	# 18. Write MIPS code that finds and prints the 
	# smallest number in the integer array "arry".  The 
	# declaration of the array is shown below. 
	#
	.data
	.align 2
	arry: .word 100,10,3,-2,-1000,0,-50,150,-17,8
	.text 
	la		$t1,arry		# base address of array
	lw		$t0,0($t1)		# use 1st value as starting point for minimum
	li		$t2,9			# there are 9 elements remaining
	addi		$t1,$t1,4		# go to next element
L0:
	lw		$t3,0($t1)		# get  array element
	slt		$t4,$t3,$t0		# is element < current min value?
	beq		$t4,$0,L1		# no - do nothing
	move	$t0,$t3			# yes - set new current min value
L1:
	addi	$t1,$t1,4		# go to next array element
	addi	$t2,$t2,-1		# decrement index varaiable
	bne		$t2,$0,L0		# end of loop?
	#
	# print minimum value
	move	$a0,$t0	
	li		$v0,1
	syscall
	# terminate program
	li		$v0,10
	syscall