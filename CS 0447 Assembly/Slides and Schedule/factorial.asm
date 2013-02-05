	# CS/COE 0447 Spring 2011 - Example of function recursion
	#
	# this program computes 3! (factorial of 3) with recursion.
	# it illustrates how to set up the procedure stack
	#
	.text
	li	$a0,5			# compute 3!
	jal	_fact
	move	$a0,$v0			# get result
	li	$v0,1			# print integer
	syscall
	li	$v0,10
	syscall

	#
	# fact(arg) - computes factorial of arg (arg!)
	#	argument is passed in $a0
	#   stack frame:
	#
	#       | ...high address... |
	#       |--------------------|
	#       |                    |
	#       |--------------------|
	#       |  return address    |  +4
	#       |--------------------|  
	#  $sp->|       saved $s0    |  +0
	#       |--------------------|
	#       |  ...low address... |
	#		
	#	
_fact:
	# prologue to procedure
	addi	$sp,$sp,-8		# push space for activation frame
	sw	$s0,0($sp)		# save $s0, which we use
	sw	$ra,4($sp)		# save return address
	# start of actual procedure work
	move	$s0,$a0			# get argument ($a0)
	li	$v0,0x1			# 1
	beq	$s0,$v0,_fact_exit	# end of recursion (f==1?)
	addi	$a0,$s0,-1		# f /= 1, so continue. set up arg(f-1)
	jal	_fact			# recursive call 
	mult	$v0,$s0			# multiply
	mflo	$v0			# return mul result
_fact_exit:
	# epilogue to exit procedure
	lw	$ra,4($sp)		# restore $ra
	lw	$s0,0($sp)		# restore $s0
	addi	$sp,$sp,8		# pop activation frame
	jr	$ra			# return


	
