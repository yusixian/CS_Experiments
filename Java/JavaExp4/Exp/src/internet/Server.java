package internet;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

/*
 * 项目名: Exp
 * 文件名: Server
 * 创建者: cos
 * 创建时间:2021/12/19 19:21
 * 描述: 服务器端类
 */
public class Server extends Thread{
    private int port;
    ServerSocket serverSocket;
    int num = 100;
    public Server(){
        try {
            port = 20000;
            serverSocket =new ServerSocket(20000);
            this.start();
            System.out.println("服务器启动成功，现有"+num+"桶水");
        }catch (Exception e) {
            System.out.println("服务器启动失败");
            e.printStackTrace();
        }
    }
    public void run() {
        while(this.isAlive()) {
            try {
                Socket socket = serverSocket.accept();

                BufferedReader  br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String lineString = br.readLine();
                System.out.println("接收了来自客户端的消息:" + lineString);

                System.out.println("向客户端发送消息：剩余桶装水数目" + --num);
                PrintStream pStream = new PrintStream(socket.getOutputStream());
                pStream.println("剩余桶装水数目" + num);
                pStream.flush();
                System.out.println("发送成功！");

                br.close();
                pStream.close();
                socket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
    public static void main(String[] args) {
        Server server = new Server();
    }
}
