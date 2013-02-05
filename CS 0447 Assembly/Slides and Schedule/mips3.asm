	# CS 447 Spring 2009 - Ch 2 Example 3
	#
	# example as C program code
	#	int a, x;
	#	printf("Number x to add?\n");
	#	sscanf("%d", x);  
	#	a = 10 + x;
	#	printf("Sum of 10 + x is\n");
	#	printf("%d", a);
	# the code below carries out the above
	#
	li		$v0,4		# print prompt
	la		$a0,x_msg
	syscall
	li		$v0,5		# get value (x)
	syscall
	move	$t0,$v0		# put x into a
	addi	$t0,$t0,10	# add 10 to x
	li		$v0,4		# print output string
	la		$a0,msg		
	syscall
	li		$v0,1		# print a
	add		$a0,$t0,$0	
	syscall				
	li		$v0,10		# terminate
	syscall				
.data
	x_msg:	.asciiz		"Number x to add?\n"
	msg:	.asciiz		"Sum of 10 + x is\n"
	
	
