.data:

    #Question 1: What is the machine code (in hexadecimal) of these instructions?
    #Replace MACHINECODE1 with the machine code of your first instruction.
    #Replace MACHINECODE2 with the machine code of your second instruction.
    machine_code_1:     .asciiz "3c08fade" 
    machine_code_2:     .asciiz "3508dcab"

    #Question 2: What instruction format are these instructions (R, I, or J)?
    #Replace with your answer for the instruction format (R, I, J).
    instruction_format: .asciiz "I"

    #Question 3: What are the values (in hexadecimal) of the immediate field in each instructions?
    #Replace IMMEDIATEFIELD1 with the immediate field for the first instruction.
    #Replace IMMEDIATEFIELD2 with the immediate field for the first instruction.
    immediate_field_1:  .asciiz "FADE"
    immediate_field_2:  .asciiz "DCAB"

.text:

    #============================================================
    #Place here your instructions to put 0xFADEDCAB into $t0.
    
	lui $t0, 0xFADE
	ori $t0, $t0, 0xDCAB

    #============================================================


    #============================================================
    #DO NOT MODIFY *ANYTHING* BELOW THIS LINE
    #============================================================
    #The following code uses system calls (syscalls)
    #to print out the result of your code and your answers to the questions.

    #Just to see if it worked, we'll print out $t0.
    addi    $v0, $zero, 4
    la      $a0, result_str
    syscall

    add     $a0, $zero, $t0 #Copy $t0 into $a0 (required to print it)
    addi    $v0, $zero, 34
    syscall

    #Set $v0 to 4 for the print string syscall.
    #From here on, we only print strings.
    addi    $v0, $zero, 4

    la      $a0, blank_line_str
    syscall

    la      $a0, code_str
    syscall

    la      $a0, hex_prefix_str
    syscall

    la      $a0, machine_code_1
    syscall

    la      $a0, blank_line_str
    syscall

    la      $a0, hex_prefix_str
    syscall

    la      $a0, machine_code_2
    syscall

    la      $a0, blank_line_str
    syscall

    la      $a0, format_str
    syscall

    la      $a0, instruction_format
    syscall

    la      $a0, blank_line_str
    syscall

    la      $a0, immediate_str
    syscall

    la      $a0, hex_prefix_str
    syscall

    la      $a0, immediate_field_1
    syscall

    la      $a0, blank_line_str
    syscall

    la      $a0, hex_prefix_str
    syscall

    la      $a0, immediate_field_2
    syscall

    la      $a0, blank_line_str
    syscall

.data
    result_str:     .asciiz "$t0 contains:\n"
    code_str:       .asciiz "The machine code (in hexadecimal) of these instructions are:\n"
    hex_prefix_str: .asciiz "0x"
    format_str:     .asciiz "The instruction format of these instructions is:\n"
    immediate_str:  .asciiz "The immediate field of each instruction is:\n"

    blank_line_str: .asciiz "\n"