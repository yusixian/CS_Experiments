; 编制程序完成12H、45H、F3H、6AH、20H、FEH、90H、C8H、57H和34H共10个无符号字节数据之和，并将结果存入字节变量SUM中（不考虑进位）。
DATAS SEGMENT
    b_data db 12H,45H,0f3H,6AH,20H,0FEH,90H,0C8H,57H,34H
    num db 10
    sum db ?
DATAS ENDS
  
CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    mov ax, DATAS
    mov ds, ax
    xor si, si
    xor al, al  ;si、al清零
    lea si, b_data
    mov cl, num
again: add al, b_data[si]
    inc si
    loop again
    mov sum, al
CODES ENDS
END START
