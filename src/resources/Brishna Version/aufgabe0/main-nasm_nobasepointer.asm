global  getDivisorCountNoPointer

getDivisorCountNoPointer:
	;push ebp
	;push esp
	;mov	ebp, esp
	push ebx		; nichtflüchtigen register sichern
;add code from here

	mov ebx, [esp+8]	; save in ebx because division result will overwrite eax
	mov ecx, 0	        ; divisor counter
	push ecx		; push counter on stack
	jmp cloop
loop: 
	inc ecx			; inkrement ecx
	mov eax, ebx	; put ebx into eax for division
	mov edx, 0		; set edx(modulo) zero otherwise erro
	div ecx     	; divide eax and edx with ecx
	cmp edx, 0		; compare stored edx modulo register with zero
	je  if			; jump to if condition if module comparison with 0 true
cloop:
	cmp ecx, ebx    ; compare ecx loop iterator with input integer
	jae exit		; goto finish	 
  	jmp loop   		; Jump bak to loop		; 
if:	
	pop eax			; get current divisor-count from stack into eax
	add eax, 1		; increment counter of divisor by 1
	push eax		; push it back onto stack
	jmp loop		; unconditional jump back

;to here
exit:	
	pop eax			; return value into eax
	pop ebx			; 
	;pop esp			; 
	ret