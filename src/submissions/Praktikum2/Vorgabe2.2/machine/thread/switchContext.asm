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

	;Prepare Stack1
	push ebp			;save basePointer
	mov ebp, esp		;move the stackpointer to the basePinter (Calling-Conv.)	
	push ebx			;save all there registers used in Coroutine
	push esi			;save all there registers used in Coroutine
	push edi			;save all there registers used in Coroutine

	;save before switching Stacks
	mov eax, [ebp + 8]	;save the 'from' in eax
	mov [eax], esp		;save the stackPointer 1 in Adress of 'from'

	;switch the Stack
	mov eax, [ebp + 12] ;save the to Adress in eax
	mov esp, [eax]		;return the saved old stackpointer to esp from Stack2

	;clean up 
	pop edi				;return all there registers used in Coroutine
	pop esi				;return all there registers used in Coroutine
	pop ebx				;return all there registers used in Coroutine
	pop ebp				;return basePointer
	ret					;Ruecksprung zum Aufrufer
