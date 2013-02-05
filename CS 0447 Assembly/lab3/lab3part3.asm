# Zach Sadler
# Lab 3 part 3
# Take in a string, reverse each word (individually), disregarding spaces
# Then output it again
# Uses $t0 for address of the input string, $t1 for the working byte,
# $t2 for individual word length, $t3 as address for buf2, $t4 for consant (' ')
# $t5 to temporarily store word length

.data
	buf1:			.space 64
	buf2:			.space 64
    string1:		.asciiz "Please enter your string:\n"	
    string2:		.asciiz "Here is the output: "
    
.text
	li		$v0, 4				# 4 is the syscall for print string
    la		$a0, string1
syscall

    li		$v0, 8				# 8 is the syscall for read string
    li		$a1, 64				# 63 total characters to be read in
    la		$a0, buf1
syscall

	la		$t0, buf1
	la		$t3	 buf2
	# 0x20 is the ascii code for ' '
	li		$t4, 0x20
	subi	$t0, $t0, 1
mloop:			# main loop that will run until null string found
	add		$t0, $t0, $t5
	add		$t5, $0, $0			# reset $t5 to 0 
	addi	$t0, $t0, 1
	
 loop1:			
 	# inner loop to count length of words
    lb		$t1, 0($t0)			# load next bye
    beq		$t1, 0x20, reverser	# if reach ' ' then reverse
    beq		$t1, 0xa, reverser	# same with newline
    beq 	$t1, $0, exit		# if you reach the null byte at the end of the string, then exit
    
    # end of special cases, continue with normal loop
    addi	$t2, $t2, 1			# increase the length of the current string
    addi	$t0, $t0, 1			# increment $t0 (to prepare for next byte)
    addi	$t5, $t5, 1			# word length
    
    j loop1
    
 reverser:
    # logically, need a for loop to send 
    lb		$t1, -1($t0)		# load the byte at $t0 -1, since $t0 is the space
  	sb		$t1, 0($t3)			# store it into $t3
  	subi	$t0, $t0, 1			# dec $t0 to go back -> front
  	addi	$t3, $t3, 1			# inc $t3 to go front -> back 
  	subi	$t2, $t2, 1			# dec word length to go
  	beq		$t2, 0, mloop		# if length == 0, go back to mloop
  	
  	j reverser
  
exit:	
   # exit, display the reversed string	
   	sb		$0, 0($t3)
	li		$v0, 4				# 4 is the syscall for print string
    la		$a0, string2		# prints 'here is the output: '
syscall
	
	la		$a0, buf2
syscall							# prints the (reversed) string
