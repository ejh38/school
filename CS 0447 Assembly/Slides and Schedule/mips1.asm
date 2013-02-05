	# CS 447 Spring 2009 - Ch 2 Example 1
	#
	# example as C program code
	#	int a;
	#	a = 10 + 8;
	#	printf("%d",a);
	# the code below carries out the above
	li		$t0,10		# $t0 is a, $t0=10
	addi	$t0,$t0,8	# $t0=10+8
	li		$v0,1		# print service
	add		$a0,$t0,$0	# pass value in $t0 to print
	syscall				# invoke OS
	li		$v0,10		# terminate program service
	syscall				# invoke OS
	
