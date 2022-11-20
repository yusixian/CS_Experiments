package internet;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

/*
 * 项目名: Exp
 * 文件名: Client
 * 创建者: cos
 * 创建时间:2021/12/19 19:19
 * 描述: 客户端类
 */
public class Client extends Thread{
    public static void main(String[] args) {
        try {
            System.out.println("客户端启动");
            Socket socket = new Socket("127.0.0.1",20000);

            System.out.println("向服务端发送信息：购买1桶水");
            PrintStream pStream = new PrintStream(socket.getOutputStream());
            pStream.println("购买1桶水");
            pStream.flush();

            System.out.println("等待接收服务端消息ing...");
            BufferedReader br =new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String msg = br.readLine();
            System.out.println("来自服务器的数据："+msg);

            pStream.close();
            br.close();
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

