# finding the length of a string
# we will store the length of the string in $t4
# we will traverse the string from its beginning to its end and count the number of bytes found before reaching the NULL byte

.data
A_string: 		.asciiz		"I go to PITT"		# asciiz strings have a NULL byte at the end. so, in this case, there is a 0 after the second T

.text
# initialization phase: it comes before starting the loop 
la	$t0, A_string
li	$t2, 0		# NULL 
li	$t4, 0		# $t4 will contain the length

# now here goes the loop body
LOOP1:
lb	$t1, 0($t0)

# if NULL byte found, goto FOUND_NULL_BYTE
beq		$t1, $t2, FOUND_NULL_BYTE

# else
addi	$t4, $t4, 1		# increment byte counter as we have found one more byte which is not NULL
addi	$t0, $t0, 1 	# increment address pointer so that the pointer now points to the next byte
j 		LOOP1			# jump for looping

FOUND_NULL_BYTE:
# we have $t4 the number of bytes (length of the string)
# print the value in $t4
addi	$a0, $t4, 0
li		$v0, 1
syscall


