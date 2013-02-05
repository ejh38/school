	# CS/COE 0447 Spring 2009 - Illustrates functions
	#
	#   NOTE: VIEW THIS FILE IN MARS.  IT TABS CORRECTLY.
	#
	#	this program encodes a string with a Caesar cipher
	#   it will also decode the string
	#   encoded and decoded strings are printed
	#   it works by looking up a character in the cipher to
	#   encode/decode it.  more efficient implementations 
	#   are possible with modulo arithmetic.
	#
	#   this program works only with legal alphabetic
	#   characters (A-Z).  lower or uppercase is fine.  the
	#   case is converted to uppercae for encoding. consider
	#   how this program can be modified to support other
	#   characters.  maybe give it a try!  (look at the ASCII
	#   code on the green card in the book for some hints.)
	#
	#   function _print_str shows passing arguments on the
	#   stack.  a better implementation would simply pass the
	#   argument in a register.
	#
	#   the functions preserve all registers.  you can write
	#   more efficient code by paying attention to exactly
	#   what registers need to be saved between calls.  in
	#   the code below, no assumptions are made about regs.
	#
	#   enct is the encoding table (the cipher)
	#   msg is space reserved to hold entered message
	# 
	.data
	enct:	.asciiz "XYZABCUVDEFRSTGHIOPQJKLMNO"
	#				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	msg:	.space	255
	prompt:	.asciiz "Enter a message to encode"
	m_enc:	.asciiz "Encoded: "
	m_dec:	.asciiz	"Decoded: "
	.text
	#
	# this loop prompts user for a message to encode/decode
	# the loop is exited by typing "!" in the input
	#
main_loop:
	la	$a0,msg
	la	$t0,prompt
	sw	$t0,-4($sp)	# push argument into called func AR
	jal	_print_str	# call function to print string
	jal	_get_msg	# get a string to encode
	# check for ! to end program
	lbu	$t0,0($a0)	
	addi	$t0,$t0,-33	# 33d is ASCII char for !
	beq	$t0,$0,main_exit   # is char='!'?
	jal	_encode		# encode the string
	la	$a1,m_enc
	jal	_print_msg	# print the encoded string
	jal	_decode		# decode the string
	la	$a1,m_dec
	jal	_print_msg	# print the decoded string
	j	main_loop
main_exit:
	li	$v0,10
	syscall

_print_str:
	# _print_str() - prints string to display
	#   arguments: address of string passed on stack
	#	destroys:  none. all registers preserved.
	#	returns:   none.
	#
	addi	$sp,$sp,-12	# push AR: arg, saved $a0, saved $v0
	sw	$a0,0($sp)	# save contents of $a0
	sw	$v0,4($sp)	# save contents of $v0
	lw	$a0,8($sp)	# addr of string from stack
	li	$v0,4		# print string service
	syscall
	lw	$v0,4($sp)	# restore contents of $v0
	lw	$a0,0($sp)	# restore contents of $a0
	addi	$sp,$sp,12	# pop AR
	jr	$ra			# return

_get_msg:
	# _get_msg() - inputs a message from user
	#   arguments: none. string put in "msg"
	#	destroys:  none.
	#   returns:   none.
	#
	addi	$sp,$sp,-12	# push AR
	sw	$ra,0($sp)	# save return addr - non-leaf proc.
	sw	$a0,4($sp)	# save regs that are modified
	sw	$a1,8($sp)
	la	$a0,msg		# pointer to input string buffer
	la	$a1,255		# maximum length input buffer
	jal	_get_str	# get a string to encode
	jal	_chomp		# remove linefeed on input
	jal	_to_ucase	# make string uppercase
	lw	$a1,8($sp)	# restore modified regs
	lw	$a0,4($sp)
	lw	$ra,0($sp)	# restore return addr
	addi	$sp,$sp,12	# pop AR
	jr	$ra			# return

_print_msg:
	# _print_msg(msg1, msg2) - prints two strings with nl
	#   arguments: $a1 holds string1, $a0 holds string2
	#   destroys:  none
	#   returns:   none
	#
	addi	$sp,$sp,-8			# push AR
	sw	$ra,0($sp)			# non-leaf proc
	sw	$v0,4($sp)			# save modified regs
	sw	$a0,8($sp)
	sw	$a1,-4($sp)			# print string in $a1
	jal	_print_str
	sw	$a0,-4($sp)			# print string in $a0
	jal	_print_str	
	addi	$v0,$0,11			# print char service
	addi	$a0,$0,'\n'			# newline char
	syscall
	lw	$a0,8($sp)			# restore modified regs
	lw	$v0,4($sp)
	lw	$ra,0($sp)			# get return addr
	addi	$sp,$sp,8			# pop AR
	jr	$ra					# return

