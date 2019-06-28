.686

public _isSquare
.model flat
.stack

.data
	

.code
 
 _isSquare proc
push ebp
mov ebp,esp
mov eax,[ebp+8]
mov ebx,[ebp+12]
imul eax,ebx
mov ecx,1
cycle1:
inc ecx
push ecx
imul ecx,ecx
cmp ecx,eax
pop ecx
je _yes
jnge cycle1
jmp _end

_yes:
mov edi,[ebp+16]
mov eax,1
mov [edi],eax


_end:
pop ebp
ret
_isSquare endp


end