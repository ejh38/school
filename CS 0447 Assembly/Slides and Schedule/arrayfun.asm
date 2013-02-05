	# CS 447 - Spring 2011 - Example of functions and arrays with numbers
	#
	# for an array, sum all numbers in the range [x,y]
	#
	.data
	arry:	.word	10,20,9,40,-10,-20,-100,50,90,0,1,2,3,4,5
	.text
	la	$a0,arry	# array of array
	li	$a1,15		# 15 elements in array
	addi	$a2,$0,-10	# low number to count
	addi	$a3,$0,9	# high number to count
	jal	_count_range
	move	$a0,$v0		# save return value
	li	$v0,1		# print integer service
	syscall
	li	$v0,10
	syscall
	
_count_range:
	# this function counts numbers in an array between [x,y]
	# args: $a0 holds address of array
	#	$a1 holds the number of elements in the array
	#	$a2 holds the value x
	#	$a3 holds the value y	
	# save the argument registers $a0, $a1, and $ra, which are modified
	move	$s0,$a0
	move	$s1,$a1
	move	$s5,$ra	
	# initialize loop variable
	li	$s2,0		# the total count
	move	$s3,$a1		# $s2 holds element count
	sll	$s3,$s3,2	# multiply by 4 to get byte offset
	move	$a1,$a2		# call to _cmp expects $a1 to be low value
	move	$a2,$a3		# call to _cmp expects $a2 to be high value
_count_range_loop:
	add	$s4,$s0,$s3	# address of element
	lw	$a0,0($s4)	# get the element value
	jal	_cmp
	add	$s2,$s2,$v0	# returns 0 if outside range, otherwise element value
	addi	$s3,$s3,-4	# decrement index variable
	bgez	$s3,_count_range_loop
	# function epilogue - exit the function
	move	$v0,$s2		# move count to return register
	# restore the arg registers to preserve them
	move	$a3,$a2		# $a2 holds $a3
	move	$a2,$a1		# $a1 holds $a2
	move	$a1,$s1		# $s1 holds $a1
	move	$a0,$s0		# $s0 holds $a0
	move	$ra,$s5
	jr	$ra
	
_cmp:
	# this function compares whether a number is a range [x,y]
	# args: $a0 holds the number to compare
	# 	$a1 holds the low range value x
	#	$a2 holds the high range value y
	# returns: $v0 is 0 if outside range, otherwise $v0 is $a0
	li	$v0,0
	blt	$a0,$a1,_cmp_exit	# exit if $a0<$a1, returning 0
	bgt	$a0,$a2,_cmp_exit	# exit if $a0>$a2, returning 0
	move	$v0,$a0			# must be $a1<=$a0<=$a2, returning $a0
_cmp_exit:
	jr	$ra
	
	