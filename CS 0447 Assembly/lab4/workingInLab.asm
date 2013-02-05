# Typed while in lab4 (Feb 6)
# Returns the string length set in name

.data
	name:	.asciiz		"Pittsburgh"
	
.text

main:
	la		$a0, name
	
	jal		strlen				# saves the return address to $ra, then jumps
	
	
	add		$a0, $v0, $0
	li		$v0, 1				# prints the length
syscall				
	
	li		$v0, 10				# exits the program
syscall

strlen:
	# loop inir
	add		$t0, $a0, $0		# $t0 contains the address
	li		$t3, 0				# $t3 is the running counter for the length


loop:
	lb		$t1, ($t0)
	# next byte to load in the next iteation
	addi	$t0, $t0, 1			# *** Remember: String is an array of 
	#incrementing the counter as we have seen one more byte
	addi	$t3, $t3, 1			# increment the counter
	bne		$t1, $0, loop		# terminating condition
	
	
	
	subi	$t3, $t3, 1
	
	add		$v0, $t3, $0
	jr		$ra	
	
	
	