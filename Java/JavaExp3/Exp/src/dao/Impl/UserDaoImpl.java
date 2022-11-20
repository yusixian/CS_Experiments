package dao.Impl;

import dao.UserDao;
import dao.entity.Order;
import dao.entity.User;
import util.DBUtil;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class UserDaoImpl implements UserDao {

    /**
     * 添加一条用户信息
     *
     * @param user 用户数据
     */
    @Override
    public void insert(User user) {
        DBUtil dbUtils = new DBUtil();
        try {
            dbUtils.getConnection();
            String sql = "insert into `users`(user_name, password) " +
                    "values(?, ?)";
            List<Object> params = new ArrayList<>();
            params.add(user.getUserName());
            params.add(user.getPassWord());
            if(dbUtils.executeUpdate(sql, params)) {
                System.out.println("添加用户成功");
            } else System.out.println("添加用户失败");
        } catch (SQLException e) {
            System.out.println("SQLException");
            e.printStackTrace();
        }

    }

    /**
     * 根据用户名更新用户信息
     * @param userName 用户名
     * @param user
     */
    @Override
    public void update(String userName, User user) {
        DBUtil dbUtils = new DBUtil();
        try {
            dbUtils.getConnection();
            String sql = "update `users` set password = ?"
                    + "where user_name = ?;";
            List<Object> params = new ArrayList<>();
            params.add(user.getPassWord());
            params.add(user.getUserName());
            if(dbUtils.executeUpdate(sql, params)) {
                System.out.println("更新用户成功");
            } else System.out.println("更新用户失败");
        } catch (SQLException e) {
            System.out.println("SQLException!");
            e.printStackTrace();
        }
    }

    /**
     * 根据用户名查询单个用户
     *
     * @param userName 用户名
     * @return User 若为空则未查询到
     */
    @Override
    public User findSingleUser(String userName) {
        User user = null;
        DBUtil dbUtils = new DBUtil();
        try {
            dbUtils.getConnection();
            String sql = "select * from `users` where user_name = ?";
            List<Object> params = new ArrayList<>();
            params.add(userName);
            ResultSet resultSet = dbUtils.executeQuery(sql, params);
            ResultSetMetaData metaData = resultSet.getMetaData();
//            System.out.println(metaData);
            while (resultSet.next()) {
                int userId = resultSet.getInt("id");
                String uName = resultSet.getString("user_name");
                String pWord = resultSet.getString("password");

                user = new User(userId, uName, pWord);
            }
            if (user != null) {
                System.out.println("该用户存在:");
                System.out.println(user);
            } else
                System.out.println("该用户不存在");
        } catch (Exception e) {
            System.out.println("查找失败！");
            e.printStackTrace();
        }
        return user;
    }

    @Override
    public List<User> findAll() {
        List<User> list = new ArrayList<>();
        DBUtil dbUtils = new DBUtil();
        try {
            dbUtils.getConnection();
            String sql = "select * from `users`";
            List<Object> params = new ArrayList<>();
            ResultSet resultSet = dbUtils.executeQuery(sql, params);
            while (resultSet.next()) {
                int id = resultSet.getInt("id");
                String userName = resultSet.getString("user_name");;
                String passWord = resultSet.getString("password");;
                User user = new User(id, userName,passWord);
                list.add(user);
            }
            if (list.isEmpty())
                System.out.println("数据库中不存在用户");
        } catch (Exception e) {
            System.out.println("查找失败！");
            e.printStackTrace();
        }
        return list;
    }
}
