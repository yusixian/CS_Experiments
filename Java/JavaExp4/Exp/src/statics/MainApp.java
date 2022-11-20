package statics;

import service.RefreshThread;
import views.UserServiceView;

import javax.swing.*;

/*
 * 项目名: Exp_1.iml
 * 文件名: MainApp
 * 创建者: cos
 * 创建时间:2021/12/19 18:48
 * 描述: 主程序
 */
public class MainApp  {
    public static JFrame userServiceFrame;
    public static UserServiceView userServiceView;
    static {
        userServiceFrame = new JFrame("桶装水下单系统");
        userServiceView = new UserServiceView();
        userServiceFrame.setContentPane(userServiceView.getMainPanel());
        userServiceFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 使用 System exit 方法退出应用程序。仅在应用程序中使用。
        // 设置大小
        userServiceFrame.setSize(1000, 600);
    }
    public static void main(String[] args) {
        // 设置可见
        userServiceFrame.setVisible(true);
        RefreshThread refreshThread = new RefreshThread();
        refreshThread.start();
        Timer timmer = new Timer(5000, userServiceView);
        //5000为间隔时间5s 第二个参数为工作类 须实现actionPerformed
        timmer.start();
        //开启定时器，开始后，每5秒执行一次actionPerformed方法中的代码
    }
}
