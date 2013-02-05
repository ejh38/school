	# CS/COE 0447  Spring 2009  Example Program weather2.asm
	#
	# this is a slightly simpler version of weather.asm.  this time, the program
	# loads the address to print inside the if-else statements.  a single print
	# point does the actual printing of the string. 
	# 
	# to run: enter a number 1-3 to select the current weather or 0 to exit
	#
	.data
	prompt:	.asciiz		"Enter a code for the weather (0 to exit, 1-3)?\n"
	msg_0:	.asciiz		"Bye! Try Hawaii!\n"
	msg_1:	.asciiz		"It is cloudy in Pittsburgh today!\n"
	msg_2:	.asciiz		"It is flurrying in Pittsburgh today!\n"
	msg_3:	.asciiz		"It is snowing in Pittsburgh today!\n"
	msg_e:	.asciiz		"You must have the wrong city!! (Wrong code entered.)\n"
	.text
	# do-while loop. TOP is the entry point in the loop.
TOP:
	la		$a0,prompt		# print prompt for a weather code
	li		$v0,4
	syscall
	li		$v0,5			# get weather code
	syscall
	move	$t0,$v0			# save returned code
	bne		$t0,$0,MSG1		# code is not 0, so check 1, 2, 3, or error
	la		$a0,msg_0		# get address of message to print
	j		PRT				# skip MSG1,2,3,error cases
MSG1:
	addi	$t1,$t0,-1		# comparison whether code == 1
	bne		$t1,$0,MSG2		# code is not 1, so check 2 and 3 or error
	la		$a0,msg_1		# print message 1
	j		PRT				# skip MSG2,3,error cases
MSG2:
	addi	$t1,$t0,-2		# comparison whether code == 2
	bne		$t1,$0,MSG3		# code is not 2, so check 3 or error
	la		$a0,msg_2		# print message 2
	j		PRT				# skip MSG3,error cases
MSG3:
	addi	$t1,$t0,-3		# comparison whether code == 3
	bne		$t1,$0,ERR		# code is not 3, so an error
	la		$a0,msg_3		# print message 3
	j		PRT				# skip error case
ERR:
	la		$a0,msg_e		# invalid code entered - error message
PRT:
	li		$v0,4			# print string - $a0 holds string address
	syscall
	bne		$t0,$0,TOP		# if code is not 0, then continue the loop
	li		$v0,10			# code==0, so exit program
	syscall
