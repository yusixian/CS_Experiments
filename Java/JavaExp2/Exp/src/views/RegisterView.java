package views;

import service.UserService;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RegisterView {
    private JPanel mainPanel;
    private JTextField PassWordField;
    private JTextField UserNameField;
    private JButton RegistorButton;

    public RegisterView() {
        RegistorButton.addActionListener(new ActionListener() {
            /**
             * Invoked when an action occurs.
             *
             * @param e
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                System.out.println("注册按钮被点击了");
                String un = UserNameField.getText();
                String pw = PassWordField.getText();
                System.out.println("用户名：" + un);
                System.out.println("密码：" + pw);
                UserService userService = new UserService();
                if(userService.isRegisterOK(un, pw)) {
                    System.out.println("注册成功！");
                    JOptionPane.showMessageDialog(null,"注册成功！" );
                } else {
                    System.out.println("用户名已存在！");
                    JOptionPane.showMessageDialog(null,"用户名已存在！" );
                }
            }
        });
    }
    public static void main(String[] args) {
        JFrame frame = new JFrame("注册界面");
        frame.setContentPane(new RegisterView().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 使用 System exit 方法退出应用程序。仅在应用程序中使用。
        // 设置大小
        frame.setSize(500, 400);
        // 设置可见
        frame.setVisible(true);
    }
}
