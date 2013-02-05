	# CS 447 Spring 2009 - Exam 1, Sample problem 10
	#
	# 10. Write MIPS code that clears bits 11 and 13 
	# (makes them 0) in $t0. The code should preserve 
	# the contents of all other bits
	#
	# the answer is straightforward. to clear a bit, we need
	# to simply AND in an appropriate mask. in this case, we
	# want a 0 in the bit positions where we are clearing the
	# bits.  all other positions are 1s.  
	#
	# in binary, the mask is:
	# 1111 1111 1111 1111 1101 0111 1111 1111b
	# FFFFD7FFh
	#
	# we have to build this mask. one strategy is to use lui 
	# and ori.  another one is to simply load the 
	# corresponding negative number for the low 16 bits!  in 
	# decimal, this number is -10241.  when this value is 
	# loaded, it will be sign extended so that the upper 
	# 16 bits are all 1s. 
	#
	#
	.text
	#
	# set a default value in $t0. what's -2? 0xFFFFFFFE
	# result should be 0xFFFFD7FE
	#
	li		$t0,-2
	########################################################
	# correct answer to question:
	########################################################
	li		$t1,-10241
	# as an alternative, you can also use lui and ori, but 
	# it is less efficient. 
	# try commenting line 33 and uncommenting lines 37, 38.
	#lui		$t1,0xFFFF
	#ori		$t1,$t1,0xD7FF
	#
	and		$t0,$t0,$t1
	########################################################
	# end of correct answer
	########################################################
	# 
	# terminate the program
	li		$v0,10
	syscall
