#####################################################################################################
# Zach Sadler
# zps6@pitt.edu
# README for Project 3
# Table of Contents:
# Programs, Sub Circuits, Control
# Explanation (and Important Notes), and Buglist
# (NOTE: made to be displayed with a window size such that this whole line is displayed with no wrap)
#####################################################################################################

------------------------------------Start of Programs-----------------------------------------------

My program successfully runs each of the following 'individual programs' and gives the correct output:
	addi.asm
    	put.asm 
   	put2.asm 
    	addui.asm 
    	sllv.asm 
    	sll.asm 
    	bz.asm 
    	bp.asm 
    	bn.asm 
    	srl.asm
    	jal.asm
    	jr.asm 
    	lwsw.asm

Additionally, my program successfully runs each of the following multi-test programs:
	increment.asm
	load.asm		(assuming correct output is '37', not '37h')
	addshift.asm 		(assuming the final correct output is '8888')
	loadstore.asm		(assuming the output should go 9-0 and halt at '0000')
	function.asm

I had the most trouble trying to get function.asm to run correctly, but after getting the correct output (00AA) for that one (and the rest) I feel confident enough to say my implementation is complete and each instruction is implemented correctly.

------------------------------------End of Programs-------------------------------------------------

------------------------------------Start of Sub Circuits-------------------------------------------

	main: this is the main circuit, which you will use for running programs and checking output.
	Registers: This is lab11 extended to 8 registers, which 2 read ports, a write port, and the ability to clear (using the clear button).
	16 Bit ALU: This is a simple ALU with four operations (00 AND, 01 NOR, 10 ADD, 11 SUB). It outputs the result of the operation, and also a one bit Zero if A is zero (used for BZ).
	Control, Branch Control, Jump Control: See the Control section below.

------------------------------------End of Sub Circuits---------------------------------------------

------------------------------------Start of Control------------------------------------------------

There are 3 control sub circuits. Each takes in the 4 bit opcode and 1 bit SubOp and outputs to the following:
Control:
	Halt	 - true only for halt, disables the PC
	Put	 - true only for put, changes the put register which changes the LEDs
	Addi	 - true only for addi, used for sign extension
	ALUOp1	 - combines with ALUOp0 below to form the ALUOp code for the ALU
	ALUOP0	 - the least significant bit of the ALUOp code
	Branch	 - true only for branch instructions, see Branch Control
	MemWrite - true only for SW, turns on the store port of the RAM
	MemRead	 - true only for LW, turns on the read port of the RAM
	RegWrite - turns on the 'write enabled' port of the Registers
	MemtoReg - true only for LW, changes the write data of the register to the output of the RAM
	ALUSrc	 - determines whether ALU input B comes from a register or immediate
	RegDest	 - this is actually an unused control signal, but I kept it in for future expansion
	Shift	 - this is true only for Shift instructions, and activates the shifters

Branch Control:
	BN	- true only for BN
	BP	- true only for BP
	BX	- true only for BX
	BZ	- true only for BZ
These signals each combine with Branch (from Control) and one or two others to determine if the 3 or 4 place AND gate (labeled BN, BP, BX, BZ) should be true or not. If either of these four AND gates is true, then the MUX is set to take the value from the immediate and pass it into PC.
	For BN, it checks the most significant bit of $rs. If it's 1 then the value is negative.
	For BP, it checks the most significant bit of $rs, and also the Zero value from the ALU. If the bit from $rs is 0 and Zero is false, then it is positive.
	For BX, it checks to see if Zero is false.
	For BZ, it checks to see if Zero is true.

Jump Control: 
	There is a single 3 bit output. This output is split, and then if either of the three single bits is 1, a MUX is set to set the PC value to either the Immediate given or the value of $rs. Additionally, if jal is the instruction then there is a control signal passed to a MUX which tells the write data going into the registers to come from PC + 1, not the normal location.
	
------------------------------------End of Control--------------------------------------------------

------------------------------------Start of Explanation--------------------------------------------

Explanation:	
	As opposed to the programs, where much explanation is needed to understand, I think the circuit speaks for itself pretty well. All the same, I'll give a few words.

	I implemented the processor mainly as was demonstrated in the lecture slides and help files given. Initially this caused me trouble, as I included support for slt (and thus, overflow detection), OR instead of NOR, and other things. Eventually I realized my error and instead just took the instructions one at a time and implemented them individually. I tested each one by generating my own byte code (not using the Assembler), and when I felt they were working I moved on to the next.
	After building the individual components and the datapath, I found that the control was actually to just manually create. I did start by using the combinational analysis, but eventually just did it myself through AND, NOT, OR gates. I realize that as a result my circuitry is likely not minimized, but it was easier for me to implement than trying to have all possible control values figured out at once.
	Mostly I would say my design is straightforward and taken from the slides. The parts that require explanation are detailed elsewhere in this README.

Important Notes:
	The 'Clear' button is used to reset the PC, clear the registers, and reset the LEDs and Put register. The 'Clear RAM' button resets the RAM.
	In addition to the required 4 Hex Digit Display, I also included outputs of $rs and either $rt or Imm (whichever is being used). I found this very helpful in debugging and reading outputs when they are not necessarily displayed using Put.

------------------------------------End of Explanation--------------------------------------------	
------------------------------------Start of Buglist----------------------------------------------

Buglist:
	I tried each of the test programs and found no errors. Thus, I'd say my implementation is very correct.

------------------------------------End of Buglist------------------------------------------------