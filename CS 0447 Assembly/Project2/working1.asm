###############################
# Zach Sadler
# zps6@pitt.edu
# First working progress of 
# Project 2.
# This is basically just copying
# in getLED and setLED and properly
# formatting them in my standard.
###############################



#-----------Start of getLED-----------#
getLED:			# arguments: $a0 is x, $a1 is y (both 0-63)
				# returns: $v0 has the color (0 black, 1 red, 2 orange, 3 green)
# preamble
	addi		$sp, $sp, -16
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$ra, 12($sp)
			
_getLED:	
	# byte offset into display = y * 16 bytes + (x / 4)
	sll  		$t0, $a1, 4			# y * 16 bytes
	srl  		$t1, $a0, 2      	# x / 4
	add  		$t0, $t0, $t1    	# byte offset into display
	la   		$t2, 0xffff0008
	add  		$t0, $t2, $t0    	# address of byte with the LED
	
	# now, compute bit position in the byte and the mask for it
	andi 		$t1, $a0, 0x3    	# remainder is bit position in byte
	neg  		$t1, $t1       		# negate position for subtraction
	addi 		$t1, $t1, 3      	# bit positions in reverse order
    sll  		$t1, $t1, 1	      	# led is 2 bits
	
	# load LED value, get the desired bit in the loaded byte
	lbu  		$t2, 0($t0)
	srlv 		$t2, $t2, $t1    	# shift LED value to lsb position
	andi 		$v0, $t2, 0x3    	# mask off any remaining upper bits
	
getLED_exit:
# postamble
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$ra, 12($sp)
	addi		$sp, $sp, 16	
	
	jr   $ra
#-----------End of getLED-----------#




#-----------Start of setLED-----------#
setLED:			# arguments: $a0 is x, $a1, is y (both 0-63),
				#			 $a2 color (0 black, 1 red, 2 orange, 3 green)
				# returns: none
# preamble
	addi		$sp, $sp, -20		
	sw			$t0, 0($sp)
	sw			$t1, 4($sp)
	sw			$t2, 8($sp)
	sw			$t3, 12($sp)
	sw			$ra, 16($sp)	
		
_setLED:
	# byte offset into display = y * 16 bytes + (x / 4)
	sll			$t0, $a1, 4      	# y * 16 bytes
	srl			$t1, $a0, 2 	    # x / 4
	add			$t0, $t0, $t1   	# byte offset into display
	li			$t2, 0xffff0008		# base address of LED display
	add			$t0, $t2, $t0    	# address of byte with the LED
	
	# now, compute led position in the byte and the mask for it
	andi		$t1, $a0, 0x3    	# remainder is led position in byte
	neg			$t1, $t1        	# negate position for subtraction
	addi		$t1, $t1, 3      	# bit positions in reverse order
	sll			$t1, $t1, 1      	# led is 2 bits
	
	# compute two masks: one to clear field, one to set new color
	li			$t2, 3		
	sllv		$t2, $t2, $t1
	not			$t2, $t2       		# bit mask for clearing current color
	sllv		$t1, $a2, $t1    	# bit mask for setting color
	
	# get current LED value, set the new field, store it back to LED
	lbu			$t3, 0($t0)     	# read current LED value	
	and			$t3, $t3, $t2    	# clear the field for the color
	or			$t3, $t3, $t1    	# set color field
	sb			$t3, 0($t0)     	# update display
	
setLED_exit:
# postamble	
	lw			$t0, 0($sp)
	lw			$t1, 4($sp)
	lw			$t2, 8($sp)
	lw			$t3, 12($sp)
	lw			$ra, 16($sp)	
	addi		$sp, $sp, 20		
	
	jr	$ra
#-----------End of setLED-----------#