_get_str:
	# _get_str() - gets a string from the user
	#   arguments: $a0 is buffer, $a1 is max length
	#   destroys:  none
	#	returns:   none
	#
	addi	$sp,$sp,-4	# push AR: saved $v0
	sw	$v0,0($sp)	# save contents of $v0
	li	$v0,8		# get string service
	syscall
	lw	$v0,0($sp)	# restore contents of $v0
	addi	$sp,$sp,4	# pop AR
	jr	$ra			# return

_chomp:
	# _chomp() - removes linefeed (LF) from string input
	#   arguments: $a0 holds address of string
	#   destroys:  none
	#   returns:   none
	#
	addi	$sp,$sp,-8			# push AR
	sw	$a0,0($sp)			# save regs that are modified
	sw	$s0,4($sp)
_chomp_loop:
	lbu	$s0,0($a0)			# get char
	beq	$s0,$0,_chomp_exit	# null?
	addi	$s0,$s0,-10			# LF is ASCII 10d
	bne	$s0,$0,_chomp_cont	# LF?
	sb	$0,0($a0)			# yes, turn LF into a null
	j	_chomp_exit
_chomp_cont:
	addi	$a0,$a0,1			# next character
	j	_chomp_loop
_chomp_exit:
	lw	$s0,4($sp)			# restore modified regs
	lw	$a0,0($sp)
	add	$sp,$sp,8			# pop AR
	jr	$ra
	
_to_ucase:
	# _to_ucase() - makes a string uppercase
	#   arguments: $a0 holds address of string
	#   destroys:  none
	#   returns:   none
	#
	addi	$sp,$sp,-12			# push AR
	sw	$s0,0($sp)			# save regs we'll modify
	sw	$s1,4($sp)
	sw	$a0,8($sp)
_to_ucase_loop:
	lbu	$s0,0($a0)			# get character
	beq	$s0,$0,_to_ucase_exit
	# lowercase c when 97 <= c <= 122
	slti	$s1,$s0,97			# $s1=1 when $s0<97
	bne	$s1,$0,_to_ucase_cont
	slti	$s1,$s0,123			# $s1=0 when $s0>122
	beq	$s1,$0,_to_ucase_cont
	addi	$s0,$s0,-32			# convert to lower case
	sb	$s0,0($a0)			# save lower case char
_to_ucase_cont:
	addi	$a0,$a0,1			# next character
	j	_to_ucase_loop
_to_ucase_exit:
	lw	$a0,8($sp)			# restore modified regs
	lw	$s1,4($sp)			
	lw	$s0,0($sp)			
	add	$sp,$sp,12			# pop AR
	jr	$ra					# return

_encode:
	# encode() - encodes a string 
	#	arguments: $a0 is string to encode
	#   destroys:  none
	#	returns:   none; message is encoded string
	#
	addi	$sp,$sp,-12				# push AR
	sw	$a0,0($sp)				# save needed regs
	sw	$s0,4($sp)
	sw	$s1,8($sp)
_encode_loop:
	lbu	$s0,0($a0)				# get char to encode
	beq	$s0,$0,_encode_exit		# null? EOL.
	addi	$s0,$s0,-65				# ofs=char-'A' 
	la	$s1,enct				
	add	$s1,$s1,$s0				# offset into cipher
	lbu	$s0,0($s1)				# get code char
	sb	$s0,0($a0)				# write code char
	addi	$a0,$a0,1				# next char in msg
	j	_encode_loop
_encode_exit:
	lw	$s1,8($sp)				# restore modified regs
	lw	$s0,4($sp)
	lw	$a0,0($sp)
	addi	$sp,$sp,12				# pop AR
	jr	$ra						# return

_decode:
	# _decode(ptr) - decodes the message pointed to by ptr
	#	arguments:  $a0 holds ptr to message to decode
	#   destroys:   none
	#   returns:    none; message is decoded string
	#
	addi	$sp,$sp,-16			# push AR
	sw	$a0,0($sp)			# save regs modified
	sw	$s0,4($sp)
	sw	$s1,8($sp)
	sw	$s2,12($sp)
_decode_loop:
	lbu	$s0,0($a0)
	beq	$s0,$0,_decode_exit  # null?  exit if so.
_decode_char:
	la	$s1,enct
	# find the encoded character in the code table
_decode_char_loop:
	lbu	$s2,0($s1)		# get char from code table
	addi	$s1,$s1,1		
	bne	$s0,$s2,_decode_char_loop	# match?
	# found a matching char - now, we can decode it
	# take position in table, add to 'A' to get decode char
	la	$s2,enct 		# -1 to adjust for extra add
	sub	$s1,$s1,$s2		# alpha position in $s1
	addi	$s1,$s1,'@'		# decoded char
	sb	$s1,0($a0)		# save decoded char to msg
	addi	$a0,$a0,1		# next char in msg
	j	_decode_loop
_decode_exit:
	lw	$s2,12($sp)		# restore modified regs
	lw	$s1,8($sp)
	lw	$s0,4($sp)
	lw	$a0,0($sp)
	addi	$sp,$sp,16		# pop AR
	jr	$ra				# return
