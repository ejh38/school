# SumOfFactorials(N) = N! + SumOfFactorials(N-1)
# SumOfFactorials(1) = 1

.text
# get input integer	
li		$v0, 5
syscall

# find the SumOfFactorials
move	$a0, $v0
jal		sumOfFactorials
move	$a0, $v0

li		$v0, 1
syscall

li		$v0, 10
syscall


    sumOfFactorials:
		# prologue
        addi $sp, $sp, -16
        sw $ra, 0($sp)
        sw $s0, 4($sp)
        sw $s1, 8($sp)
        sw $a0, 12($sp)

		# body
        blt $a0, 1, sumOfFactorials_baseCase

        sumOfFactorials_recursiveCode:
            jal _fact         
            move $s0, $v0           #Put fact(n) into $s0

            lw $a0, 12($sp)         #Restore n
            addi $a0, $a0, -1       #n = n - 1

            jal sumOfFactorials     #sumOfFactorials(n)
            move $s1, $v0           #Put the result into $s1

            add $v0, $s0, $s1       #return value = $s0 + $s1
            j sumOfFactorials_return

        sumOfFactorials_baseCase:
            move $v0, $a0
            j sumOfFactorials_return

		# epilogue
        sumOfFactorials_return:
            lw $ra, 0($sp)
            lw $s0, 4($sp)
            lw $s1, 8($sp)
            lw $a0, 12($sp)
            addi $sp, $sp, 16
            jr $ra

_fact:
    # prologue to procedure
    addi    $sp,$sp,-8        # push space for activation frame
    sw    $s0,0($sp)        # save $s0, which we use
    sw    $ra,4($sp)        # save return address
    # start of actual procedure work
    move    $s0,$a0            # get argument ($a0)
    li    $v0,0x1            # 1
    beq    $s0,$v0,_fact_exit    # end of recursion (f==1?)
    addi    $a0,$s0,-1        # f /= 1, so continue. set up arg(f-1)
    jal    _fact            # recursive call 
    mult    $v0,$s0            # multiply
    mflo    $v0            # return mul result 

_fact_exit:
    # epilogue to exit procedure
    lw    $ra,4($sp)        # restore $ra
    lw    $s0,0($sp)        # restore $s0
    addi    $sp,$sp,8        # pop activation frame
    jr    $ra            # return


