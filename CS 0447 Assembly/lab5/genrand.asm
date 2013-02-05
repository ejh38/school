# generate 10 random numbers in the range 0 - 30
.data
A_str:	.asciiz	" "

.text
main:
li	$t2, 0		# running counter
li	$t3, 10		# final count

# initialize the random number generator
jal	randinit

LOOP_BODY:
li	$a0, 30		# upper bound of the range
jal	getrandomnumber	
# v0 has the random number

# print the number with the space
move	$a0, $v0
li	$v0, 1
syscall

la	$a0, A_str
li	$v0, 4
syscall

addi	$t2, $t2, 1
beq	$t2, $t3, DONE_PRINTING

j	LOOP_BODY		
		
DONE_PRINTING:		
li	$v0, 10
syscall
		
				
randinit:
# preemble
subi	$sp, $sp, 8
sw	$s0, 0($sp)
sw	$ra, 4($sp)

# get the system time
li	$v0, 30
syscall
# system time (64bits) will be in a1:a0... take the lower half (i.e., a0)
move	$s0, $a0

# set the seed and the id
move	$a1, $s0		# seed
li	$a0, 1		# id
li	$v0, 40
syscall

# postemble
lw	$s0, 0($sp)
lw	$ra, 4($sp)
addi	$sp, $sp, 8

jr	$ra

# takes a0 - upper bound 
# returns v0 as the random number 
getrandomnumber:
# pre
subi	$sp, $sp, 8
sw	$s0, 0($sp)
sw	$ra, 4($sp)

# 
move	$s0, $a0	# upper bound

li	$a0, 1		# id
move	$a1, $s0	# upper bound
li	$v0, 42
syscall
# a0 has the random number
move	$v0, $a0

# post
lw	$s0, 0($sp)
lw	$ra, 4($sp)
addi	$sp, $sp, 8

jr	$ra
