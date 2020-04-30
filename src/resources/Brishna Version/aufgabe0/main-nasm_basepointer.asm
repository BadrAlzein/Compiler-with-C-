
global  getDivisorCountPointer

getDivisorCountPointer:
	push ebp		; calling convention save non-fluent registers and baspointer
	mov	ebp, esp
	push ebx
;add code from here
	push 0			; push 0 on stack for counting the divisor-count
	mov ecx, 1	     ; divisor counter
	mov ebx, [ebp+8]; save in ebx because division result will overwrite eax
loop:
	mov eax, ebx	; put ebx into eax for division
	mov edx, 0		; set edx(modulo) zero otherwise error
	idiv ecx     		; dvide eax and edx with ecx
	cmp edx, 0		; compare stored edx modulo register with zero
	je  if			; jump to if condition if module comparison with 0 true
	cmp ecx, ebx    	; compare ecx loop iterator with input integer
	jae exit			; goto finish	
	inc ecx      	; Increment
	cmp ecx,ebx    	; Compare cx to the limit
	jle loop   		; Loop while less or equal
if:	
	pop eax			; get current divisor-count from stack into eax
	add eax, 1		; increment counter of divisor by 1
	push eax		; push it back onto stack
	inc ecx
	jmp loop		; unconditional jump back

;to here
exit:	
	pop eax				; get divisor-count from stack
	mov ecx, [ebp+12]	; get pointer address for storing divisor-count 
	mov [ecx], eax		; move divisor-count into address to pointer points
	pop ebx				;restore non-fluent register
	pop ebp				;restore old basepointer 
	ret