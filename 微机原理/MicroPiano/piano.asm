data segment
   io8255a      equ 288h    ;8255 A口    
   io8255c      equ 28aH    ;8255 C口
   io8255ctl    equ 28bh    ;8255 控制字
   io8254a      equ 280h    ;8254 A
   io8254b      equ 283h    ;8254 B
;    table dw 524,588,660,698,784,880,988,1048;高音
   table dw 493, 440, 392, 349, 329, 293, 261    ;2~8各个键对应频率（……re,do）
   table1    dw 0770h,0B70h,0D70h,0E70h,07B0h,0BB0h,0DB0h,0EB0h
           dw 07D0h,0BD0h,0DD0h,0ED0h,07E0h,0BE0h,0DE0h,0EE0h    ;键盘扫描码表
   key_in db 0h
   chars db '012345678'
   nowindex db 00h
   ;music1 两只老虎
    ;musicsnum db 32
    ;musics db 1,2,3,1, 1,2,3,1, 3,4,5, 3,4,5, 5,6,5,4,3,1, 5,6,5,4,3,1, 2,1,2, 2,1,2 ;乐谱中的各音符
    ;intervals db 2,2,2, 4, 2,2,2, 4, 2,2, 6, 2,2, 6, 2,3,2,2,2, 4, 2,3,2,2,2, 4, 2,2, 6, 2,2,6 ;各音符间隔延时 最后一个也算
    
    ;music2 欢乐颂
    ;musicsnum db 39
    ;musics db   3,3,4,5, 5,4,3,2, 1,1,2,3, 3,2,2, 3,3,4,5, 5,4,3,2, 1,1,2,3, 2,1,1 ,2,2,3,1, 2, 3,4, 3,1
    ;intervals db 2,2,2, 4,2,2,2, 4,2,2,2, 4,4,2, 4,2,2,2, 4,2,2,2, 4,2,2,2, 4,2,2, 6,2,2,2, 4, 2,2,2, 2, 4 
     
    ; music3 小星星
   musicsnum db 42
   musics db  1,1,  5,5,  6,6,5,   4,4, 3,3, 2,2, 1,   5,5,  4,4,  3,3, 2,   5,5, 4,4, 3,3, 2, 1,1 ,5,5, 6,6, 5,   4,4, 3,3, 2,2, 1
   intervals db 2,4,2,4,2,4,6, 2,4,2,4,2,4,6, 2,4,2,4,2,4,6, 2,4,2,4,2,4,6, 2,4,2,4,2,4,6, 2,4,2,4,2,4,6
   
   msg1 db 'Press 0,1,2,3,4,5,6,7,8,ESC:',0dh,0ah,'$'
   msg2 db 'Start mute, press again to release',0dh,0ah,'$'
   msg3 db 'Unmute',0dh,0ah,'$'
   msg4 db 'sing~',20h,'$'
   msg5 db 'song~',0dh,0ah,'$'
   msg6 db ' delay ','$'
   isMute db 01h        ;0静音状态 1为正常播放状态
   note db ?
data ends
code segment
assume cs:code,ds:data
start:                  ;主程序开始
    mov ax,data
    mov ds,ax
main:
    mov dx,offset msg1
    mov ah,9
    int 21h              ;显示提示信息msg1 等待输入
    call input           ;get a char in (key_in) and display it

    ; mov ah,7
    ; int 21h              ;从键盘接收字符 不回显
    
    mov al, key_in
    cmp al,1bh
    je finish            ;若为ESC 则转finish

    cmp al,'0'
    jl main
    cmp al,'8'
    jg main              ;若不在'0'-'8'之间重新输入
    
    cmp al,'0'           ;0则转放一首歌
    je gosong

    cmp al,'1'           ;1则转静音
    je mute

    call sing
    jmp main
gosong:
    call song
    jmp main
mute:                    ;静音
    mov al, isMute
    cmp al, 01h          ;若当前为播放状态 转到开启静音
    je startmute
    cmp al, 00h          ;若当前为静音状态 转到关闭静音
    je endmute
startmute:
    mov al, 00h
    mov isMute, al       ;开启静音状态

    mov dx,offset msg2
    mov ah,9
    int 21h               ;显示msg2 
    jmp main
endmute:
    mov al, 01h
    mov isMute, al       ;关闭静音状态

    mov dx,offset msg3
    mov ah,9
    int 21h              ;显示msg3
    jmp main
               
finish:                  ;主程序退出
    mov ax,4c00h
    int 21h

song proc near           ; 播放music中的乐曲
    push ax
    push dx
    push bx
    push cx
    
    mov al, isMute       
    cmp al, 00h
    je songover   
    
    mov dx,offset msg5
    mov ah,9
    int 21h               ; 显示msg5:song~

    mov al, 0
    mov nowindex, al
    mov cl, musicsnum   
    mov bx, offset musics
