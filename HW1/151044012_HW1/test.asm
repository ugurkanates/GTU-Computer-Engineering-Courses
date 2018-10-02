        ; 8080 assembler code
        .hexfile test.hex
        .binfile test.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

	; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6
GET_RND     equ 7

FLAG		equ 50 ; calculate until 50


	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE        

	; testing each method call
test_string:	DW '##-->Testing String',00AH,00H ; null terminated string
random_test_string:	DW '##-->Random number will be generated',00AH,00H ; null terminated string
use_input_string:	DW '##--Enter input string to test',00AH,00H ; null terminated string
use_input_num:	DW '##--Enter input num to test',00AH,00H ; null terminated string
use_input_mem:	DW '##--Enter input mem to test',00AH,00H ; null terminated string



begin:
	LXI SP,stack 	; always initialize the stack pointer

	MVI B,0 ; init b

	; testing both get rnd and print b together

	LXI B,random_test_string ; string for random_test_string
	MVI A, PRINT_STR ; store type
	call GTU_OS ; 

	MVI A,GET_RND ; get random to b
	call GTU_OS;
	MVI A, PRINT_B ; print random num to screen
	call GTU_OS;

	; testing print str alone

	LXI B,test_string ; test for PRINT_STR
	MVI A, PRINT_STR ; store  type
	call GTU_OS ; 

	; testing for print str and read str then printing input str again 

	LXI B,use_input_string ; test for PRINT_STR
	MVI A, PRINT_STR ; store  type
	call GTU_OS ; 

	MVI B, 70 ; use BC for storing user input
	MVI C, 70
	MVI A, READ_STR
	call GTU_OS

	
	MVI B, 70 ; move BC for printing
	MVI C, 70
	MVI A, PRINT_STR ; store  type
	call GTU_OS ; 


	; testing for read_b and printing that given input
	LXI B,use_input_num ; string for num input
	MVI A, PRINT_STR ; store  type
	call GTU_OS ; 

	MVI A, READ_B ; read num input
	call GTU_OS

	MVI A, PRINT_B ; print that num input to screen with printb
	call GTU_OS

	; testing for read mem and printing that given mem input
	LXI B,use_input_mem ; string for mem input
	MVI A, PRINT_STR ; store  type
	call GTU_OS ;
	 
	MVI B, 100
	MVI C, 100
	MVI A, READ_MEM
	call GTU_OS

	MVI A, PRINT_MEM ; store  type
	call GTU_OS ; system call


	hlt    ; end program