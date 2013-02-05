# From Lab 4, (feb 6)
# playing with the keyboard and LED display
# LED colors: 00 - black, 01 - red, 10 - yellow, 11 - green


.data
	A:		.word 4

.text
	li		$t0, 0xFFFF0008
	# want GGGG RRRR YYYY RRRR
	# stored as RRRR YYYY RRRR GGGG
	li		$t1, 0x55AA55FF				# 01 01 01 01   10 10 10 10   01 01 01 01   11 11 11 11 11				
	li		$t0, 0
	li		$t3, 4
	
loop_start:
	add		$a0, $t0, $zero
	add		$a1, $t1, $zero
	jal		drawPattern
	
	addi	$t0, $t0, 32				# skip words
	
	addi	$t2, $t2, 1
	
	beq		$t2, $t3, exit_the_loop
	
	j		loop_start
	
	
exit_the_loop:	
	
	li		$v0, 10
syscall									# exit

drawPattern:
	# arguments: (address to write pattern, bitpattern to draw)
	sw		$a1, ($a0)
	jr		$ra