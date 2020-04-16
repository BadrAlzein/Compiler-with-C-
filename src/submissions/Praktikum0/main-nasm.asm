
global mainWithWhileLoop ;find DivSum using while loop
global mainWithtForLoop ;find DivSum using For loop

;****************************Part 1 **********************

mainWithWhileLoop:
	mov eax, [esp + 4] ; get Input from Stack to eax
	cmp eax, -1  ;input < 0
	jle is_negative	;convert Input to positive and continue
	jng is_it_lessThanTwo
	
	is_it_lessThanTwo:	;input <= 2 then output the Input itself 
		cmp eax, 2  
		jle exit_Program_One	;ja-> output Input
		jmp findSumDiv_WithWhileLoop ; else start Prog1

	is_negative:
		imul eax,-1		; negative Input convert -> X (-1)
		jmp is_it_lessThanTwo	; try the test again

findSumDiv_WithWhileLoop: ;will find the sum of div using for 
        
        
        mov eax, 4711 ;For Test Only Input over 2 will resolve 4711


        ;Obada Code 




        jmp exit_Program_One
	exit_Program_One:
		ret




;**************************** Part2 **********************
mainWithtForLoop:

	push ebp			; calling convention save non-fluent registers and baspointer
	mov	ebp, esp
	push ebx

	push 0				; push 0 on stack for counting the divisor-count
	mov ecx, 1	    	; divisor counter
	mov ebx, [ebp+8]	; save in ebx because division result will overwrite eax

	;test Input (negative -> positive && Input ==0 then exit)
	
	cmp ebx,0			;test if the Input = 0 
	je	exit 			; if it is exit 

	cmp ebx, 0  		;test if the input equal or less than 0 negative
	je is_negative_2	; y? convert it and start the loop

	is_negative_2:
		imul ebx,-1		; negative Input convert -> X (-1)

	;end test Input

loop:
	mov eax, ebx		; put ebx into eax for division
	mov edx, 0			; set edx(modulo) zero otherwise error
	idiv ecx     		; dvide eax and edx with ecx
	cmp edx, 0			; compare stored edx modulo register with zero
	je  if				; jump to if condition if module comparison with 0 true
	cmp ecx, ebx    	; compare ecx loop iterator with input integer
	jae exit			; goto finish	
	inc ecx      		; Increment
	cmp ecx,ebx    		; Compare cx to the limit
	jle loop   			; Loop while less or equal
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
