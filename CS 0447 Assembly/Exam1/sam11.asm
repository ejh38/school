	# CS 447 Spring 2009 - Exam 1, Sample problem 10
	#
	# 11. Write MIPS code that prints the value for 
	# bits 15, 16, and 17 in $t0.  The code should 
	# print a single integer number that corresponds
	# to the 3 digit binary number in bits 15, 16, 17.
	#
	# OK, with the other sample problems, you should have
	# a pretty good idea how to do this!
	#
	# we need to select bits 15-17 from $t0
	# shift the bits right (by 14 places)
	# put the value into $a0
	# call the OS print integer service
	#
	.text
	#
	# set a default value for $t0 to0x20000
	# the correct numeric result should be 8
	#
	li		$t0,0x8000
	sll		$t0,$t0,2
	######################################################
	# correct answer is below (other variations possible)
	######################################################
	# build a mask to select bits 15-17
	li		$a0,7
	sll		$a0,$a0,15
	# mask off the bits and shift all the way to the right
	and		$a0,$t0,$a0
	srl		$a0,$a0,15
	# print the number - notice the result is built in $a0
	li		$v0,1
	syscall
	######################################################
	# end of correct answer
	######################################################
	# terminate the program
	li		$v0,10
	syscall
	