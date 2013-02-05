.data
	num1:	.asciiz		"Number 1?\n"
	num2:	.asciiz		"Number 2?\n"
	res:	.asciiz		"The result is "
.text
	li		$v0, 4
	la		$a0, num1
	syscall
	
	li		$v0, 5
	syscall
	
	move	$t0, $v0
	
	li		$v0, 4
	la		$a0, num2
	syscall
	
	li		$v0, 5
	syscall
	
	move	$t1, $v0
	
	
	li		$v0, 4
	la		$a0, res
	syscall
	
	add		$a0, $t0, $t1
	
	li		$v0, 1
	syscall