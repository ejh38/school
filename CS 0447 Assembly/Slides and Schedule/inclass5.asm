	# in class example for simple procedures
	# write two procedures:
	#     print(str) -- prints the string str
	#     hello(n) -- prints "Hello World!" a total of n times on separate lines
	.data
m_hello:	.asciiz		"Hello World!"
nl:			.asciiz		"\n"

	# text entry point
	.text
	# how many times should this print "Hello World"?
	li		$a0,2
	jal		hello_n
	li		$a0,0
	jal		hello_n
	li		$a0,3
	jal		hello_n
	li		$v0,10
	syscall
	
	#
	# print(s) function
	#   args: $a0 holds the address of asciiz string to print
	#   ret: none
	#   uses: $v0 (destroyed!)
	#   
print:	
	li		$v0,4
	syscall
	jr		$ra
	
	#
	# hello(n) function
	#   args: $a0 holds the number of times (n) to print
	#   ret: none
	#   uses $s0 (preserved), $s1 (preserved), $v0 (destroyed)
	#
hello_n:
	move	$s0,$ra		# save return address
	move	$s1,$a0		# preserve value in argument register

	# while (n>0) { call hello; n = n - 1; }
hello_n_loop:			
	beq		$s1,$0,hello_n_exit
	la		$a0,m_hello	# set argument for print
	jal		print
	la		$a0,nl		# print a newline between each print
	li		$v0,4
	syscall
	addi	$s1,$s1,-1
	j		hello_n_loop

hello_n_exit:
	jr	$s0
	
	
	
