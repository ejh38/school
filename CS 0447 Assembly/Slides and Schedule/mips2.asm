	# CS 447 Spring 2009 - Ch 2 Example 2
	#
	# example as C program code
	#	int a;
	#	a = 10 + 8;
	#	printf("Sum of 10 + 8 is\n");
	#	printf("%d", a);
	# the code below carries out the above
	li		$t0,10		# $t0 is a, $t0=10
	addi	$t0,$t0,8	# $t0=10+8
	li		$v0,4		# print string service
	la		$a0,msg		# load string (address)
	syscall
	li		$v0,1		# print integer service
	add		$a0,$t0,$0	
	syscall				
	li		$v0,10		# terminate program service
	syscall				
.data
	msg:	.asciiz		"Sum of 10 + 8 is\n"
	
