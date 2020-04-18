
global mainWithWhileLoop ;find DivSum using while loop
global mainWithtForLoop ;find DivSum using For loop

;****************************Part 1 **********************

mainWithWhileLoop:
	push ebp					; calling convention save non-fluent registers and baspointer
	mov	ebp, esp
	push ebx

	mov eax, [ebp + 8] 			; get Input from Stack to eax

findSumDiv_WithWhileLoop: 		;will find the sum of div using for 
		push 0 ; sum devision 
		mov ecx,eax ; i = num (inverted for loop)
		jmp while_loop
while_body_loop: 
		pop eax ;Test
		add eax,3 ;Test
		push eax;test


			;Obada Operations





		dec ecx
while_loop:
		cmp ecx, 0
		je exit_Program_One
		jmp while_body_loop
		
exit_Program_One:
	pop eax ; save sum dividers in eax (the return Value)
	pop ebx	
	pop ebp
	ret

;**************************** Part2 **********************
mainWithtForLoop:

	push ebp			; calling convention save non-fluent registers and baspointer
	mov	ebp, esp
	push ebx

	push 0				; push 0 on stack for counting the divisor-count
	mov ecx, 1	    	; divisor counter
	mov ebx, [ebp+8]	; save in ebx because division result will overwrite eax

	cmp ebx,0			;see if input is 0 
	jle exit			;ja? then out the default value of sum dividers
	jmp loop			;nein? start looping 
loop:
	mov eax, ebx		; put ebx into eax for division
	mov edx, 0			; set edx(modulo) zero otherwise error
	idiv ecx     		; dvide eax and edx with ecx
	cmp edx, 0			; compare stored edx modulo register with zero
	je  if				; jump to if condition if module comparison with 0 true
	cmp ecx, ebx    	; compare ecx loop iterator with input integer
	jae exit			; goto finish	
	inc ecx      		; Increment i++
	jmp loop   			; repait the loop
if:	
	pop eax				; get current divisor-count from stack into eax
	add eax, 1			; increment counter of divisor by 1
	push eax			; push it back onto stack
	inc ecx
	jmp loop			; unconditional jump back

;to here
exit:	
	pop eax				; get divisor-count from stack
	mov ecx, [ebp+12]	; get pointer address for storing divisor-count 
	mov [ecx], eax		; move divisor-count into address to pointer points
	pop ebx				;restore non-fluent register
	pop ebp				;restore old basepointer 
	ret
