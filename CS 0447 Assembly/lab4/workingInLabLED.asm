# From Lab 4, (feb 6)
# playing with the keyboard and LED display
# LED colors: 00 - black, 01 - red, 10 - yellow, 11 - green


.data
	A:		.word 4

.text
	li		$t0, 0xFFFF0008
	li		$t1, 0xFF						# 11 11 11 11 <=> 0xFF, and we want four green LEDs
	sw		$t1, 0($t0)
	
	li		$t1, 0xDB
	addi	$t0, $t0, 4						# move $t0 over by the one word (4 bytes)
	sw		$t1, ($t0)
	
	li		$v0, 10
syscall