package dao.entity;

import java.util.Date;

public class Order {
    private int orderId;
    private int custormerId;
    private Date orderDate;
    private Date requiredDate;
    public Order() {
        this.orderId = 0;
        this.custormerId = 0;
        this.orderDate = null;
        this.requiredDate = null;
    }
    public Order(int orderId, int custormer_id, Date order_Date, Date requiredDate) {
        this.orderId = orderId;
        this.custormerId = custormer_id;
        this.orderDate = order_Date;
        this.requiredDate = requiredDate;
    }

    public int getOrderId() {
        return orderId;
    }

    public void setOrderId(int orderId) {
        this.orderId = orderId;
    }

    public int getCustormerId() {
        return custormerId;
    }

    public void setCustormerId(int custormerId) {
        this.custormerId = custormerId;
    }

    public Date getOrderDate() {
        return orderDate;
    }

    public void setOrderDate(Date orderDate) {
        this.orderDate = orderDate;
    }

    public Date getRequiredDate() {
        return requiredDate;
    }

    public void setRequiredDate(Date requiredDate) {
        this.requiredDate = requiredDate;
    }

    @Override
    public String toString() {
        return "Order{" +
                "orderId=" + orderId +
                ", custormerId=" + custormerId +
                ", orderDate=" + orderDate +
                ", requiredDate=" + requiredDate +
                '}';
    }
}
