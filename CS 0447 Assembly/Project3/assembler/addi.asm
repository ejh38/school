	# this program checks that addi works (the simplest instruction)
	#
	# put a probe on the output of the ALU to check the result
	#
	addi	$r0,1	# value is 1
	addi	$r0,2	# value is 1+2=3
	addi	$r0,3	# value is 3+3=6
	# check sign extend	
	addi	$r0,0xfe # value is 6+(-2)=4	
	addi	$r0,5	# value is 4+4=9
	halt		# you can remove this and it should work