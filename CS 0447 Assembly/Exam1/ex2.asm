# Swapping between A and B
# using address of both A and B

.data
A: 	.word	0xdeadbeef
B:	.word 	0xba5eba11

.text
# step 1: load A into $t2
la	$t0, A				# A's address loaded into $t0
lw	$t2, 0($t0)			# load content of A into $t2, here as $t0 is pointing to A itself, we use offset of 0

# step 2: load B into $t3
la	$t0, B				
lw	$t3, 0($t0)

# step 3: store $t3 (which is B) into A
la	$t0, A
sw	$t3, 0($t0)			# storing $t3 into the content of A

# step 4: store $t2 (which is A) into B
la	$t0, B
sw	$t2, 0($t0)			# storing $t2 into the content of B

