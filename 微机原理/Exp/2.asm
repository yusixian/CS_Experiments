DATAS SEGMENT
    ASCII    db 30h,31h,32h,33h,34h,35h,36h,37h,38h,39h
    ;对应0 ~ 9的ASCII码
    ASCII2 db 41h,42h,43h,44h,45h,46h
    ;对应A ~ F的ASCII码 41h~5ah
    hex    db 01h
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
    mov bx,offset ASCII
    ;BX指向ASCII码表
    mov CL, 10  
    mov al,hex;AL取得一位16进制数，为ASCII码表中的位移
    and al,0fh    ;只有低4位是有效的，高4位清0
    s:  xlat ;换码：AL←DS:[BX＋AL]
        mov dl,al    ;欲显示的ASCII码送DL
        mov ah,2    ;02号DOS功能调用
        int 21h    ;显示一个ASCII码字符
        inc al  ;al++
    loop s ;CX-1 判断是否为0，否则跳转至s

    mov bx,offset ASCII2    
    mov CL, 6   
    mov al, hex     
    and al,0fh    ;只有低4位是有效的，高4位清0
    s2: xlat ;换码：AL←DS:[BX＋AL]
        mov dl,al    ;欲显示的ASCII码送DL
        mov ah,2    ;02号DOS功能调用
        int 21h    ;显示一个ASCII码字符
        inc al  ;al++
    loop s2 ;CX-1 判断是否为0，否则跳转至s2

    MOV AH,4CH
    INT 21H
CODES ENDS
END START
