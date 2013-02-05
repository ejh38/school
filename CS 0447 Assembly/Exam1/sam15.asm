	# CS 447 Spring 2009 - Exam 1, Sample problem 15
	# 
	# 15. Using only ori and sll instructions, put the 
	# constant 0x3FF01 into $t0. 
	#
	# we can do this by putting 0x3FF0 into $t0
	# shift value by 4
	# or with 0x01
	#
	#########################################################
	# answer is below:
	#########################################################
	ori		$t0,$0,0x3FF0
	sll		$t0,$t0,4
	ori		$t0,$t0,0x1
	#########################################################
	li		$v0,10
	syscall
