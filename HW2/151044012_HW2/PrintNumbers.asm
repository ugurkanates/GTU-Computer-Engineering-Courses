        ; 8080 assembler code
        .hexfile PrintNumbers.hex
        .binfile PrintNumbers.com
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

	; prints even numbers starting from 0 to 50(including)
	; print b and increment each time
	; it works on loop and will stop when flag-b <=0 

begin:
	LXI SP,stack 	; always initialize the stack pointer

	MVI B,0 ; init b

LOOP:	
    MVI A, PRINT_B ; first print operation
	call GTU_OS ; system call
	INR B ; increment b
	INR B ; increment b
	MVI A, FLAG ; register A to set FLAG(50)
	SUB B ; subbing content of reg b from reg A
	JP LOOP ; jump again loop if its not 0 or negative
	hlt		; end program
