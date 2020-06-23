%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym getCurrentEsp

[GLOBAL getCurrentEsp]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

getCurrentEsp:
    mov     eax, esp
    ret

