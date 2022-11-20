package dao;

import dao.entity.Order;
import dao.entity.User;

import java.util.List;

public interface UserDao {

    /**
     * 添加一条用户信息
     * @param user 用户数据
     */
    void insert(User user);

    /**
     * 根据用户名更新用户密码
     * @param userName 用户名
     * @param user 新用户信息
     */
    void update(String userName, User user);

    /**
     * 查询所有订单信息并返回订单列表
     * @return List<Order> 订单信息列表
     */
    List<User> findAll();

    /**
     * 根据用户名查询单个用户
     * @param userName 用户名
     * @return User 若为空则未查询到
     */
    User findSingleUser(String userName);
}
