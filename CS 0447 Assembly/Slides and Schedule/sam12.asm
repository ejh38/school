	# CS 447 Spring 2009 - Exam 1, Sample problem 12
	#
	# 12. Write MIPS code that prints the 32-bit value 
	# in $t0 as a hexadecimal number.  Hint: your program 
	# should use a table lookup to convert to characters
	# for the hex number.  You might find a loop useful 
	# to extract 4 bit quantities from $t0, which are then 
	# converted into hex characters.
	#
	#######################################################
	#
	# we do this with a small loop that iterates over the
	# 4-bit chunks in $t0.  we extract each chunk, do a lookup
	# into a digit-to-hex table, write the result into a 
	# buffer, and continue. when done, the buffer will be a 
	# string of hex characters, which we can print. when we 
	# reach the end of the 32 bit number (8 chunks of 4 
	# bits), we print the string.
	#
	# the conversion of $t0 is done right to left: we extract 
	# the least significant 4-bit number from $t0 and convert
	# it.  when we're done with this number, we shift $t0 by
	# 4 to the right to do the next one. in the output 
	# string, this means we need to also work right to left 
	# because the rightmost character in the string is the 
	# least significant hex character for the
	# lowest 4-bits in $t0!
	#
	# note: we can avoid the table lookup.  we'll see how
	# when we talk about ASCII encoding of characters.
	#
	#######################################################
	#
	.data
	#
	# conversion table: 4-bit binary number to hex character.
	# to convert a binary number into a hex character, we 
	# just add the address digit_to_hex to the
	# 4-bit binary number.
	#
	digit_to_hex:	.byte	'0','1','2','3','4','5','6','7',
							'8','9','A','B','C','D','E','F'
	#
	# this is the output buffer
	# we need 9 bytes: 8 to hold the hex characters and one to
	# be a null (0) to terminate the string for printing
	#
	buf:			.byte	0,0,0,0,0,0,0,0,0
	#
	# this is the number we'll convert for printing as a 
	# string of hex characters.
	#
	.align 2
	num:			.word	0x1234ABCD
	#
	.text
	#
	# set default value for t0 (the variable "num")
	la		$t0,num
	lw		$t0,0($t0)
	##########################################################
	# correct answer is below
	#
	# note that $t3 is decrement by 1 byte each time through
	# the loop. this lets us work from the rightmost char in
	# the string to the leftmost char.
	#
	# also, note that $t1 was set to 8 so that we can do a
	# simple test against $0 to finish the loop.
	##########################################################
	#
	li		$t1,8					# 8 binary digits to convert
	la		$t2,digit_to_hex		# ptr to lookup table
	la		$t3,buf+7				# ptr to output buffer
L1:	
	andi	$t4,$t0,0xF				# extract digit
	add		$t5,$t2,$t4				# address into table
	lb		$t5,0($t5)				# table lookup
	sb		$t5,0($t3)				# set hex character in buf
	srl		$t0,$t0,4				# shift to next digit
	addi	$t3,$t3,-1				# next position in buf
	addi	$t1,$t1,-1				# loop index variable
	bne		$t1,$0,L1				# more digits?
	#
	# ok, buf now has a string for the number
	# print it to the display
	#
	la		$a0,buf
	li		$v0,4
	syscall
	#
	# terminate the program
	#
	li		$v0,10
	syscall
