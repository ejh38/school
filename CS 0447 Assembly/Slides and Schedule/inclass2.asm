# write the C code below as MIPS assembly language
#
# void fun(void) {
#	int a=10,b=20,c=30;
#	a=a+10;
#	b=0;
#	c=a+b;
# }

.data
	a:	.word	10
	b:	.word	20
	c:	.word	30
.text
	la	$t0,a
	lw	$t1,0($t0)	# get a's value
	addi	$t1,$t1,10	# a=a+10
	sw	$t1,0($t0)	# store a 
	add	$t1,$0,$0	# clear $t1
	sw	$t1,4($t0)	# set b=0
	lw	$t2,0($t0)	# load a (again-we can be smarter)
	add	$t2,$t2,$t1	# c=a+b
	sw	$t2,8($t0)	# store c
	li	$v0,10		# exit
	syscall