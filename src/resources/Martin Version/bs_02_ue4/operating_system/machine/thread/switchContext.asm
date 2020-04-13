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
; 1. Kontext der zu deaktivierenden Coroutine sichern
; sichere nicht fluechtige Register ebp, ebx, esi und edi oder im Kontrollflussstatusblock sichern
; esp im Kontrollflussstatusblock sichern
; 2. Kontext der zu aktivierenden Coroutine wiederherstellen
; esp aus dem Kontrollflussstatusblock laden
; edi, esi, ebx, ebp wiederherstellen (man beachte die Reihenfolge)
; Ruecksprungadresse beachten
switchContext:

	push ebp
	mov ebp, esp
	
	push ebx
	push esi
	push edi

	mov eax, [ebp+8]	;move &from to eax (first parameter)
	mov [eax+0], esp

	mov eax, [ebp+12] 	;&to second parameter
	mov esp, [eax]

	pop edi
	pop esi
	pop ebx

	pop ebp
	ret		; Ruecksprung zum Aufrufer

