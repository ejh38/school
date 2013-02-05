# Zach Sadler
# Lab 3 part 2
# Takes in an input string, then switches the case
# (up -> low, low -> up) of the individual characters.
# Uses $t0 for the (working) input string address,
# $t1 for the working byte, $t2 for current slt/beq
# $t3 for temporary comparison (of A, a, Z, z)

.data
	# some_string is used for the input string
    some_string:	.space 64
    string1:		.asciiz "Please enter your string:\n"
    string2:		.asciiz "Here is the output: "
  
.text
    li		$v0, 4				# 4 is the syscall for print string
    la		$a0, string1
syscall

    li		$v0, 8				# 8 is the syscall for read string
    li		$a1, 64				# 63 total characters to be read in
    la		$a0, some_string
syscall

    # initialization before loop
    la		$t0, some_string	# store the address of the input to $t0
    
loop:
    
    # need to set less than 0x41 (for A) and 0x5A (for Z)
    # similarly, 0x61 (for a) and 0x7a (for z)
    
    lb		$t1, 0($t0)			# load next byte poop
    addi	$t0, $t0, 1			# increment $t0 (to prepare for next byte)
    beq 	$t1, $0, exit		# if you reach the null byte at the end of the string, then exit
    
    li		$t3, 0x41			# load with value of A to prep for slt
    slt		$t2, $t1, $t3		# see if the byte is less than A
    beq		$t2, 1, loop		# if so, then just go back to top of loop

    li		$t3, 0x5B			# load with value of Z + 1 to prep for slt
    slt		$t2, $t1, $t3		# less than Z + 1 => A to Z (inclusive
    beq		$t2, 1, up_to_low	# if between A and Z, go to up_to_low
    
    li		$t3, 0x7B			# load with value of z + 1 to prep for slt
    slt		$t2, $t1, $t3		# less than z + 1 => z to a (inclusive)
    beq		$t2, 1, low_to_up	# if between a and z, go to low_to_up
    

    j	loop
    
up_to_low:
    addi	$t1, $t1, 0x20
    sb		$t1, -1($t0)
    j 	loop
    
low_to_up:
    subi	$t1, $t1, 0x20
    sb		$t1, -1($t0)
    j	loop
         
exit:

    li		$v0, 4			# Print Here is the output: 
    la		$a0, string2
syscall

    li		$v0, 4
    la		$a0, some_string
syscall

