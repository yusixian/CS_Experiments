DATAS SEGMENT
    msg db 'Please input string:',0dH,0aH,'$'	
    keynum = 20
    keybuf db keynum    ;缓冲区 最大20
    db 0
    db keynum dup(0)    ;20个字节都初始化为0 还有一个留给回车
    output db keynum dup(0)
DATAS ENDS
CODES SEGMENT
    ASSUME DS:DATAS, CS:CODES
START:
    mov ax, DATAS
    mov ds, ax
    lea dx, msg
    mov ah, 9
    int 21h     ;提示输入

    lea dx, keybuf
    mov ah, 10  
    int 21H ;10号功能 即0aH 输入缓冲区首字符在dx

    xor cx, cx  ;计数器cx清零
    mov si, offset keybuf+1
    mov cl, [si]
;将输入的字符串进行大写转换    
CHANG:inc si
    mov al, [si]
    cmp al, 'a'
    jb NEXT    
    cmp al, 'z'
    ja NEXT
    sub al, 20h     ;在'a'~'z'范围内 -20h变成大写 
    mov [si], al
NEXT: loop CHANG        ;循环调用
    mov byte ptr [si+1], '$'    ;在最后加个结束符号

    mov dl, 0dh
    mov ah, 2
    int 21h ;输出一个回车符
    mov dl, 0ah
    mov ah, 2
    int 21h ;输出一个换行符

    mov dx, offset keybuf+2 ;
    mov ah, 9
    int 21h ;输出转换后的字符串
CODES ENDS
END START