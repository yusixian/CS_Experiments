data segment
   io8255a      equ 288h    ;8255 A��    
   io8255c      equ 28aH    ;8255 C��
   io8255ctl    equ 28bh    ;8255 ������
   io8254a      equ 280h    ;8254 A
   io8254b      equ 283h    ;8254 B
;    table dw 524,588,660,698,784,880,988,1048;����
   table dw 493, 440, 392, 349, 329, 293, 261    ;2~8��������ӦƵ�ʣ�����re,do��
   table1    dw 0770h,0B70h,0D70h,0E70h,07B0h,0BB0h,0DB0h,0EB0h
           dw 07D0h,0BD0h,0DD0h,0ED0h,07E0h,0BE0h,0DE0h,0EE0h    ;����ɨ�����
   key_in db 0h
   chars db '012345678'
   nowindex db 00h
   ;music1 ��ֻ�ϻ�
    ;musicsnum db 32
    ;musics db 1,2,3,1, 1,2,3,1, 3,4,5, 3,4,5, 5,6,5,4,3,1, 5,6,5,4,3,1, 2,1,2, 2,1,2 ;�����еĸ�����
    ;intervals db 2,2,2, 4, 2,2,2, 4, 2,2, 6, 2,2, 6, 2,3,2,2,2, 4, 2,3,2,2,2, 4, 2,2, 6, 2,2,6 ;�����������ʱ ���һ��Ҳ��
    
    ;music2 ������
    ;musicsnum db 39
    ;musics db   3,3,4,5, 5,4,3,2, 1,1,2,3, 3,2,2, 3,3,4,5, 5,4,3,2, 1,1,2,3, 2,1,1 ,2,2,3,1, 2, 3,4, 3,1
    ;intervals db 2,2,2, 4,2,2,2, 4,2,2,2, 4,4,2, 4,2,2,2, 4,2,2,2, 4,2,2,2, 4,2,2, 6,2,2,2, 4, 2,2,2, 2, 4 
     
    ; music3 С����
   musicsnum db 42
   musics db  1,1,  5,5,  6,6,5,   4,4, 3,3, 2,2, 1,   5,5,  4,4,  3,3, 2,   5,5, 4,4, 3,3, 2, 1,1 ,5,5, 6,6, 5,   4,4, 3,3, 2,2, 1
   intervals db 2,4,2,4,2,4,6, 2,4,2,4,2,4,6, 2,4,2,4,2,4,6, 2,4,2,4,2,4,6, 2,4,2,4,2,4,6, 2,4,2,4,2,4,6
   
   msg1 db 'Press 0,1,2,3,4,5,6,7,8,ESC:',0dh,0ah,'$'
   msg2 db 'Start mute, press again to release',0dh,0ah,'$'
   msg3 db 'Unmute',0dh,0ah,'$'
   msg4 db 'sing~',20h,'$'
   msg5 db 'song~',0dh,0ah,'$'
   msg6 db ' delay ','$'
   isMute db 01h        ;0����״̬ 1Ϊ��������״̬
   note db ?
data ends
code segment
assume cs:code,ds:data
start:                  ;������ʼ
    mov ax,data
    mov ds,ax
main:
    mov dx,offset msg1
    mov ah,9
    int 21h              ;��ʾ��ʾ��Ϣmsg1 �ȴ�����
    call input           ;get a char in (key_in) and display it

    ; mov ah,7
    ; int 21h              ;�Ӽ��̽����ַ� ������
    
    mov al, key_in
    cmp al,1bh
    je finish            ;��ΪESC ��תfinish

    cmp al,'0'
    jl main
    cmp al,'8'
    jg main              ;������'0'-'8'֮����������
    
    cmp al,'0'           ;0��ת��һ�׸�
    je gosong

    cmp al,'1'           ;1��ת����
    je mute

    call sing
    jmp main
gosong:
    call song
    jmp main
mute:                    ;����
    mov al, isMute
    cmp al, 01h          ;����ǰΪ����״̬ ת����������
    je startmute
    cmp al, 00h          ;����ǰΪ����״̬ ת���رվ���
    je endmute
