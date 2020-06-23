;
;	to compile this code
;	first create an object file
;	nasm -f elf -o main.o main-nasm.asm
;
;	to create an executeable, link it
;	gcc -m32 -o run main.o
;
;	run it:
;	./run

global getDivisorCount
global _getDivisorCount

; return amount of integer division numbers
getDivisorCount:
	mov eax, [esp + 4]
	cmp eax, 0
	je finished
	; compare and check if input is below 0 -> if yes unsign it
	cmp eax, 0
	jl unsign
	jmp unsigned
	; multiply signed value with -1
	unsign: 
		imul eax, -1
	unsigned:
	cmp eax, 1
	je finished
	cmp eax, 2
	je two
	; initialize the loop index i
	mov ecx, eax
	; push index i on stack
	push ecx
	; catch errors so that unsigned int handed over
	; use while loop and no basepointer
	; ecx is the counting register and at the beginning its the hand over value
	; sum of divisors got at least one divisor itself
	push 1 
	jmp whileloop
	two:
		mov eax, 2
		mov eax, eax
		ret
	modiszero:
		; sum of divisors -> stackpointer shows the last element
		pop eax
		pop ecx
		; if index is 0 leave the whileloop
		cmp ecx, 0
		je finished
		; increment the sumDivisors
		inc eax
		push ecx
		push eax
	whileloop:
		; input value 
		mov eax, [esp + 12]
		cmp eax, 0
		jl signed2
		jmp unsigned5
		signed2: 
			imul eax, -1
		unsigned5:
		; modulo operation
		mov edx, 0
		div ecx
		
		pop eax
		pop ecx
		; ecx is the integer index 
		dec ecx
		push ecx
		push eax
		
		cmp edx, 0
		je modiszero
		cmp ecx, 0
		; jump if not 0 (jump not equal ecx is 0)
		jne whileloop
	finished:
		; store sumdivisors in return register eax
		mov eax, eax
		ret

_getDivisorCount:
	; with for loop and use basepointer
	push ebp
	mov ebp, esp
	; input value
	mov edi, 1
	mov eax, [ebp + 8]
	cmp eax, 0
	je zero
	; guaranteed positive value in eax
	; push eax
	; result int pointer point initial on value 0 -> in [ebp is the adress -> intptr result
	; sum of divisors got at least one divisor itself
	; push 1
	; int i = value for iteration through for loop
	mov ecx, eax
	cmp eax, 1
	je finished3
	cmp eax, 2
	je finished7
	jmp for
	zero:
		; ebx speichern 
		mov edi, 0
		push ebx
		mov ebx, [ebp + 12]                  
        	mov [ebx], edi
		pop ebx
		mov ebp, esp
		pop ebp
		ret
	finished7:
		push ebx
		mov eax, 2
		pop ebx
	finished3:
		push ebx
		; point on sum of divisors with handed pointer   
		; mov [ebp + 4], eax 
		; the pointer is before value so higher                  
        	mov ebx, [ebp + 12]                  
        	mov [ebx], edi
		pop ebx
		; leave does the same
		mov ebp, esp
		pop ebp
		ret
	modiszero3:
		; sum of divisors ++ 
		; pop eax
		; inc eax
		; push eax
		inc edi
		loop for
	for:
		mov eax, [ebp + 8]
		; needed for modulo because edx could be 64 bit and to big for div
		mov edx, 0
		; i
		cmp ecx, 1 
		je finished3
		div ecx

		; value mod i == 0
		cmp edx, 0
		je modiszero3
	; i < value
	; mov ecx, [ebp - 12]
	; cmp ecx, [ebp - 4]
	loop for
	jmp finished3
