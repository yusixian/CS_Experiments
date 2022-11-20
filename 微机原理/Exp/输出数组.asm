DATAS SEGMENT
   musics db 1,2,3,1, 1,2,3,1, 3,4;乐谱中的各音符
   musicsnum db 10
   chars db '012345678'
    ;假设两个数据;此处输入数据段代码  
DATAS ENDS
  
STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    mov cl, musicsnum    ;循环次数放入
    mov bx, offset musics
array: 
    mov al, [bx]
    call print
    inc bx
    loop array
    
    mov ax,4c00h
    int 21h

print proc near          ;输出al 1234567
    push dx
    push bx
    push ax

    sub al,30h              ;30h为ASCII中0的值 0、1有别的功能
    and al ,0fH               ;用与操作将al高四位清0
    xor ah,ah ;AH清0
    lea bx, chars ;获取变量偏移地址（有效地址）
    add bx, ax ;BX+AX的地址存入BX(注意是地址)
    mov dl,[bx]  ;将BX所在地址的值送到DL中
    mov ah,02H ;键盘回显DL中的内容
    int 21H

    mov dl, 0dh
    mov ah,02H ;键盘回显DL中的内容
    int 21H
    mov dl, 0ah
    mov ah,02H ;键盘回显DL中的内容
    int 21H

    pop ax
    pop bx
    pop dx
    ret
print endp    

CODES ENDS
END START
