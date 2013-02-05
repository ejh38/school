.text

li	$v0, 4			# Print string
la	$a0, string1
syscall

li	$v0, 5			# Read integer
syscall

add	$t1, $v0, $zero		# Store the 1st int in $t1

li	$v0, 4			# Print string
la	$a0, string2
syscall

li	$v0, 5			# Read integer
syscall

add	$t2, $v0, $zero		# Store the 2nd int in $t2

li	$v0, 4			# Print string
la	$a0, string3
syscall

add 	$a0, $t1, $zero		# Stroe the 2nd int

li	$v0, 1			# Print 1st int 
syscall

li	$v0, 4			# Print string
la	$a0, string4
syscall

add	$a0, $t2, $zero		# Setup second int

li	$v0, 1			# Print second int
syscall

li	$v0, 4			# Print string
la	$a0, string5
syscall

sub	$a0, $t1, $t2		# Do the subtraction

li	$v0, 1			# Print the result
syscall


.data
    string1:     .asciiz "What is the first value?\n"
    string2:	.asciiz "What is the second value?\n"
    string3:	.asciiz "The difference of "
    string4:	.asciiz " and "
    string5:	.asciiz " is "  