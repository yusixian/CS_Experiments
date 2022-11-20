package util;

import util.DBUtil;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

public class BatchUtil {
    /**
     * 事务的开始
     * @param sqls 多条sql语句
     * @return 事务提交成功与否 否则回滚
     */
    public static boolean batchExecute(String[] sqls) {
        // 创建DBUtil对象
        DBUtil db = new DBUtil();
        Connection conn = null;
        try {
            conn = db.getConnection();
            boolean autoCommit = conn.getAutoCommit();
            System.out.println("事务自动提交状态： " + autoCommit);
            if(autoCommit) {
                // 关闭自动提交 开始事务
                conn.setAutoCommit(false);
                System.out.println("已关闭自动提交，事务开始");
            }


            conn.setAutoCommit(autoCommit); // 恢复原有事务提交状态
            db.closeAll();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            if(conn != null) {
                try {
                    conn.rollback();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
            }
            return false;
        }
    }

}
