#CS/COE 447 Lab 4 Part 2 Template

#This template includes testing code, but also has some support code to check
#for a common error.
# LED colors: 00 - black, 01 - red, 10 - yellow, 11 - green
#8 E	9 0 5 D
#1000 1110  1001 0000 1100 0110 1101
# B 7 9 F 5 6 D
#1110 0111 1001 1111 0101 0110 1101 1011
.text:
        #This is the beginning of the testing code. 

		# you may put additional instructions to calculate the addresses and bit patterns
		li $a0, 0xFFFF0010		# replace your_address with the actual address
        li $a1, 0x7EF965BD	    # replace your_pattern with the actual pattern
        li $a2, 7               #Draw the pattern 7 times vertically.
        jal drawRepeatedPattern #Jump and link to drawRepeatedPattern.

		li $a0, 0xFFFF003C		# replace your_address with the actual address
        li $a1, 0x8E096C4D	    # replace your_pattern with the actual pattern
        li $a2, 7               #Draw the pattern 7 times vertically.
        jal drawRepeatedPattern #Jump and link to drawRepeatedPattern.

		# do not alter 
        la $a0, successfulQuitMessage
        li $v0, 4
        syscall

        li $v0, 10             #Exit syscall
        syscall

        #This is the end of the testing code.

#========================================
# * Place your drawPattern code here    *
#========================================
    drawPattern:
        sw		$a1, ($a0)
		jr		$ra



#========================================
# * DO NOT ALTER THIS NEXT LINE         *
j returnErrorHappened
#========================================




#========================================
# * Place drawRepeatedPattern code here *
#========================================
    drawRepeatedPattern:
    	move	$s0, $ra
    loop:
    	beq		$a2, $0, exit
    	jal		drawPattern
    	addi	$a0, $a0, 32
    	subi	$a2, $a2, 1
    	j loop
    exit:
    	move	$ra, $s0
    	jr $ra
        



#========================================
# * DO NOT ALTER THIS NEXT LINE         *
j returnErrorHappened
#========================================


returnErrorHappened:
    #If this code is executed, your function did not properly return.
    la $a0, badReturnMessage
    li $v0, 4
    syscall
    li $v0, 10
    syscall

.data:
    badReturnMessage:       .asciiz "A function did not properly return!"
    successfulQuitMessage:  .asciiz "The program has finished."

