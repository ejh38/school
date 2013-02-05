# lit up every other set of four-pixels

# each of the four LEDs is a set addressed as a byte
# each row has 128 pixels. So we need 256 bits (32 bytes) to describe them. 
# so, there are 32 sets of pixels (each set has four pixels)
# let's lit up the last set of pixels from the first row

.text
li	$a0, 0xFFFF0008
li	$a1, 0x9D			# 10 01 11 01
	
	# t5 and t6 will work as a loop counter
li	$t5, 0
li	$t6, 128		# 32 bytes X 8 rows = 256, every other means we skip a set, so we have 128 sets of pixels
	
LOOP:
sb	$a1, 0($a0)

addi	$t5, $t5, 1
beq	$t5, $t6, EXIT

# otherwise, go to the next pixel bottom-right diagonal to the current one
addi	$a0, $a0, 2		# adding 32 would go to the pixel beneath, so we added one more  

j LOOP

EXIT:

