DATAS SEGMENT
DATAS ENDS
CODES SEGMENT
    ASSUME DS:DATAS, CS:CODES
START:
    mov ah, 1
    int 21h ;输入字符到al

    sub al, 20h

    mov dl, al
    mov ah, 2
    int 21h ;显示字符
CODES ENDS
END START