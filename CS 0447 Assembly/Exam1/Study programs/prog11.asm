.text
	# 0000 0000 0000 0011 1000 0000 0000 0000
	# 0x00038000
	lui		$t0, 0x0001
	ori		$t0, 0x8000
	
	lui		$at, 0x0003
	ori		$at, 0x8000
	and		$t0, $t0, $at
	srl		$t0, $t0, 15
	
	addi	$v0, $v0, 1
	move	$a0, $t0
	syscall