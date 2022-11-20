package service;

import dao.Impl.OrderDaoImpl;
import dao.entity.Order;

import java.util.Date;
import java.util.List;

public class OrderService {
    public static void main(String []args) throws Exception  {
        OrderDaoImpl orderDao = new OrderDaoImpl();
        Order order = new Order(90, 3, new Date(2021-11-18), new Date(2021-12-12));
        System.out.println("-----------插入"+order.toString()+"-----------");
        orderDao.insert(order);
        List<Order> list = orderDao.findAll();
        System.out.println("-----------以下为所有订单-----------");
        for(int i = 0; i < list.size(); ++i) {
            System.out.println(list.get(i));
        }

        System.out.println("-----------更新"+order.toString()+"-----------");
        order.setCustormerId(100);
        order.setRequiredDate(new Date(2023-12-12));
        orderDao.update(order.getOrderId(), order);
        System.out.println("----------------------");

        list = orderDao.findAll();
        System.out.println("-----------以下为所有订单-----------");
        for(int i = 0; i < list.size(); ++i) {
            System.out.println(list.get(i));
        }

        System.out.println("-----------插入4条订单信息-----------");
        list.clear();
        list.add(new Order(40, 1, new Date(2012-02-11), new Date(2012-12-22)));
        list.add(new Order(41, 3, new Date(2010-01-12), new Date(2012-06-25)));
        list.add(new Order(42, 51, new Date(2016-06-12), new Date(2019-06-25)));
        list.add(new Order(43, 21, new Date(2013-03-20), new Date(2016-11-19)));
        orderDao.insertList(list);

        System.out.println("-----------以下为所有订单-----------");
        list = orderDao.findAll();
        for(int i = 0; i < list.size(); ++i) {
            System.out.println(list.get(i));
        }
    }
}
