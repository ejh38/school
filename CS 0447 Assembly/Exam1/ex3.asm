# Swapping between A and B
# using address of A only ($t0 will always point to A)

.data
A: 	.word	0xdeadbeef		# <--- $t0
B:	.word 	0xba5eba11

.text
# step 1: load address of A into $t0
la	$t0, A				# $t0 has A's address now

# we will keep $t0 unchanged
# so, 0($t0) points to A
# and, 4($t0) points to B

# step 2: load A into $t2
lw	$t2, 0($t0)

# step 2: load B into $t3
lw	$t3, 4($t0)			# load content of B into $t3, here as $t0 is pointing to A, we use offset of 4 to get to B's address from A's address

# step 3: store $t3 (which is B) into A
sw	$t3, 0($t0)

# step 4: store $t2 (which is A) into B
sw	$t2, 4($t0)

