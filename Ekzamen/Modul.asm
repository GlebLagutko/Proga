.686

public @DecToBin@8
.model flat
.stack

NOD macro expression1, expression2

	mov ebx, expression2;
	mov eax, expression1;

	_begin:
	cmp eax,0
	je _end
	cmp eax,ebx
	cdq
	je _end;
	jg aGreater
	xchg eax,ebx
	idiv ebx
	mov eax,edx
	jmp _begin
	aGreater:
	idiv ebx;
	mov eax,edx;
	
	jmp _begin
	cdq;
	_end:
endm

.data
	

.code

@DecToBin@8 proc

     mov eax,ecx
	  mov ebx,edx
     mov ecx,16
	

	 
     loop1 : 
	 cmp eax,0
	 je _end
	 cdq
	 mov edi,2
	 idiv edi
	 mov dword ptr[ebx + ecx*4 - 4],edx
	 loop loop1
     _end:
	
	 ret 

@DecToBin@8 endp

end