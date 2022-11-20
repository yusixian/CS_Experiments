package dao.entity;

public class Product {
    private int product_id;
    private char productName;
    private int category_id;
    private double unit_price;
    private int units_stock;

    public int getProduct_id() {
        return product_id;
    }

    public void setProduct_id(int product_id) {
        this.product_id = product_id;
    }

    public char getProductName() {
        return productName;
    }

    public void setProductName(char productName) {
        this.productName = productName;
    }

    public int getCategory_id() {
        return category_id;
    }

    public void setCategory_id(int category_id) {
        this.category_id = category_id;
    }

    public double getUnit_price() {
        return unit_price;
    }

    public void setUnit_price(double unit_price) {
        this.unit_price = unit_price;
    }

    public int getUnits_stock() {
        return units_stock;
    }

    public void setUnits_stock(int units_stock) {
        this.units_stock = units_stock;
    }
}
