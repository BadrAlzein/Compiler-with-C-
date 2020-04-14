
global mainWithWhileLoop ;find DivSum using while loop
global mainWithtForLoop ;find DivSum using For loop

;****************************Part 1 **********************

mainWithWhileLoop:
	mov eax, [esp + 4] ; get Input from Stack to eax
	cmp eax, 2  ;input < 2 then output the Input itself 
	jle exit_Program_One
	jng findSumDiv_WithWhileLoop ; else start Prog1

    findSumDiv_WithWhileLoop: 
        
        
        mov eax, 4711 ;For Test Only

        ;Obada Code 




        jmp exit_Program_One
	exit_Program_One:
		ret




;**************************** Part2 **********************
mainWithtForLoop:
	mov eax, [esp + 8] 
	cmp eax, 2
	jle exit_Program_Two
	jng findSumDiv_WithForLoop 

    findSumDiv_WithForLoop: 
        
        


        ;Brishna Code 




        jmp exit_Program_Two
	exit_Program_Two:
		ret
