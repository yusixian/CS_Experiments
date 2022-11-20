package service;

import statics.MainApp;
import views.UserServiceView;

import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableColumn;
import javax.swing.table.TableModel;
import java.awt.*;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/*
 * 项目名: Exp_1.iml
 * 文件名: RefreshThread
 * 创建者: cos
 * 创建时间:2021/12/19 18:22
 * 描述: 实现订单自动刷新 线程
 */
public class RefreshThread extends Thread {
    @Override
    public void run() {
        while (true) {
            // 延时5s一次
            try {
                sleep(5000);
            } catch (InterruptedException e) {e.printStackTrace();}
            // 刷新表格数据
            LocalDateTime now = LocalDateTime.now();
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
            String refreshTime = "刷新于" + dtf.format(now);
            System.out.println(refreshTime);
            MainApp.userServiceView.setRefreshLabel(refreshTime);
        }
    }
}
