# Create a word (integer) variable myVar
# Give the variable the value 20
# Print the value to the console (Run I/O window)
# Terminate the program

.data
	myVar:	.word	20
.text
	la	$t0,myVar		# get address of myVar
	lw	$t1,0($t0)		# load value at myVar
	li	$v0,1			# print integer service
	move	$a0,$t1			# put value into argument register
	syscall
	# extension
	addi	$t1,$t1,10		# add 10 to the value
	sw	$t1,0($t0)		# save the value to memory
	move	$a0,$t1
	syscall
	li	$v0,10			# terminate program service
	syscall
	