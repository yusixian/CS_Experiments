package dao;

import dao.entity.Order;

import java.util.List;

public interface OrderDao {
    /**
     * 添加一条订单信息
     * @param order 订单数据
     */
    void insert(Order order);

    /**
     * 添加多条订单信息
     * @param list 订单列表
     */
    void insertList(List<Order> list);

    /**
     * 根据id删除订单信息
     * @param oid 订单id
     * @return boolean 删除成功与否
     */
    boolean delete(int oid);

    /**
     * 根据id更新订单信息
     * @param oid 订单id
     */
    void update(int oid, Order order);

    /**
     * 根据id查询单个订单
     * @param oid 订单id
     * @return Order 若为空则未查询到
     */
    Order findSingleOrder(int oid);

    /**
     * 查询所有订单信息并返回订单列表
     * @return List<Order> 订单信息列表
     */
    List<Order> findAll();

}
