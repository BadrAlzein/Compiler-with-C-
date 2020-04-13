
global main
 
main:
	push ebp    ;push the basepointer to Stack 
	mov	ebp, esp   ;set the Top as the Base of the stack

;************* Start ***********************
    mov eax, [esp + 8]  ;giving the eax the value of the input (two Steps after the ebp and the retunValue on the Stack)
    push esi ; saving the Value of esi in Stack (nach gcc-Convention)
    push edi ; saving the Value of edi in Stack (nach gcc-Convention)
    push edx ; saving the Value of edx in Stack (nach gcc-Convention)

;+++++++++++++++++++++++++Test Input ++++++++++++++++++++

;Step 1) TEST THE INPUT
    cmp eax,eax    ;test Input if its Signed/unsigned
    jle is_negative  ; Input is 0 or lower
    jge is_bigger_Than_Two   ; check if input is 1

;Step 1-1)is_negative::negative -> pos.
is_negative:   ; if Input is negative multi by (-1)
    imul eax,-1

;Step 1-2) is_bigger_Than_Two::POSTIVE Input BUT check if its grater than one or two
is_bigger_Than_Two:
    cmp eax, 2 
      jle exit  ; return eax if the Input =< 2
      jge findSumDiv  ; start the Operatione for Input > 2

;+++++++++++++++++++++++++ Start ++++++++++++++++++++++

;Step 2) GET THE DEVIDERS for Positive Input>2
findSumDiv:  ; this will finde the sum of the Divs
    ;init the loop 1
        
        
        
; 3) save the Input in eax and return it 
exit: 
    mov eax, eax 
    ret
    
;****************************End **********************
;this will clean the Stack 
	mov	eax, 0  ;claaen up eax
	pop	ebp     ; push the base out 
	ret

