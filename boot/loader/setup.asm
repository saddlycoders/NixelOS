  [BITS 16]

setup:
    mov  ax, cs
    mov  ds, ax
    mov  es, ax
    mov  ss, ax
    mov  sp, setup
    mov  bp, sp
    mov ax,12h
	int 10h
  
	jmp $
os_print_string:
	pusha

	mov ah, 0Eh			; int 10h teletype function

.repeat:
	lodsb				; Get char from string
	cmp al, 0
	je .done			; If char is zero, end of string

	int 10h				; Otherwise, print it
	jmp .repeat			; And move on to next char

.done:
	popa
	ret
section .data
   vbe_not_supp     db '[VBE]Controller not supported.',13,10,0
   vbe_found_mode   db '[VBE]Support Video Mode found.',13,10,0
   vbe_ok           db '[VBE]Setting new video mode: [OK]',13,10,0