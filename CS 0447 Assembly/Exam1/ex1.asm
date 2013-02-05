# integer input, print and store in memory example

# step1: input an integer, print it on the screen with a string
# step2: store that integer into memory at address of A

.data
A: 		.word	0xba5eba11
my_str:	.asciiz	"_ " 

.text
# input an integer
li		$v0, 5				# syscall service 5
syscall

# $v0 contains the integer that is read
# save it into a register ($t4) because we will use $v0 for other system calls
addi 		$t4, $v0, 0		# $t4 = $v0

# print the string
li		$v0, 4				# service 4
la		$a0, my_str			# $a0 has the address of the string we need to print
syscall

# print the integer (which is now in $t4)
li			$v0, 1			# service 1
addi		$a0, $t4, 0		# $a0 contains the integer (from $t4) to print
syscall

# store that integer into A
la		$t0, A				# $t0 now has A's address
sw		$t4, 0($t0)			# store $t4 into A

