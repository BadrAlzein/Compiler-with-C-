;
;	to compile this code
;	first create an object file
;	nasm -f elf -o main.o main-nasm.asm
;
;	to create an executeable, link it
;	gcc -m32 -o run main.o
;
;	run it:
;	./run

global  _start

_start:
	push	ebp
	mov	ebp, esp

;add code from here


;to here
	
	mov	eax, 0
	pop	ebp
	ret
