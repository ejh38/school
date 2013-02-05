
		# a demo of loops and strings
		# replaces spaces (20h, 32d) with pluses (2Bh, 43d)
		#
	.data
		str:	.asciiz		"Hello CS 477!\n"
	.text
	
		la		$a0,str
		li		$v0,4		# print string service
		syscall
		
	TOP:
		lbu		$t0,0($a0)	# get character from string
		beq		$t0,$0,END	# reached null
		addi	$t0,$t0,-32	# check for space?
		bne		$t0,$0,NEXT
		# fall thru: the character was a space
		addi	$t0,$0,'+'	# get the plus character
		sb		$t0,0($a0)	# replace space with plus
	NEXT:
		addi	$a0,$a0,1	# increment to next character
		j		TOP
	END:
		la		$a0,str		# reset string pointer
		li		$v0,4		# print string service
		syscall
		li		$v0,10		# halt service
		syscall

