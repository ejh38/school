	# CS/COE 0447  Spring 2009  Example Program weather.asm
	#
	# this program illustrates control flow instructions and how to do simple
	# "if-then-else" style statements.
	# 
	##########################################################################
	# in C, this program does the following:
	# int code;
  	# do {
  	#  	printf("Enter a code for the weather (0 to exit, 1-3)?\n");
    #	scanf("%d", &code);
	#   if (code == 0) printf("Bye! Try Hawaii!\n");
	#	else if (code == 1) printf("It is cloudy in Pittsburgh today!\n");
	#   else if (code == 2) printf("It is flurrying in Pittsburgh today!\n");
	#	else if (code == 3) printf("It is snowing in Pittsburgh today!\n");
	#	else printf("You must have the wrong city!! (Wrong code entered.)\n");
	# } while (code != 0);
	##########################################################################
	#
	# notice in the program below how the if-then-else statement is done.  we
	# do a comparison for the condition (code's value).  if the comparison is
	# false, then we skip the body of the "then arm".  the actual comparison
	# is a subtraction and the branch is a "branch not equal" because we want
	# to skip the body of the then-arm when the condition isn't satisfied.
	#
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
	# the prompt is do-while loop. TOP is the entry point in the loop.
TOP:
	# prompt for a code
	la		$a0,prompt
	li		$v0,4
	syscall
	# get a weather code from the user
	li		$v0,5
	syscall
	# $t0 is "code" - save code from the system call
	move	$t0,$v0
	#
	# if (code == 0) printf("Bye! Try Hawaii!\n");
	#
	bne		$t0,$0,MSG1
	la		$a0,msg_0
	li		$v0,4
	syscall
	j		WHILE	# go to bottom of while loop (skip else parts)
MSG1:
	#
	# else if (code == 1) printf("It is cloudy in Pittsburgh today!\n");
	#
	# the comparison is done by subtracting the expected value from the code
	#   e.g., when the code is 1: $t0-1=0
	# thus, we can check the result of the comparison against 0.  if the
	# result is not zero, then $t0 is not 1.
	#
	addi	$t1,$t0,-1
	bne		$t1,$0,MSG2		# code is not 1, so check 2 and 3 or error
	la		$a0,msg_1
	li		$v0,4
	syscall
	j		WHILE
MSG2:
	#
	# else if (code == 2) printf("It is flurrying in Pittsburgh today!\n");
	#
	# check whether the code is 2 - works the same way as MSG1 case
	addi	$t1,$t0,-2
	bne		$t1,$0,MSG3		# code is not 2, so check 3 or error
	la		$a0,msg_2
	li		$v0,4
	syscall
	j		WHILE
MSG3:
	#
	# else if (code == 3) printf("It is snowing in Pittsburgh today!\n");
	# 
	addi	$t1,$t0,-3
	bne		$t1,$0,ERR		# code is not 3, so an error
	la		$a0,msg_3
	li		$v0,4
	syscall
	j		WHILE
ERR:
	#
	# else printf("You must have the wrong city!! (Wrong code entered.)\n");
	#
	# if we reach this point, then an error code was entered
	# this point is the final 'else' in the code above
	la		$a0,msg_e
	li		$v0,4
	syscall
	#
WHILE:
	# this does:   }while (code !=0);	
	bne		$t0,0,TOP
	#
	# exit point from loop
	# terminate the program
	li		$v0,10
	syscall
