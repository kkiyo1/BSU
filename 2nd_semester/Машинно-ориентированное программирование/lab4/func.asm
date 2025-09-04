.386
.model flat, C

.code
compare proc C
    mov esi, [esp+4]
    mov edi, [esp+8]
    mov ecx, [esp+12]
compare_loop:
    mov al, [esi]
    mov bl, [edi]
    cmp al, bl
    jne not_equal
    inc esi
    inc edi
    loop compare_loop
equal:
    mov eax, 1
    ret
not_equal:
    xor eax, eax
    ret
compare endp



copy proc C
    mov edi, [esp+4]
    mov esi, [esp+8]
    mov ecx, [esp+12]
copyloop:
    mov al, [esi]
    mov [edi], al
    inc esi
    inc edi
    loop copyloop
done:
    ret
copy endp



insert proc C
    mov edi, [esp+4]
    movzx eax, byte ptr [esp+8] ; перемещение с расшиернием 1 байта из esp+8
    mov edx, [esp+12]
    add edi, edx
    mov [edi], al
    ret
insert endp



search proc C
    mov esi, [esp+4]
    mov edi, esi
    movzx edx, byte ptr [esp+8]
searchloop:
    cmp byte ptr [esi], 0
    je not_found
    cmp byte ptr [esi], dl
    je found
    inc esi
    jmp searchloop
found:
    sub esi, edi
    mov eax, esi
    ret
not_found:
    mov eax, -1
    ret
search endp
end
