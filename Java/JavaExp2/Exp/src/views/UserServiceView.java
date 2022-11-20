package views;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableColumn;
import javax.swing.table.TableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UserServiceView {
    private JPanel mainPanel;
    private JTable ProductsTable;
    private JScrollPane scrollPane;
    private JTextField ProductNumField;
    private JButton ConfirmButton;

    public UserServiceView() {
        intiComponent();
        ConfirmButton.addActionListener(new ActionListener() {
            /**
             * Invoked when an action occurs.
             *
             * @param e
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                int num = Integer.parseInt(ProductNumField.getText());
                System.out.println("点击了下单按钮！");
                System.out.println("下单数量为:" + num);
            }
        });
    }
    /**
     * 初始化窗体组件
     */
    private void intiComponent()
    {
        /*
         * 设置JTable的列名
         */
        String[] columnNames = { "产品编号", "产品名称", "产品单价", "产品库存" };
        String[] names = {"农夫山泉", "娃哈哈", "雀巢"};
        /*
         * 初始化JTable里面各项的值，设置两个一模一样的实体"赵匡义"学生。
         */
        Object[][] obj = new Object[3][4];
        for (int i = 0; i < 3; i++)  {
            obj[i][0] = i;
            obj[i][1] = names[i];
            obj[i][2] = 20+i*4;
            obj[i][3] = 2000+i*100;
        }
        System.out.println(obj);
        /*
         * JTable的其中一种构造方法
         */
        TableModel dataModel = new DefaultTableModel(obj,columnNames);
        ProductsTable.setModel(dataModel);
        JTableHeader head = ProductsTable.getTableHeader(); // 创建表格标题对象
        head.setPreferredSize(new Dimension(head.getWidth(), 35));// 设置表头大小
        head.setFont(new Font("楷体", Font.PLAIN, 24));// 设置表格字体
        ProductsTable.setRowHeight(30);
        /*
         * 设置JTable的列默认的宽度和高度
         */
        TableColumn column = null;
        int colunms = ProductsTable.getColumnCount();
        for(int i = 0; i < colunms; i++)
        {
            column = ProductsTable.getColumnModel().getColumn(i);
            /*将每一列的默认宽度设置为100*/
            column.setPreferredWidth(100);

        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("桶装水下单系统");
        frame.setContentPane(new UserServiceView().mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// 使用 System exit 方法退出应用程序。仅在应用程序中使用。
        // 设置大小
        frame.setSize(1000, 600);
        // 设置可见
        frame.setVisible(true);
    }
}