array: 
    mov al, 39h
    sub al, [bx]          ;al = 39h-当前音符（1-7）  为实际音符ascii码值
    call sing
    call songsdelay       ;根据nowindex 播放对应延时数量
    inc nowindex          ;延时表下标++
    inc bx
    loop array
    call printEndl
songover:
    pop cx
    pop bx
    pop dx
    pop ax
    ret
song endp

;播放al对应音符 如al = 38h（'8'）则放do
sing proc near          
    push ax
    push dx
    push bx
    mov note, al         
    mov al, isMute       
    cmp al, 00h
    je over              
    mov dx,offset msg4
    mov ah,9
    int 21h            
        
    mov al, note
    call print
    
    mov al, note
    sub al,32h
    shl al,1                ;转为查表偏移量，注意：频率值占两个字节
    mov bl,al               ;保存偏移到bx
    mov bh,0
    
    mov ax,4240H            ;计数初值 = 1000000 / 频率, 保存到AX
    mov dx,0FH
    div word ptr[table+bx]
    mov bx,ax         ;bx中也是计数初值
    
    mov dx,io8254b ;设置8254计时器0方式3, 先读写低字节, 再读写高字节
    mov al,00110110B
    out dx,al
    mov dx,io8254a         
    mov ax,bx
    out dx,al            ;写计数初值低字节
    
    mov al,ah
    out dx,al            ;写计数初值高字节

    mov dx,io8255ctl          ;设置8255 A口输出
    mov al,10000000B
    out dx,al
    
    mov dx,io8255a            
    mov al,03h
    out dx,al            ;置PA1PA0 = 11(开扬声器)
    call delay           ;延时
    mov al,0h
    out dx,al            ;置PA1PA0 = 00(关扬声器)

over:
    pop bx
    pop dx
    pop ax
    ret
sing endp

input proc near       ; get a char in (key_in) and display it  
    ;push dx
    ;push bx
    ;push cx
    ;push ax
    mov dx,io8255ctl            ;初始化8255控制字
    mov al,81h
    out dx,al    
key_loop:
        mov ah,1
        int 16h
        jnz exit                    ;pc键盘有键按下则退出
       
        mov dx,io8255c
        mov al,0fh
        out dx,al
        in al,dx                    ;读行扫描值
        and al,0fh
        cmp al,0fh
        jz key_loop                 ;未发现有键按下则转
        call delay                  ;delay for a moment
        mov ah,al
        mov dx,io8255ctl
        mov al,88h
        out dx,al
        mov dx,io8255c
        mov al,ah
        or al,0f0h
        out dx,al
        in al,dx                    ;读列扫描值
        and al,0f0h
        cmp al,0f0h
        jz key_loop                 ;未发现有键按下则转
        
        mov si,offset table1        ;键盘扫描码表首址
        mov di,offset chars          ;字符表首址
        mov cx,16                   ;待查表的表大小
key_tonext:
        cmp ax,[si]                 ;cmp (col,row) with every word
        jz key_findkey              ;in the table
        dec cx
        jz key_loop                 ;未找到对应扫描码
        add si,2
        inc di
        jmp key_tonext
key_findkey:
        mov dl,[di]
        mov ah,02
        int 21h            ;显示查找到的键盘码
        mov byte ptr key_in,dl
key_waitup:
        mov dx,io8255ctl
        mov al,81h
        out dx,al
        mov dx,io8255c
        mov al,0fh
        out dx,al
        in al,dx           ;读行扫描值
        and al,0fh
        cmp al,0fh
        jnz key_waitup     ;按键未抬起转
        call delay         ;delay for amoment
exit:        
    ;pop ax
    ;pop bx
    ;pop cx
    ;pop dx
    ;ret
input endp  

print proc near         
    push dx
    push bx
    push ax

    sub al,30h              
    and al ,0fH               
    xor ah,ah 
    lea bx, chars
    add bx, ax 
    mov dl,[bx]  
    mov ah,02H 
    int 21H

    mov dl, 20h
    mov ah,02H 
    int 21H
    
    pop ax
    pop bx
    pop dx
    ret
print endp    

printEndl proc near          
    push dx
    push ax

    mov dl, 0dh
    mov ah,02H 
    int 21H
    mov dl, 0ah
    mov ah,02H
    int 21H

    pop ax
    pop dx
    ret
printEndl endp   
 
songsdelay proc near       ;根据nowindex 播放对应延时数量
    push dx
    push cx
    push bx
    push ax
     
    xor ax, ax
    mov al, nowindex
    mov si, ax
    lea bx, intervals
    mov cl, [bx+si]
    dec cx
delayloop:
    call delay
    loop delayloop

    pop ax
    pop bx
    pop cx
    pop dx
songsdelay endp

delay proc near          ;delay for amoment
    push dx
    push cx
    push ax

       mov ax,22
x1:     mov cx,0ffffh
x2:     dec cx
    jnz x2
    dec ax    
    jnz x1

    mov dx,offset msg6
    mov ah,9
    int 21h              
    pop ax
    pop cx
    pop dx
    ret
delay endp

code ends
end start
