array db 10, -3,0,20,900,587,-632,777,234,-34,-56
maxay dw ? ;最大值
minay dw ? ;最小值
lea si, array
mov cx, [si]    ;循环次数放入
dec cx
add si, 2
mov ax, [si]
mov bx, [si]
maxck: add si, 2
    cmp [si], ax
    jle minck
    mov ax, [si]
    jmp next
minck:
    cmp [si], bx
    jge next
    mov bx, [si]
    jmp next
next:
    loop maxck
    mov maxay, ax
    mov minay, bx


