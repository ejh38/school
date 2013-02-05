	# tests jr by itself
	#
	# assumes addui, put and halt work
	#
	addui	$r7,5
	jr	$r7		# should transfer control to label "here" below
	addui	$r7,10
	put	$r7		# incorrect output (maybe 15?)
	halt
here:
	put	$r7		# correct output is 5
	halt