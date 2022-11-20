package util;
import config.Config;

import java.lang.reflect.Field;
import java.sql.*;
import java.util.List;

public class DBUtil {
    private static String URL;
    private static String USER;
    private static String PASSWORD;
    private static String DRIVER;
    private PreparedStatement ps;
    private Connection connection;  //数据库连接对象
    private ResultSet resultSet;    //查询结果集
    private boolean autoCommit;
    public DBUtil() {
        DRIVER = Config.getValue("driver");
        URL = Config.getValue("url");
        USER = Config.getValue("user");
        PASSWORD = Config.getValue("pwd");
    }
    /**
     * 获取数据库连接
     * @return connection 数据库连接对象
     */
    public Connection getConnection() throws SQLException {
        try {
            Class.forName(DRIVER);
            // 获取数据库连接
            connection = DriverManager.getConnection(URL, USER, PASSWORD);
            System.out.println("数据库连接成功");
            return connection;
        } catch (Exception e) {
            // 如果连接过程出现异常，抛出异常信息
            e.printStackTrace();
            throw new SQLException("驱动错误或连接失败！");
        }
    }

    /**
     * 事务开启函数
     */
    public void startBatch() {
        try {
            autoCommit = connection.getAutoCommit();
            System.out.println("事务自动提交状态： " + autoCommit);
            if(autoCommit) {
                // 关闭自动提交 开始事务
                connection.setAutoCommit(false);
                System.out.println("已关闭自动提交，事务开始");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("事务启动失败");
        }
    }

    /**
     * 事务结束函数
     * 成功则提交，失败则回滚
     */
    public void closeBatch() {
        try {
            connection.setAutoCommit(autoCommit); // 恢复原有事务提交状态
            closeAll();
            System.out.println("事务结束，恢复自动提交状态");
            System.out.println("事务自动提交状态： " + autoCommit);
        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("事务提交失败，进行回滚");
            try {
                connection.rollback();
                System.out.println("回滚成功");
            } catch (SQLException ex) {
                ex.printStackTrace();
                System.out.println("回滚失败");
            }
        }
    }
    /**
     * 释放资源
     */
    public void closeAll() {
        // 关闭resultSet
        if(resultSet != null) {
            try {
                resultSet.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        // 关闭ps
        if(ps != null) {
            try {
                ps.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        // 关闭connection
        if(connection != null) {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 执行sql语句进行数据库数据的查询
     * @param preSql 待填充参数的数据库查询语句
     * @param params 准备填充的参数列表
     * @throws SQLException 数据库更新异常
     * @return ResultSet 结果集
     */
    public ResultSet executeQuery(String preSql, List<Object> params) {
        try {
            ps = connection.prepareStatement(preSql);
            if (ps != null) {
                // 填充参数
                for(int i = 0; i < params.size(); ++i) {
                    ps.setObject(i+1, params.get(i));
                }
            }
            // 执行sql语句
            resultSet = ps.executeQuery();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return resultSet;
    }


    /**
     * 执行sql语句进行数据库数据的增加，删除，修改等更新
     * @param sql 待填充参数的数据库查询语句
     * @param params 准备填充的参数列表
     * @throws SQLException 数据库更新异常
     * @return 是否更新成功
     */
    public boolean executeUpdate(String sql, List<Object> params) throws SQLException {
        int rowNum = -1;        // 如果行号小于零说明更新失败
        ps = connection.prepareStatement(sql);
        if (params != null && !params.isEmpty()) {
            for(int i = 0; i < params.size();  ++i) {
                ps.setObject(i+1, params.get(i));
            }
        }
        rowNum = ps.executeUpdate(); //executeUpdate的返回值是一个整数，指示受影响的行数（即更新计数）
        return rowNum > 0;
    }

    /**
     * 通过反射机制查询单条数据库数据，处理完绑定后打包，并直接返回包装好的对象
     * 简单对象查询可用，如对象成员只包含基本类型String、int、double1等
     * @param <T> 当前数据类型
     * @param sql 待填充参数的数据库查询语句
     * @param params 待填充的参数列表
     * @param cls 要打包的对象的类型
     * @throws Exception 抛出一个异常
     * @return 直接返回包装好的数据
     */
    public <T> T findSimpleProResult(String sql, List<Object> params, Class<T> cls) throws Exception {
        System.out.println("正在查找");
        T resultObject = null;
        ps = connection.prepareStatement(sql);
        if (params != null && !params.isEmpty()) {
            for (int i = 0; i < params.size(); i++) {
                ps.setObject(i+1, params.get(i));
            }
        }
        resultSet = ps.executeQuery();
        ResultSetMetaData metaData = resultSet.getMetaData();
        System.out.println(metaData);
//        System.out.println(ps); // 调试用
        int col = metaData.getColumnCount();
        //单条 若有多个的话取最后一个
        while (resultSet.next()) {
            System.out.println("rrr");
            resultObject = cls.newInstance(); // 创建一个该类的一个新实例
            // 对每项数据依次处理
            for (int i = 0; i < col; i++) {
                String colName = metaData.getColumnName(i+1);
                Object colValue = resultSet.getObject(colName);
                System.out.println(colValue);
//                System.out.println(colName);
//                System.out.println(colValue);
                Object newValue = null;
                System.out.println(colValue.getClass());
                if (colValue == null) {
                    newValue = "null";
                } else if (colValue.getClass() == Integer.class) {
                    newValue = new Integer(Integer.parseInt(colValue.toString()));
                } else if (colValue.getClass() == String.class) {
                    newValue = colValue.toString();
                } else if(colValue.getClass() == Double.class) {
                    newValue = new Integer(Integer.parseInt(colValue.toString()));
                }
                Field field = cls.getDeclaredField(colName);
                field.setAccessible(true);
                field.set(resultObject, newValue);
            }
        }
        return resultObject;
    }
}
