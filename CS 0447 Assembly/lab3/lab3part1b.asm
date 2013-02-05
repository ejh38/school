# Zach Sadler
# Lab 3 part 1 b
# Takes in an integer, shifts it bitwise,
# then displays the 3rd digit only.
# Uses $t0 for the input integer

.text
	li		$v0, 4				# Print Please enter your integer
	la		$a0, string1
syscall

	li		$v0, 5				# Read integer
syscall

	add		$t0, $v0, $zero		# Store the 1st int in t0


	li		$v0, 4				# Print Here is the output: 
	la		$a0, string2
syscall

	sll		$t0, $t0, 11		# Do the shifting bitwise
	srl		$a0, $t0, 29		# Put it into a0 so it can be displayed

	li		$v0, 1				# Print integer
syscall


.data
    string1:    .asciiz "Please enter your integer:\n"
    string2:	.asciiz "Here is the output: "

