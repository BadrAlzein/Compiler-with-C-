%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym initializeStacks

[GLOBAL initializeStacks]

; IMPLEMENTIERUNG DER FUNKTIONEN

;                           +4              +8          +12          +16
; void initializeStacks(unsigned edi, unsigned esi, unsigned ebx, void* bp);

[SECTION .text]

initializeStacks:

    ; Pushreinfolge:
    ;
    ;   1. ebp
    ;   2. ebx
    ;   3. esi
    ;   4. edi
    ;

    mov     eax, [esp+16]
    push    eax

    mov     eax, [esp+12]
    push    eax

    mov     eax, [esp+8]
    push    eax

    mov     eax, [esp+4]
    push    eax

    mov     eax, [esp]
    push    eax

    mov     eax, esp
    ret
