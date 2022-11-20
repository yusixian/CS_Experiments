; 查询输入接口
mov dx, 5001h       ;DX指向状态端口
STATUS: in al, dx   ;读状态端口
        test al, 01h;测试标志位D0
        jz STATUS   ;D0 = 0，未准备好，继续查询
        dec dx      ;D0 = 1 准备好，DX-1,指向数据端口
        in al, dx   ;从数据端口输入数据
;查询输出接口
mov dx, 5001h       ;DX指向状态端口
STATUS: in al, dx   ;读状态端口
        test al, 80h;测试标志位D7
        jnz STATUS  ;D7＝1，未就绪，继续查询
        inc dx      ;D7＝0，就绪，DX指向数据端口
        mov al, buf ;变量buf送AL
        out dx, al  ;将数据输出给数据端口