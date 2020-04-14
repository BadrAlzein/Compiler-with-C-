
global mainWithWhileLoop ;find DivSum using while loop
global mainWithtForLoop ;find DivSum using For loop

;****************************Part 1 **********************

mainWithWhileLoop:
	mov eax, [esp + 4] ; get Input from Stack to eax
	cmp eax, -1  ;input < 0
	jle is_negative	;convert Input to positive and continue
	jng is_it_lessThanTwo
	
	is_it_lessThanTwo:	;input < 2 then output the Input itself 
		cmp eax, 2  
		jle exit_Program_One	;ja->output Input
		jmp findSumDiv_WithWhileLoop ; else start Prog1

	is_negative:
		imul eax,-1		; negative Input convert -> X (-1)
		jmp is_it_lessThanTwo	; try the test again

    findSumDiv_WithWhileLoop: ;will find the sum of div using for 
        
        
        mov eax, 4711 ;For Test Only

        ;Obada Code 




        jmp exit_Program_One
	exit_Program_One:
		ret




;**************************** Part2 **********************
mainWithtForLoop:
	mov eax, [esp + 4] ; get Input from Stack to eax
	cmp eax, -1  ;input < 0
	jle is_negative_Program2;convert Input to positive and continue
	jng is_it_lessThanTwo_Program2
	
	is_it_lessThanTwo_Program2:	;input < 2 then output the Input itself 
		cmp eax, 2  
		jle exit_Program_One	;ja->output Input
		jmp findSumDiv_WithForLoop ; else start Prog1

	is_negative_Program2:
		imul eax,-1		; negative Input convert -> X (-1)
		jmp is_it_lessThanTwo	; try the test again

    findSumDiv_WithForLoop: 
        
        


        ;Brishna Code 




        jmp exit_Program_Two
	exit_Program_Two:
		ret
