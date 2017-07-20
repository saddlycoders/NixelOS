      [BITS 32]
org 0x7C00 
jmp start
nop
     OEM_ID                db 		"NixelOS    "
     BytesPerSector        dw 		0x0200
     SectorsPerCluster     db 		0x01
     ReservedSectors       dw 		0x187e
     TotalFATs             db 		0x02
     MaxRootEntries        dw 		0x0000
     NumberOfSectors       dw 		0x0000
     MediaDescriptor       db 		0xF8
     SectorsPerFAT         dw 		0x0000
     SectorsPerTrack       dw 		0x003F
     SectorsPerHead        dw 		0x0002
     HiddenSectors         dd 		0x00000000
     TotalSectors     	   dd 		0x20000		
     BigSectorsPerFAT      dd 		0x000003C1
     Flags                 dw 		0x0000
     FSVersion             dw 		0x0000
     RootDirectoryStart    dd 		0x000002
     FSInfoSector          dw 		0x0001
     BackupBootSector      dw 		0x0006

     TIMES 13 DB 0 ;jumping to next offset

     DriveNumber           db 		0x00
     Signature             db 		0x29
     VolumeID              dd 		0xFFFFFFFF
     VolumeLabel           db 		"BOOTLOADER"
     SystemID              db 		"FAT32   "
start: 
	mov ax, cs
	mov ds, ax
	;mov ss, ax
	
	mov [disk],dl;Диск с которого загргузились в Disk
	mov ah,0x08
	int 13h;Получаем информацию о диске
	mov ax,dx
	inc dh
	mov [SectorsPerHead],dh
	
	mov dx,[BigSectorsPerFAT+2]
	mov ax,[BigSectorsPerFAT]
	
	mov bx,[TotalFATs]
	mul bx
	
	add ax,[ReservedSectors]
	jnc next
	;Carry-флаг установлен, значит
	;AX переполнился, тогда в AX - остаток, а DX увеличиваем на 1
	inc dx
	next:
	;DX:AX - номер первого кластера корневого каталога
	;используем 4 байта после таблицы векторов прерываний чтобы обращатся к ней, не высчитывая номер корневой директории каждый раз
	
	
	
	mov [RootDirectoryStart+2],dx
	mov [RootDirectoryStart],ax
	mov eax,[RootDirectoryStart]
	mov di,0x400
	stosd
	;Пишем
	;call PrintHex
	mov bx,0x1000
	push bx
	call Read_Lba
	pop bx
	mov si,msg
	call PrintString;Сообщение о загрузке
	;Ищем загрузочный файл в корневом каталоге FAT
	;У нас по адресу 0x1000 занято 512 байт, т.е 0x200, значит по адресу 0x1200 можно сделать дополнительный буффер
	;DX:AX - текущий сектор
	mov si,0x1000
	;DS:SI текущая карточка
	Find_Loop:
		lodsb
		cmp al,0
		jz NotFound;Файлы в каталоге закончились
		mov di,0x1200
		stosb
		mov cx,10
		rep movsb
		mov di,0x1200
		pusha
		mov si,0x1200
		call PrintString
		mov si,endl
		call PrintString
		mov di,0x1200
		mov si,Loader_Name
		mov cx,11
		repe cmpsb
		popa
		
		jz found
		mov cx,21
		rep lodsb
		jmp Find_Loop
		
	NotFound:
		jmp Rerror
	found:
		;Нашли загрузчик
		;нам надо прочитать 15 байт
		mov cx,15
		rep lodsb
		lodsw
		dec ax
		dec ax
		;ax - начальный кластер файла
		mov cx,ax
		mov dx,[RootDirectoryStart+2]
		add ax,[RootDirectoryStart]
		mov bx,0x1000
		read_loop:
		jnc oopp
		;переполнение
		inc dx
		oopp:
		call Read_Lba
		call Get_NextCluster
		cmp dx,0x0FFF
		jnz oos
		cmp ax,0xFFFD
		jnz oos
		jmp ppi
		oos:
		add dx,[RootDirectoryStart+2]
		add ax,[RootDirectoryStart]
		add bx,0x200
		jmp read_loop
	ppi:
	mov dl,[disk];Передаем следующему загрузчику номер диска
	mov dh,[SectorsPerHead]
	mov ax,[SectorsPerTrack]
	mov bl,[SectorsPerCluster]
	mov cx,[ReservedSectors]
	jmp 0x0:0x1000
	jmp $
Get_NextCluster:
	;cx - кластер
	inc cx
	inc cx
	push cx
	push si
	push bx
	mov ax,cx
	and ax,0b1111111
	shl ax,2
	shr cx,7
	;cx - смещения сектора фат
	;ax - смещение байта в фате
	mov bx,ax
	mov ax,cx
	mov cx,bx
	mov dx,0
	add ax,[ReservedSectors]
	mov bx,0x800
	call Read_Lba
	mov si,0x800
	add si,cx
	mov ax,0
	lodsw
	mov dx,ax
	lodsw
	xchg ax,dx
	pop bx
	pop si
	pop cx
	dec ax
	dec ax
	mov cx,ax
	ret

Loader_Name db 'LOADER',0
;Читает Сектор DX:AX(LBA)
;ES:BX куда читать
Read_Lba:
	;mov ax,0
	;mov ax,0x420
	pusha
	xchg	ax, cx		; cx = a0
	mov	ax, [SectorsPerTrack]
	xchg	ax, si		; si = Scnt
	xchg	ax, dx		; ax = a1
	xor	dx, dx
	; dx:ax = 0:a1
	div	si		; ax = q1, dx = c1
	xchg	ax, cx		; cx = q1, ax = a0
	; dx:ax = c1:a0
	div	si		; ax = q2, dx = c2 = c
	inc	dx		; dx = Sector?
	xchg	cx, dx		; cx = c, dx = q1
	; dx:ax = q1:q2
	div	word [SectorsPerHead]	; ax = C (track), dx = H
	mov	dh, dl		; dh = H
	mov	ch, al
	ror	ah, 2
	or	cl, ah
	mov	ax, 0201h		; ah=2 - номер функции, al = 1 сектор
	mov	dl, [disk]
	int 13h
	jc Rerror
	popa
	ret
Rerror:
	jmp 0xFFFF:0x0;Перезагружаемся
PrintString:
	pusha
	mov ah,0x0e
	l:
		lodsb
		test al,al
		jz z
		int 10h
		jmp l
	z:
	popa
	ret
endl db 13,10,0
msg db 'Loading...',13,10,0
disk db 0
;times 510-($-$$) db 0 
db 0x55, 0xAA
db 0x52,0x52,0x61,0x41
times 480 db 0
db 0x72,0x72,0x41,0x61
dd -1
dd 0
times 12 db 0
dw 0
db 0x55,0xAA