.data
	neg:	.asciiz "It is negative"
.text
	li $t1, -5
	slt $t0, $t1, $0
	beq $t0, 1, nega
	j exit
	
nega:
	la $a0, neg
	li $v0, 4
	syscall




exit:
	li $v0, 10
	syscall