	# CS/COE 0447  Spring 2009  Example Program weather4.asm
	#
	# this is a fancy version of weather.asm, using static table of pointers. 
	# similarly to weather3.asm, we'll compute an index, but this time the
	# index will be into a data table.  the data table is an array of addresses
	# for the different messages.
	#
	# also, notice that we've cleaned up the loop by moving the error case
	# outside of the actual loop body.  
	#
	# lastly, notice we do the error checking with a more direct way, using
	# a range check on the entered code.  we need this error checking because
	# we use the actual code in the array indexing calculation. 
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
	.align	2
	# array of pointers (addresses) to the messages
	d_tbl:	.word		msg_0,msg_1,msg_2,msg_3
	.text
	#
	# do-while loop. TOP is the entry point in the loop.
	#
TOP:
	la		$a0,prompt		# print prompt for a weather code
	li		$v0,4
	syscall
	li		$v0,5			# get weather code
	syscall
	move	$t0,$v0			# save returned code
	# do error checking before computing offset 
	# check: 0 <= code <= 3
	bltz	$t0,ERR			# is code < 0?
	slti	$t1,$t0,4		# is code < 4?  $t1=0 when code >= 4
	beq		$t1,$0,ERR		
	sll		$t1,$t0,2		# compute offset into table (code * 4)
	la		$t2,d_tbl		# load base address of data table
	add		$t2,$t2,$t1
	lw		$a0,0($t2)		# falls thru to the print
	li		$v0,4			# print string - $a0 holds string address
	syscall
	bne		$t0,$0,TOP		# if code is not 0, then continue the loop
	#
	# exit point
	li		$v0,10			# code==0, so exit program
	syscall
	#
	# this shows the error handling outside the loop
ERR:
	la		$a0,msg_e		# invalid code entered - error message
	li		$v0,4
	syscall
	j		TOP				# re-enter the loop
