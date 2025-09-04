.386
.model flat, C

.code
first_asm proc C x:dword, a:dword
	mov eax, a
	imul eax
	jo metka2
	mov ebx, 7
	imul ebx
	jo metka2
	mov ecx, eax
	cmp ecx, 0
	
	jz metka1
	mov eax, x
	imul eax
	jo metka2
	imul x
	jo metka2
	add eax, 3
	jo metka2
	cdq
	idiv ecx
	mov ecx, eax
	xor eax, eax
	mov eax, x
	cdq
	mov ebx, 2
	idiv ebx
	add ecx, eax
	jmp finish
metka1:
	mov ah, 1
	jmp finish
metka2:
	mov bh, 1
finish:
	ret
	
first_asm endp
end