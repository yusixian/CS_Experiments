-- auto-generated definition
create schema todo_list collate utf8mb4_0900_ai_ci;
# 客户表，含客户编号、联系人名、联系电话、联系地址，以客户编号为主键
DROP TABLE IF EXISTS Custormers;
create table Custormers
(
    custormer_id  int auto_increment comment '客户编号'
        primary key,
    contact_name char(80)  not null,
    phone        char(48)  null,
    address      char(120) null
);


# 订单表，含订单编号、客户编号、订货日期、交货日期，以订单编号为主键
DROP TABLE IF EXISTS Orders;
create table Orders
(
    order_id int auto_increment,
    custormer_id char(10) null,
    order_date datetime null,
    required_date datetime null,
    constraint orders_pk
        primary key (order_id)
);

# 订单明细表，含订单编号、产品编号、产品单价、产品数量，以订单编号和产品编号共同为主键
DROP TABLE IF EXISTS Order_detail;
create table order_detail
(
    product_id int auto_increment
        primary key,
    order_id   int    not null,
    unit_price double not null,
    quantity   int    null comment '数量',
    constraint order_id
        unique (order_id, product_id)
);



# 产品表，含产品编号、产品名称、种类号、产品单价、库存，以产品编号为主键
DROP TABLE IF EXISTS Products;
create table Products
(
    product_id  int auto_increment
        primary key,
    productName char(80)         not null,
    category_id int              null,
    unit_price  double default 0 not null,
    units_stock int    default 0 null comment '库存'
);
