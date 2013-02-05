# find out if an integer is even or odd
# we will get a user input integer and print whether it is even or odd 

.data
A_string:	.asciiz		"Enter your integer: "
E_string:	.asciiz		"Your integer is Even"
O_string:	.asciiz		"Your integer is Odd"

.text
# first get user input integer 
la	$a0, A_string
li	$v0, 4
syscall

li	$v0, 5
syscall
addi	$t4, $v0, 0		# storing user inputer integer into $t4

# now we know that the user input integer is in $t4

# check for even/odd
andi	$t0, $t4, 0x1

# if t0 == 0, the number is even
beq		$t0, $zero, ITS_EVEN
# else the number is odd
j		ITS_ODD

ITS_EVEN:
# print it's even
la	$a0, E_string	
li	$v0, 4
syscall

j EXIT		# we need this because otherwise the following code sequence will be executed and both E_string and O_string will get printed  
			# jumping to EXIT will skip printing O_string

ITS_ODD:
# print it's odd
la	$a0, O_string	
li	$v0, 4
syscall

EXIT:


