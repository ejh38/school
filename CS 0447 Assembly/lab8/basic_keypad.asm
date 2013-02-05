# prints as key pressed

.data

R_str:	.asciiz	"Right Key\n"
L_str:	.asciiz	"Left Key\n"
U_str:	.asciiz	"Up Key\n"
D_str:	.asciiz	"Down Key\n"
C_str:	.asciiz	"Center Key\n"

.text

_poll:
	# check for a key press
	la	$t0,0xffff0000	# status register address	
	lw	$t0,0($t0)	# read status register
	andi	$t0,$t0,1		# check for key press
	bne	$t0,$0,_keypress
	
	j	_poll

_keypress:
	# handle a keypress to change snake direction
	la	$t0,0xffff0004	# keypress register
	lw	$t0,0($t0)	# read keypress register

	# center key
	subi	$t1, $t0, 66				# center key?
	beq	$t1, $0, center_pressed		# 

	# left key
	subi	$t1, $t0, 226				# left key?
	beq	$t1, $0, left_pressed		# 

	# right key
	subi	$t1, $t0, 227				# right key?
	beq	$t1, $0, right_pressed		# 

	# up key
	subi	$t1, $t0, 224				# up key?
	beq	$t1, $0, up_pressed			# 

	# down key
	subi	$t1, $t0, 225				# down key?
	beq	$t1, $0, down_pressed		# 

	j	_poll

right_pressed:
	la	$a0, R_str
	j	print_str

left_pressed:
	la	$a0, L_str
	j	print_str

up_pressed:
	la	$a0, U_str
	j	print_str

down_pressed:
	la	$a0, D_str
	j	print_str

center_pressed:
	la	$a0, C_str
	li	$v0, 4
	syscall
	j	_exit

print_str:
	li	$v0, 4
	syscall
	
j	_poll

_exit:
	li	$v0, 10
	syscall
