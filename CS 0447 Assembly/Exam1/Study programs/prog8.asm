.data
	string0:	.asciiz "The bit is 0"
	string1:	.asciiz "The bit is 1"
.text
	addi $t0, $t0, 0x00008000
	sll $t0, $t0 ,16
	srl $t0, $t0, 31
	bne $t0, $0, bit1

bit0:
	la $a0, string0
	j exit
bit1:
	la $a0, string1
exit:
	li $v0, 4
	syscall
	li $v0, 10
	syscall