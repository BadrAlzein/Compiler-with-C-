
global mainWithWhileLoop ;find DivSum using while loop
global mainWithtForLoop ;find DivSum using For loop

;****************************Part 1 **********************

mainWithWhileLoop:
	push ebp				; calling convention save non-fluent registers and baspointer
	mov	ebp, esp					
	push ebx				;ebx will be used so save it acording to gcc convention
	mov ebx, [ebp + 8] 		; get Input from Stack to eax

findSumDiv_WithWhileLoop: 	;will find the sum of div using while loop
		push 0			;the sum of the dividers 	
		mov ecx,eax ; make i = num (inverted for loop) from num to 0 
		jmp while_loop	;start the loop
while_body_loop: 	
		mov eax,ebx	;save the value of num in eax every time the loop starts
		mov edx,0	;give the register that have the mod a default value of 0 
		idiv ecx 	;divide eax onto i and save it in eax and the rest of the division in edx
		dec ecx		;i--
		cmp edx,0 	;if the mod==0 then save it  
		je foundend ;inc the sum dividers of 1 
while_loop:				
		cmp ecx, 0		;if the loop i =0 then stop the loop 
		je exit_Program_One	; stop the loop and show the answer
		jmp while_body_loop	;

foundend:	 ; this will inc the sum dividers by 1 
		pop eax 	
		inc eax 
		push eax 
		jmp while_loop ;continue the loop 


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
