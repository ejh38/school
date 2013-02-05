		# this example shows two functions, including how to call them:
		#    replace(string, toreplacechar, replacewithchar);
		#    print(string);
		#
		.data
		str:	.asciiz "Hello CS 447!\n"
		nl:		.asciiz	"\n"
		cstr:	.asciiz "The count is:"
		.text
		# this is the main entry point to the program
		la		$a0,str		# string to replace character in
		li		$a1,' '		# character to replace (space)
		li		$a2,'+'		# replacement character
		jal		replace		# do the replacement
		jal		print		# now print the string
		li		$a1,'+'		# character to replace
		li		$a2,'_'		# change + to _
		jal		replace
		jal		print
		addi	$a1,$0,'_'	# count the '_'
		jal		count
		move	$a1,$v0		# count is in $v0
		la		$a0,cstr
		jal		print_str_num
		li		$v0,10
		syscall

replace:
		# replace(string, chartoreplace, replacement)
		# 	purpose: global find and replace for a character in a string
		#	args: $a0 is string; $a1 is char to find, $a2 is replacement
		#   trashes: $t0,$t1
		move	$t0,$a0		# preserve $a0's contents
replace_loop:
		lbu		$t1,0($t0)
		beq		$t1,$0,replace_exit
		sub		$t1,$t1,$a1	# check for char to replace?
		bne		$t1,$0,replace_next
		sb		$a2,0($t0)	# write the replacement char
replace_next:
		addi	$t0,$t0,1
		j		replace_loop
replace_exit:
		jr		$ra

print:
		# print(string)
		#	purpose: print a string to console
		#	args: $a0 is string to print
		#   trashes: $t0
		move	$t0,$v0		# save $v0
		li		$v0,4
		syscall
		move	$v0,$t0		# restore $v0
		jr		$ra
	
count:
		# count(string)
		#	purpose: count number of particular characters
		#	args: $a0 is string, $a1 is character to count
		#	trashes: $t0, $t1
		#	returns: $v0 is count
		move	$t0,$a0
		add		$v0,$0,$0
count_loop:
		lbu		$t1,0($t0)
		beq		$t1,$0,count_exit
		sub		$t1,$t1,$a1
		bne		$t1,$0,count_next
		addi	$v0,$v0,1
count_next:
		addi	$t0,$t0,1
		j		count_loop
count_exit:
		jr		$ra

print_str_num:
		# print_str_num(string, number)
		#	purpose: format and print a string followed by a number
		#	args: $a0 is string, $a1 is number
		#	trashes: $t0,$t1, $t2
		move	$t0,$a0		# save arg 0
		move	$t1,$a1		# save arg 1
		move	$t2,$ra		# save $ra due to call to print
		jal		print		# print the string - destroys $ra!
		addi	$a0,$0,' '		# print space after string
		li		$v0,11
		syscall
		move	$a0,$a1		# get number in arg register
		li		$v0,1		# print number service
		syscall				# the number
		move	$ra,$t2		# restore return address register
		move	$a1,$t1
		move	$a0,$t0
		jr		$ra

		
