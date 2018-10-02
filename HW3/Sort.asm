        ; 8080 assembler code
        .hexfile Sort.hex
        .binfile Sort.com
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
T_CREATE    equ 8
T_EXIT      equ 9
T_JOIN      equ 10
T_YIELD     equ 11


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

begin:
	LXI SP,stack 	; always initialize the stack pointer

	MVI B,0 ; init b
	LDA FLAG ; A = 50
	MOV E A ; ASSIGN A to E as 50 to keep that value.

WHILE:
	DCR E ; while 50 isnt 0 try loop 
	MVI A,GET_RND ; get random to b
	call GTU_OS;
	MVI A, PRINT_B ; print random num to screen
	call GTU_OS;

	JNZ WHILE ;  iterate loop


	hlt    ; end program