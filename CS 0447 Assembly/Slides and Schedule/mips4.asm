	# CS 447 Spring 2009 - Ch 2 Example 3
	#
	# swap example as C program code
	#	int temp;
	#	temp=v[k];
	# 	v[k]=v[k+1];
	#	v[k+1]=temp;
	#
	# we'll print the values before and after the swap as well
	#
	# note: the example on the slide is a function - we'll talk
	# about this in a later lecture. the code below doesn't work
	# directly as a function.
	#
	# assume:
	# 	 $a0 holds the starting (base) address of array v
	#	 $a1 holds the integer k
	#
	# traditionally, the "data segment" comes before the text segment
	# the "data" directive indicates declaration of data locations
	.data
whitespace:	.asciiz	" "
	# declare an array of ten integers (words)
array_v:	.word	0,10,20,30,40,50,60,70,80,90
	#
	# the "text" directive indicates that code comes next
	.text
	# set up arguments -- swap elements 4 and 5 in array_v
	la	$a0,array_v
	li	$a1,4		
	# compute a word offset from integer k
	sll	$t0,$a1,2
	add	$t1,$a0,$t0
	# load array elements v[k] and v[k+1]
	lw	$t3,0($t1)
	lw	$t4,4($t1)
	# print the array elements before the swap with whitespace between
	li	$v0,1
	move	$a0,$t3
	syscall
	li	$v0,4
	la	$a0,whitespace
	syscall
	li	$v0,1
	move	$a0,$t4
	syscall
	li	$v0,4
	la	$a0,whitespace	# ws between before & after swap
	syscall
	# now, do the actual swap operation
	sw	$t4,0($t1)
	sw	$t3,4($t1)
	# reload the swapped values so we can print them (checking that
	# our swap, which went through memory, actually worked)
	lw	$t3,0($t1)
	lw	$t4,4($t1)
	# print the array elements after the swap with whitespace between
	li	$v0,1
	move	$a0,$t3
	syscall
	li	$v0,4
	la	$a0,whitespace
	syscall
	li	$v0,1
	move	$a0,$t4
	syscall
	# terminate the program
	li		$v0,10
	syscall				
	
	
