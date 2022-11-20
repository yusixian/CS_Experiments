package dao.Impl;

import dao.OrderDao;
import dao.entity.Order;
import util.DBUtil;

import java.sql.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class OrderDaoImpl implements OrderDao {
    @Override
    public void insert(Order order) {
        DBUtil dbUtils = new DBUtil();
        try {
            dbUtils.getConnection();
            String sql = "insert into `orders`(order_id, custormer_id, order_date, required_date) " +
                    "values(?, ?, ?, ?)";
            List<Object> params = new ArrayList<>();
            params.add(order.getOrderId());
            params.add(order.getCustormerId());
            params.add(order.getOrderDate());
            params.add(order.getRequiredDate());
            if(dbUtils.executeUpdate(sql, params)) {
                System.out.println("添加订单成功");
            } else System.out.println("添加订单失败");
        } catch (SQLException e) {
            System.out.println("添加订单失败！");
            e.printStackTrace();
        }
    }

    @Override
    public void insertList(List<Order> list) {
        DBUtil dbUtils = new DBUtil();
        Connection conn = null;
        try {
            conn = dbUtils.getConnection();
            dbUtils.startBatch();
            String sql = "insert into `orders`(order_id, custormer_id, order_date, required_date) " +
                    "values(?, ?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            for(int i = 0; i < list.size(); ++i) {
                Order order = list.get(i);
                pstmt.setInt(1, order.getOrderId());
                pstmt.setInt(2, order.getCustormerId());

                Date utilDate = order.getOrderDate();
                pstmt.setTimestamp(3, new java.sql.Timestamp(utilDate.getTime()));
                utilDate = order.getRequiredDate();
                pstmt.setTimestamp(4, new java.sql.Timestamp(utilDate.getTime()));
                pstmt.addBatch();//添加到同一个批处理中
//                System.out.println(pstmt);
            }
            pstmt.executeBatch();            // 执行批处理
            conn.commit();                  // 如果顺利执行则在此提交
            dbUtils.closeBatch();
        } catch (SQLException e) {
            System.out.println("添加订单失败！");
            e.printStackTrace();
        }
    }

    @Override
    public boolean delete(int oid) {
        DBUtil dbUtils = new DBUtil();
        try {
            dbUtils.getConnection();
            String sql = "delete from `orders` where order_id = ?";
            List<Object> params = new ArrayList<>();
            params.add(oid);
            if(dbUtils.executeUpdate(sql, params)) {
                System.out.println("删除订单成功");
                return true;
            } else System.out.println("删除订单失败");
        } catch (SQLException e) {
            System.out.println("删除订单失败！");
            e.printStackTrace();
        }
        return false;
    }

    @Override
    public void update(int oid, Order order) {
        DBUtil dbUtils = new DBUtil();
        try {
            dbUtils.getConnection();
            String sql = "update `orders` set custormer_id = ?, order_date = ?, required_date = ?"
                    + "where order_id = ?;";
            List<Object> params = new ArrayList<>();
            params.add(order.getCustormerId());
            params.add(order.getOrderDate());
            params.add(order.getRequiredDate());
            params.add(oid);
            if(dbUtils.executeUpdate(sql, params)) {
                System.out.println("更新订单成功");
            } else System.out.println("更新订单失败");
        } catch (SQLException e) {
            System.out.println("更新订单失败！");
            e.printStackTrace();
        }

    }

    @Override
    public Order findSingleOrder(int oid) {
        Order order = null;
        DBUtil dbUtils = new DBUtil();
        try {
            dbUtils.getConnection();
            String sql = "select * from `orders` where order_id = ?";
            List<Object> params = new ArrayList<>();
            params.add(oid);
            ResultSet resultSet = dbUtils.executeQuery(sql, params);
            while (resultSet.next()) {
                int orderId = resultSet.getInt("order_id");
                int custormerId = resultSet.getInt("custormer_id");;
                Date orderDate = resultSet.getDate("order_date");;
                Date requiredDate = resultSet.getDate("required_date");;
                order = new Order(orderId, custormerId, orderDate, requiredDate);
            }
            if (order != null) {
                System.out.println("该订单存在:");
                System.out.println(order);
            } else
                System.out.println("该订单不存在");
        } catch (Exception e) {
            System.out.println("查找失败！");
            e.printStackTrace();
        }
        return order;
    }

    @Override
    public List<Order> findAll() {
        List<Order> list = new ArrayList<>();
        DBUtil dbUtils = new DBUtil();
        Order resultObject = null;
        try {
            dbUtils.getConnection();
            String sql = "select * from `orders`";
            List<Object> params = new ArrayList<>();
            ResultSet resultSet = dbUtils.executeQuery(sql, params);
            ResultSetMetaData metaData = resultSet.getMetaData();
//            System.out.println(metaData);
            while (resultSet.next()) {
                int orderId = resultSet.getInt("order_id");
                int custormerId = resultSet.getInt("custormer_id");;
                Date orderDate = resultSet.getDate("order_date");;
                Date requiredDate = resultSet.getDate("required_date");;
                Order order = new Order(orderId, custormerId, orderDate, requiredDate);
                list.add(order);
            }
            if (list.isEmpty())
                System.out.println("数据库中不存在订单");
        } catch (Exception e) {
            System.out.println("查找失败！");
            e.printStackTrace();
        }
        return list;
    }
}
