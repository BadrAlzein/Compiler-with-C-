
global mainWithWhileLoop ;find DivSum using while loop
global mainWithtForLoop ;find DivSum using For loop

;****************************Part 1 **********************
mainWithWhileLoop:
	push ebp    ;push the basepointer to Stack 
	mov	ebp, esp   ;set the Top as the Base of the stack
    mov eax, [esp + 4]  ;giving the eax the value of the input (one Steps after the ebp)

;+++++++++++++++++++++++++ Test Input ++++++++++++++++++++
;Step 1) TEST THE INPUT
    cmp eax,eax    ;test Input if its Signed/unsigned
    jle is_negative  ; Input is 0 or lower
    jge is_bigger_Than_One   ; check if input is 1

;Step 1-1)is_negative::negative -> pos.
is_negative:   ; if Input is negative multi by (-1) 
    imul eax,-1
    jmp is_bigger_Than_One

;Step 1-2) is_bigger_Than_Two::POSTIVE Input BUT check if its grater than one or two
is_bigger_Than_One:
    cmp eax, 1 
      jle Out_One  ; return eax if the Input =< 2
      jge is_bigger_Than_Two  ; start the Operatione for Input > 2

is_bigger_Than_Two:
    cmp eax, 2 
      jle Out_Two  ; return eax if the Input =< 2
      jge findSumDiv  ; start the Operatione for Input > 2

;+++++++++++++++++++++++++ Start ++++++++++++++++++++++

;Step 2) GET THE DEVIDERS for Positive Input>2
findSumDiv:  ; this will finde the sum of the Divs using while loop

    ;Obada Code is Here 





    mov eax, 1000
    jmp exit
        
        
; 3) save the Input in eax and return it 
Out_One:
    mov eax,1 
    jmp exit
Out_Two:
    mov eax,2 
    jmp exit
exit: 
;this will clean the Stack 
	pop	ebp     ; push the base out 
	ret

;**************************** Part2 **********************

mainWithtForLoop:
	push ebp    ;push the basepointer to Stack 
	mov	ebp, esp   ;set the Top as the Base of the stack
    mov eax, [esp + 8]  ;giving the eax the value of the input (two Steps after the ebp and the retunValue on the Stack)


    ; code Brishna here 




    jmp exit 