startmute:
    mov al, 00h
    mov isMute, al       ;��������״̬

    mov dx,offset msg2
    mov ah,9
    int 21h               ;��ʾmsg2 
    jmp main
endmute:
    mov al, 01h
    mov isMute, al       ;�رվ���״̬

    mov dx,offset msg3
    mov ah,9
    int 21h              ;��ʾmsg3
    jmp main
               
finish:                  ;�������˳�
    mov ax,4c00h
    int 21h

song proc near           ; ����music�е�����
    push ax
    push dx
    push bx
    push cx
    
    mov al, isMute       
    cmp al, 00h
    je songover   
    
    mov dx,offset msg5
    mov ah,9
    int 21h               ; ��ʾmsg5:song~

    mov al, 0
    mov nowindex, al
    mov cl, musicsnum   
    mov bx, offset musics
array: 
    mov al, 39h
    sub al, [bx]          ;al = 39h-��ǰ������1-7��  Ϊʵ������ascii��ֵ
    call sing
    call songsdelay       ;����nowindex ���Ŷ�Ӧ��ʱ����
    inc nowindex          ;��ʱ���±�++
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

;����al��Ӧ���� ��al = 38h��'8'�����do
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
    shl al,1                ;תΪ���ƫ������ע�⣺Ƶ��ֵռ�����ֽ�
    mov bl,al               ;����ƫ�Ƶ�bx
    mov bh,0
    
    mov ax,4240H            ;������ֵ = 1000000 / Ƶ��, ���浽AX
    mov dx,0FH
    div word ptr[table+bx]
    mov bx,ax         ;bx��Ҳ�Ǽ�����ֵ
    
    mov dx,io8254b ;����8254��ʱ��0��ʽ3, �ȶ�д���ֽ�, �ٶ�д���ֽ�
    mov al,00110110B
    out dx,al
    mov dx,io8254a         
    mov ax,bx
    out dx,al            ;д������ֵ���ֽ�
    
    mov al,ah
    out dx,al            ;д������ֵ���ֽ�

    mov dx,io8255ctl          ;����8255 A�����
    mov al,10000000B
    out dx,al
    
    mov dx,io8255a            
    mov al,03h
    out dx,al            ;��PA1PA0 = 11(��������)
    call delay           ;��ʱ
    mov al,0h
    out dx,al            ;��PA1PA0 = 00(��������)

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
    mov dx,io8255ctl            ;��ʼ��8255������
    mov al,81h
    out dx,al    
key_loop:
        mov ah,1
        int 16h
        jnz exit                    ;pc�����м��������˳�
       
        mov dx,io8255c
        mov al,0fh
        out dx,al
        in al,dx                    ;����ɨ��ֵ
        and al,0fh
        cmp al,0fh
        jz key_loop                 ;δ�����м�������ת
        call delay                  ;delay for a moment
        mov ah,al
        mov dx,io8255ctl
        mov al,88h
        out dx,al
        mov dx,io8255c
        mov al,ah
        or al,0f0h
        out dx,al
        in al,dx                    ;����ɨ��ֵ
        and al,0f0h
        cmp al,0f0h
        jz key_loop                 ;δ�����м�������ת
        
        mov si,offset table1        ;����ɨ�������ַ
        mov di,offset chars          ;�ַ�����ַ
        mov cx,16                   ;�����ı��С
key_tonext:
        cmp ax,[si]                 ;cmp (col,row) with every word
        jz key_findkey              ;in the table
        dec cx
        jz key_loop                 ;δ�ҵ���Ӧɨ����
        add si,2
        inc di
        jmp key_tonext
key_findkey:
        mov dl,[di]
        mov ah,02
        int 21h            ;��ʾ���ҵ��ļ�����
        mov byte ptr key_in,dl
key_waitup:
        mov dx,io8255ctl
        mov al,81h
        out dx,al
        mov dx,io8255c
        mov al,0fh
        out dx,al
        in al,dx           ;����ɨ��ֵ
        and al,0fh
        cmp al,0fh
        jnz key_waitup     ;����δ̧��ת
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
 
songsdelay proc near       ;����nowindex ���Ŷ�Ӧ��ʱ����
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
