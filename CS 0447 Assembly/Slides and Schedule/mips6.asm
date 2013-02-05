	# CS 447 Spring 2009 - Ch 2 Example 6
	#	
	# this program illustrates masking and shifting to get
	# a bit from a word
	#
	# the program will extract bit 7 from a word and
	# print the value of the bit
	#
	.data
	ws:	.asciiz	" "
	nl:	.asciiz	"\n"
	.align 2
	# notice position of bit 7 for v1, when specified with byte
	v1:	.byte	0x80,0x00,0x00,0x00
	# now, notice position of bit 7 for v2 in the notation
	v2:	.word	0xFFFFFF7F
	.text
	# extract bit 7 from v1
	la		$t0,v1
	lw		$t1,0($t0)
	andi	$t1,$t1,0x80
	srl		$t1,$t1,7
	# print the resulting value (should be 1)
	li		$v0,1
	move	$a0,$t1
	syscall	
	# print a newline
	la		$a0,nl	
	li		$v0,4
	syscall
	# extract bit 7 from v2
	lw		$t1,4($t0)		# v2 is the next word after v1
	andi	$t1,$t1,0x80
	srl		$t1,$t1,7
	# print the resulting value (should be 0)
	li		$v0,1
	move	$a0,$t1
	syscall
	# terminate the program
	li		$v0,10
	syscall
