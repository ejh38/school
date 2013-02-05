# each of the four LEDs is a set addressed as a byte

.text
li	$a0, 0xFFFF0008		# address of first four pixels
li	$a1, 0x01				# 00 00 00 01
sb	$a1, 0($a0)			# lit up first four pixels according to the bit pattern 

li	$a0, 0xFFFF0009		# address of second four pixels
li	$a1, 0x03				# 00 00 00 11
sb	$a1, 0($a0)			# lit up these four pixels according to the bit pattern 

# each row has 128 pixels. So we need 256 bits (32 bytes) to describe them. 
# so, there are 32 sets of pixels (each set has four pixels)
# let's lit up the last set of pixels from the first row
li	$a0, 0xFFFF0008
addi	$a0, $a0, 31			# address of the last set of pixels
li	$a1, 0x02				# 00 00 00 10
sb	$a1, 0($a0)			
