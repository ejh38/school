	# in class example for simple procedures
	# write two procedures:
	#   hello -- prints "Hello" and then calls "world"
	#   world -- prints "World" and returns
	.data
m_hello:	.asciiz		"Hello"
m_world:	.asciiz		"World"
nl:		.asciiz		"\n"
	.text
	jal	hello
	la	$a0,nl
	li	$v0,4
	syscall
	jal	world
	li	$v0,10
	syscall
hello:	
	move	$s0,$ra	
	la	$a0,m_hello
	li	$v0,4
	syscall
	addi	$a0,$0,' '
	li	$v0,11
	syscall
	jal	world
	move	$ra,$s0
	jr	$ra

world:
	la	$a0,m_world
	li	$v0,4
	syscall
	jr	$ra

	
	
