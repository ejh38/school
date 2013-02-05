	# a simple example of functions
	#
	# this code implements the C:
	# main() {
	#   int x=strawberry(10);
	#   print(x);
	# }
	# int strawberry(int x) {
	#   int y = poptart(x);
	#   return y;
	# }
	# int poptart(int x) {
	#   int z = frosting();
	#   z = z + x;
	#   return z;
	# }
	# int frosting(void) {
	#   // return random number - not shown; see below.
	# }
	#
	
	.text
	# program entry point
	li	$a0,10		# $v0=strawberry(10)
	jal	_strawberry
	move	$a0,$v0		# move return value for printing it
	li	$v0,1		# print integer service
	syscall
	li	$v0,10		# halt program service
	syscall
	
_strawberry:
	addi	$sp,$sp,-4	# non-leaf, so push AR for saving $ra
	sw	$ra,0($sp)	# save $ra
	jal	_poptart	# $v0=poptart($a0)
	lw	$ra,0($sp)	# restore $ra
	addi	$sp,$sp,4	# pop frame
	jr	$ra		# return 
	
_poptart:
	addi	$sp,$sp,-8	# need to save both $ra (non-leaf) and $a0 (clobbered)
	sw	$ra,4($sp)	# save $ra to AR
	sw	$a0,0($sp)	# save $a0 to AR
	jal	_frosting	# $v0=frosting()
	lw	$a0,0($sp)	# restore $a0
	add	$v0,$a0,$v0	# $v0=$v0+$a0
	lw	$ra,4($sp)	# restore $ra to return
	addi	$sp,$sp,8	# pop frame
	jr	$ra		# return
	
_frosting:
	# don't save anything: this is a leaf function and it doesn't use any regs
	# that the calling convention says must be saved in the callee. 
	li	$v0,30		# get time to give pseudorandom ID
	syscall
	li	$v0,42		# random int range [0,high]
	li	$a1,100		# limit upperbound on random number to 100
	syscall
	move	$v0,$a0
	jr	$ra