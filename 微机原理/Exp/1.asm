DATAS SEGMENT 
    string db 'Hello, Assembly!', 0dh, 0ah, '$'
DATAS ENDS
CODES SEGMENT
    ASSUME DS:DATAS, CS:CODES
start:
mov ax, datas
mov ds, ax
mov dx, offset string
mov ah, 9h
int 21h
mov ah, 4ch
int 21h
CODES ENDS
end start