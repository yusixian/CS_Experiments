package views;

import dao.entity.User;
import service.UserService;
import statics.NowUser;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StartMenusView {
    private JPanel mainpanel;
    private JTextField UserNameField;
    private JPasswordField PasswordField;
    private JButton LoginButton;
    private JButton RegisterButton;

    public StartMenusView() {
        LoginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("登录按钮被点击了");
                String un = UserNameField.getText();
                String pw = String.valueOf( PasswordField.getPassword() );
                System.out.println("用户名：" + un);
                System.out.println("密码：" + pw);
                UserService userService = new UserService();
                User user = userService.login(un, pw);
                if(user != null) {
                    NowUser.initNowUser(user);
                    System.out.println("登录成功！");
                    JOptionPane.showMessageDialog(null,"登录成功！" );
                } else {
                    System.out.println("用户名或密码错误！");
                    JOptionPane.showMessageDialog(null,"用户名或密码错误！" );
                }
            }
        });
        RegisterButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("注册按钮被点击了");
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("newSystem");
        frame.setContentPane(new StartMenusView().mainpanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 使用 System exit 方法退出应用程序。仅在应用程序中使用。
        // 设置大小
        frame.setSize(500, 400);
        // 设置可见
        frame.setVisible(true);
    }
}
