.data
x:	.half 15
y:	.half 8
z:	.half 0

.text
lh	$t0, x			# load x to $t0
lh	$t1, x+2		# load y (2 bytes after x) to $t1
add 	$t2, $t0, $t1		# add the values at x and y
  
sh 	$t2, z			# storze x + y to z

la 	$t3, z			# load the address of z
sh 	$t2, -2($t3)		# store the value of z to 2 bytes before (y)
sb 	$t2, -4($t3)		# 4 bytes before (x)