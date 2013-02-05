	.data
a:	10
b:	0
	.text
	la $r0,a
	lw $r1,$r0
loop:	add $r2,$r1
	addi $r1,-1
	bp $r1,loop
	la $r0,b
	sw $r2,$r0
	lw $r3,$r0
	put $r3,0	# answer should be 37h
	halt
	