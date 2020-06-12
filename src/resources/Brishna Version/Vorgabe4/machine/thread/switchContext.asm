%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym switchContext

[GLOBAL switchContext]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]


switchContext:

	;Prepare switch
	push ebp			;save basePointer
	
	mov ebp, esp		;move the stackpointer to the basePinter (Calling-Conv.)
	push edi			;save all there callee-saved registers 
	push esi			;save all there callee-saved registers 
	push ebx			;save all there callee-saved registers 
	
	;save before switching Stacks (using two registers eax & edx)
	mov eax, [ebp + 8]	;save the 'from' in eax
    mov edx, [ebp + 12] ;save the to 'to' in edx
    
    ;switch the Stack
	mov [eax], esp		;save the stackPointer 1 in Adress of 'from'
	mov esp, [edx]		;return the saved old stackpointer to esp from Stack2
    
    
    ; alternative way (using only one register eax)
    ;	mov eax, [ebp + 8]	;save the 'from' in eax
    ;	mov [eax], esp		;save the stackPointer 1 in Adress of 'from'
    ;   mov eax, [ebp + 12] ;save the to Adress in eax
    ;	mov esp, [eax]		;return the saved old stackpointer to esp from Stack2
    
    
	;clean up
	pop ebx				;load new callee-saved registers
	pop esi				;load new callee-saved registers
	pop edi				;load new callee-saved registers
	
	pop ebp				;return basePointer
	ret					;Ruecksprung zum Aufrufer
