# implementation of strlen as a function
# strlen function takes the string address as a parameter in $a0
# strlen returns the length of that string in $v0

	.data
name:	.asciiz		"123"

	.text
main:
	la		$a0, name		# taking the address of that string into $a0

	# parameters are all set, so we can call that function
	jal		strlen			# calls strlen	

	# at this point, strlen should return the string length in $v0

	# print the length
	add		$a0, $v0, $0
	li		$v0, 1
	syscall

	# exit 
	li		$v0, 10
	syscall

# this is the function implementation
# input: $a0 = contains the address of the string
# output: $v0 = contains the length of the string
strlen:
	add		$t0, $a0, $0	# $t0 contains the address
	li		$t3, 0		# $t3 is the running counter to find the length

loop:
	lb		$t1, ($t0)		# loads one charactar from the current string index
	addi		$t0, $t0, 1		# *** REMEMBER: String is an array of bytes ***
	addi		$t3, $t3, 1		# increment the counter
	bne		$t1, $0, loop	# check if the byte is a NULL charactar (0)

	# so, we have found NULL at the end of the string

	subi	$t3, $t3, 1			# fixup: because we have over-counted the length by +1

	# ok, now we have the length in $t3 
	add		$v0, $t3, $0	# because, we agreed to return the length in $v0 :(
	jr		$ra			# go back to the caller



