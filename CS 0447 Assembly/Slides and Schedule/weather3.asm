	# CS/COE 0447  Spring 2009  Example Program weather3.asm
	#
	# this is a fancy version of weather.asm, using a "computed goto".  the 
	# message addresses are loaded similarly to weather2.asm.  however, the
	# handling of the cases is done by computing a target address in a "jump
	# table" that will transfer control to the correct case.
	#
	# a jump table is a list of jumps!  we use the code to compute an index
	# into the jump table. based on the computed index, we jump into the 
	# jump table.  the jump in the table takes us to the actual place that
	# handles the case. 
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
	#
	# check range of weather code
	# a valid code is 0 to 3
	# for an invalid code, we want to just print the
	# error message.  we don't want to use the jump table!
	#
	bltz	$t0,ERR			# is code < 0?
	slti	$t1,$t0,4		# is code >= 4?  ($t1=0 when code >=4)
	beq		$t1,0,ERR		#
	#
	# now, we compute an index as a byte value into the jump table
	#
	sll		$t1,$t0,2		# compute offset into table (code * 4)
	la		$t2,J_TBL		# load base address of jump table
	add		$t2,$t2,$t1	
	# use an indirect jump - we computed the address in $t2
	jr		$t2				# jump to address in $t2
	#
	# start of jump table
	# notice that the error case is not in the jump table because
	# we checked for that already with the range check above.
	#	
J_TBL:
	j		EXT				# base point for the jump table
	j		MSG1			# reached this entry, when $t2 = J_TBL + (1*4)
	j		MSG2			# reached this entry, when $t2 = J_TBL + (2*4)
	j		MSG3			# reached this entry, when $t2 = J_TBL + (3*4)
	#
	# code to handle each case
	#
EXT:
	la		$a0,msg_0		# get address of message to print
	j		PRT				# skip MSG1,2,3,error cases
MSG1:
	la		$a0,msg_1		# print message 1
	j		PRT				# skip MSG2,3,error cases
MSG2:
	la		$a0,msg_2		# print message 2
	j		PRT				# skip MSG3,error cases
MSG3:
	la		$a0,msg_3		# print message 3
	j		PRT				# skip error case
	#
	# error case handling
	#
ERR:
	la		$a0,msg_e		# invalid code entered - error message
	#
	# print message
	#
PRT:
	li		$v0,4			# print string - $a0 holds string address
	syscall
	#
	# go back to top of loop?
	#
	bne		$t0,$0,TOP		# if code is not 0, then continue the loop

	li		$v0,10			# code==0, so exit program
	syscall
