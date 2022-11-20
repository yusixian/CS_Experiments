DATAS SEGMENT
    LEDtable db 0c0h,0f9h,0a4h,0b0h,99h,92h,82h,0f8h
			db 80h,90h,88h,83h,0c6h,0c1h,86h,8eh
    LEDnum db ?
DATAS ENDS
CODES SEGMENT
    ASSUME DS:DATAS, CS:CODES
START:
    mov ah, 1
    int 21h ;输入字符到al
    ;mov al, LEDnum
    mov bx, offset LEDtable
    xlat    ;换码 AL←DS:[BX＋AL]
    mov dl, al
    mov ah, 2
    int 21h ;显示字符
CODES ENDS
END START