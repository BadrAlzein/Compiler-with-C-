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

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;

switchContext:

/* switchContext hat die Aufgabe, die Kontrolle
 * vom Stack der Coroutine "from" auf den Stack der
 * Coroutine "to" zu wechseln und damit einen Kontrolltransfer
 * zu vollziehen.
 *
 *  >Prepare Stack<
 * Am einfachsten ist es, einfach die betreffenden Register
 * auf den aktuellen Stack zu retten (pushen) 
 * 
 *  >save before switching Stacks<
 * und den Stackpointer (esp)
 * danach an der Adresse auf die "from" verweist, zu sichern.
 * 
 *  >switch Stack<
 * Nachdem das geschehen ist, wird der Stack gewechselt,
 * indem man den neuen Stackpointerwert von der Adresse
 * auf die "to" zeigt in das Stackpointerregister esp laedt.
 * 
 * >clean up<
 * Dadurch haben wir den Stack gewechselt und wir koennen nun
 * einfach alle auf diesem Stack geretteten Register wiederherstellen 
 * (in umgekehrter Reihenfolge poppen).
 * 
 * 
 * Zum Schluss fuehren wir einfach eine "ret" Instruktion aus, die dazu fuehrt,
 * dass die Coroutine "to" an der Stelle weiterlaeuft,
 * an der sie das letzte mal "switchContext" aufgerufen hat.
 * F�r Coroutinen die zum ersten mal aktiviert werden, muss
 * deshalb ein Stackframe existieren, was gleich aussieht mit
 * dem einer Coroutine die "switchContext" aufgerufen hat.
 */

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


