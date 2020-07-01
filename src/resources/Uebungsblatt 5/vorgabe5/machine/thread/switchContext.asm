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

    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    push    edi

    ; from <= esp
    mov     eax, [ebp+8]    ; eax <= Wert von from (eine Adresse)
    mov     [eax], esp      ; Ort der Adresse "eax" <= esp

    ; esp <= to
    mov     eax, [ebp+12]   ; eax <= Wert von to (eine Adresse)
    mov     esp, [eax]      ; esp <= Ort der Adresse "eax"

    pop     edi
    pop     esi
    pop     ebx
    pop     ebp

	ret		; Ruecksprung zum Aufrufer



