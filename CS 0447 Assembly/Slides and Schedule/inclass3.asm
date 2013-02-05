	# check endianness
	.data
	endian:	.byte	0x1,0x2,0x3,0x4
	m_lit:	.asciiz	"Little endian!\n"
	m_big:	.asciiz	"Big endian!\n"

	# the program to check it
	.text
	la		$s0,endian
	lw		$s1,0($s0)
	andi		$s1,$s1,0xFF	# select lowest byte
	addi		$s1,$s1,-1	# check for 0x1	
	beq		$s1,$0,lit_end
	la		$a0,m_big		# it was big endian
	j		print
lit_end:
	la		$a0,m_lit
print:
	li		$v0,4			# print string service
	syscall
	li		$v0,10
	syscall
	
