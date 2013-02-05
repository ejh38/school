# $a0 used for address
# $a1 used for bitpattern (one word long)
.data
	ok:		.asciiz	"The LED pattern matches."
	not_ok:	.asciiz "The LED pattern doesn't match!"
.text
# 0xFFFF0008 start of memory addresses for LED	
	li		$a0, 0xFFFF0008
	li		$a1, 0x7EF965BD
	jal 	drawPattern
	jal		getPattern
	bne		$a1, $v0, else
	la		$a0, ok
	j end
else:
	la		$a0, not_ok
end:
	li		$v0, 4
	syscall
	li		$v0, 10
	syscall
drawPattern:
	sw		$a1, ($a0)
	jr		$ra
getPattern:
	lw		$v0, ($a0)
	jr		$ra
disruptPattern:
	