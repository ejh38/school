.data
	num_dishes:		.asciiz "Enter the number of dishes?\n"
	min_moves:		.asciiz	"The minimum number of moves?\n"

.text
	li				$v0, 4
	la				$a0, num_dishes
  syscall
  	li				$v0, 5
  syscall									# the number of dishes is in $v0
  
  	move			$s0, $v0				# now it is in $s0
  	li				$s1, 2					# the value 2 is stored in $s1
  	addi			$a0, $s0, -1			# put n-1 in $a0
 	jal				hanoi					# get the hanoi of n-1
 	li				$t0, 2
 	mult			$v0, $t0
 	mflo			$t0
 	addi			$t0, $t0, 1
 	
 	li				$v0, 4
 	la				$a0, min_moves
  syscall									# display 'minum number of moves?'
 	
 	move			$a0, $t0
 	li				$v0, 1
  syscall									# display number of moves
 	
 j exit	


hanoi:
		# prologue
   addi				$sp, $sp, -16 
   sw 				$ra, 0($sp)
   sw 				$s0, 4($sp)
   sw 				$s1, 8($sp)
   sw 				$a0, 12($sp)

		# body
   blt 				$a0, 1, hanoi_baseCase

hanoi_recursiveCode:
   jal 				_hanoi         
   move 			$s0, $v0          		# Put fact(n) into $s0

   lw 				$a0, 12($sp)        	# Restore n
   addi 			$a0, $a0, -1       		# n = n - 1

   jal 				hanoi   
   move 			$s1, $v0           		# Put the result into $s1

   add 				$v0, $s0, $0      		# return value = $s0
   j 				hanoi_return

hanoi_baseCase:
   move 			$v0, $a0
   j 				hanoi_return

		# epilogue
hanoi_return:
   lw 				$ra, 0($sp)
   lw 				$s0, 4($sp)
   lw 				$s1, 8($sp)
   lw 				$a0, 12($sp)
   addi 			$sp, $sp, 16
   jr				$ra          
			           	           
			           	           	           	           
_hanoi:
    # prologue to procedure
   addi   			$sp,$sp,-8       		 # push space for activation frame
   sw   			$s0,0($sp)       		 # save $s0, which we use
   sw   			$ra,4($sp)        		 # save return address
    # start of actual procedure work
   move   			$s0,$a0            		 # get argument ($a0)
   li				$v0, 0x1
   beq    			$s0, $v0, _hanoi_exit    # end of recursion (f==1?)
   addi    			$a0,$s0,-1        		 # f /= 1, so continue. set up arg(f-1)
   jal   			_hanoi   	        	 # recursive call 
   li				$t0, 2
   mult    			$v0,$t0            		 # multiply
   mflo    			$v0            			 # return mul result  
   addi				$v0, $v0, 1  
   
_hanoi_exit:
	lw    $ra,4($sp)        				 # restore $ra
    lw    $s0,0($sp)        				 # restore $s0
    addi    $sp,$sp,8        				 # pop activation frame
    jr    $ra            					 # return
	
			
exit:
	li		$v0, 10
	syscall