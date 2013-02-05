	# CS 447 Spring 2009 - Exam 1, Sample problem 9
	#
	# 9. Write MIPS code that sets bits 7 and 9 (makes 
	# them 1) in $t0. The code should preserve the 
	# contents of all other bits. 
	#
	# the answer is straightforward. to set a bit, we need
	# to simply OR in an appropriate mask.  in the mask, we
	# put a 1 in the bit positions where we want to set the
	# bits and a 0 in all other bit positions.
	#
	# in binary, the mask is:
	# 0010 1000 0000b   ==>  280h
	#
	.text
	#
	# set a default value in $t0
	#
	# with this default, the correct numeric value is 
	# 0xFF0002FF after we set bits 7 and 9.
	#
	li		$t0,0xFF00007F
	########################################################
	# correct answer to question:
	########################################################
	ori		$t0,$t0,0x280
	# 
	# notice that the mask above is less than 16 bits.  what
	# would we need to do for a larger mask?  
	#
	li		$v0,10
	syscall
