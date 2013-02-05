# reversing a string without using an extra character buffer
# we will have two pointers: one at the start and the other at the end of the string
# we will swap bytes at these pointers
# then we will increment the beginning pointer and decrement the end pointer
# then we will swap again
# we do this until these pointers are equal or cross each other (i.e., end pointer gets equal or smaller than start pointer)

.data
A_string: 		.asciiz		"I will reverse this string"

.text
# step 1: get the length of the string into $t4
la	$t0, A_string
li	$t2, 0		# NULL 
li	$t4, 0		# $t4 will contain the length

LOOP1:
lb	$t1, 0($t0)
# if NULL byte found, goto FOUND_NULL_BYTE
beq	$t1, $t2, FOUND_NULL_BYTE
# else
addi	$t4, $t4, 1	# increment byte counter
addi	$t0, $t0, 1 	# increment address pointer
j 	LOOP1		# LOOP

FOUND_NULL_BYTE:
# we have $t4 the number of bytes (length of the string)

# step 2: do the reverse using the length of the string

# fix the start pointer ($t0)
la	$t0, A_string		# $t0 points to the starts of the string as usual
# fix the end pointer ($t1)
add	$t1, $t0, $t4		# at this point, $t1 points to the null byte
subi	$t1, $t1, 1		# at this point, $t1 points to the last character of the string

LOOP2:
# swap the bytes at $t0 and $t1 (using $t3 and $t4 as the intermediate registers)
lb	$t3, 0($t0)
lb	$t4, 0($t1)
sb	$t4, 0($t0)
sb	$t3, 0($t1)

# increment start pointer and decrement end pointer
addi	$t0, $t0, 1
subi	$t1, $t1, 1

# if they are equal or crossed each other, we are done
ble	$t1, $t0, END_OF_REVERSE
# else
j 	LOOP2

END_OF_REVERSE:
# we are done
# print the string
la	$a0, A_string
li	$v0, 4
syscall

