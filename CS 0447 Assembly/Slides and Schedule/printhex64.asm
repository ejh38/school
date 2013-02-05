
	.data
	num:	.word 0x8013ABFC, 0x1724EDAB
	hex:	.byte '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
	.text
	la	$t0,num			# address of the multi-bit quantity to display
	li	$t2,0xf0000000		# mask to select upper most 4 bits
	la	$t3,hex			# address of conversion table
	li	$t6,2			# number of words to print
printhex:
	lw	$t1,0($t0)		# load the word with the hex digits
	li	$t4,8			# number of times to go through loop
inner:
	and	$t5,$t1,$t2		# select upper 4 bits
	srl	$t5,$t5,28		# move bits to lower most 4 bits
	add	$t5,$t3,$t5		# address in table
	lbu	$a0,0($t5)		# character to print
	li	$v0,11			# print character service
	syscall
	addi	$t4,$t4,-1		# decrement loop count
	sll	$t1,$t1,4		# move to next lower 4 bits
	bne	$t4,$0,inner		# print hex digits for the current word
	addi	$t0,$t0,4		# go to next word 
	addi	$t6,$t6,-1
	bne	$t6,$0,printhex
	li	$v0,10
	syscall
	