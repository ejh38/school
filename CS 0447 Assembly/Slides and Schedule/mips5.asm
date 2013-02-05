	# CS 447 Spring 2009 - Ch 2 Example 5
	#
	# this program illustrates memory endianness
	#
	.data
	ws:		.asciiz	" : "
	nl:		.asciiz "\n"
	.align 2	# align x ==> align memory to 2^x (2^2 is word)
	# numbers are shown in big endian and little endian
	# big endian: least significant byte is at highest address
	# lit endian: least significant byte is at lowest address
	# MARS is little endian on x86, so the 2nd number is right
	buf:	.byte	0, 0, 0, 1, 2, 0, 0, 0
	#
	.text
	# get address of buffer 
	la	$t0,buf
	# print 1st integer
	lw	$a0,0($t0)		# loading 1st integer as a word
	li	$v0,1			# print	integer
	syscall
	# print a space
	la	$a0,ws			# address of white space
	li	$v0,4			# print string
	syscall
	# print each byte for 1st integer, starting at low address
	lb	$a0,0($t0)		# lowest address  byte 0
	li	$v0,1			# print integer
	syscall
	lb	$a0,1($t0)		# byte 1
	li	$v0,1			# print integer
	syscall
	lb	$a0,2($t0)		# byte 2
	li	$v0,1			# print integer
	syscall
	lb	$a0,3($t0)		# highest address  byte 3
	li	$v0,1
	syscall
	# print on next line
	la	$a0,nl
	li	$v0,4
	syscall
	# print 2nd integer
	lw	$a0,4($t0)		# load 2nd integer as word
	li	$v0,1			# print integer
	syscall
	# print white space
	la	$a0,ws			# get address of whitespace string
	li	$v0,4			# print string
	syscall
	# print each byte for 2nd integer, starting at low address
	lb	$a0,4($t0)		# lowest address  byte 0
	li	$v0,1			# print integer
	syscall
	lb	$a0,5($t0)		# byte 1
	li	$v0,1			# print integer
	syscall
	lb	$a0,6($t0)		# byte 2
	li	$v0,1			# print integer
	syscall
	lb	$a0,7($t0)		# highest address  byte 3
	li	$v0,1			# print integer
	syscall
	# terminate program
	li	$v0,10
	syscall
