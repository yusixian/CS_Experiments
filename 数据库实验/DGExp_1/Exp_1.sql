/* 1.在产品表(Products)中找出库存大于30的产品的所有信息 */
SELECT * FROM 销售数据库.dbo.Products WHERE UnitsInStock > 30

/* 2.查询顾客表(Customers)中所有不重复的所在城市 */
SELECT DISTINCT City FROM 销售数据库.dbo.Customers

/* 3.在订单表(Orders)中找出运费在10到50（含10和50）之间的订单编号、顾客编号和职员编号 */
SELECT OrderID,CustomerID,EmployeeID FROM Orders WHERE Freight >= 10 and Freight <= 50

/* 4.在顾客表(Customers)中找出所在城市为London的联系人名和公司名 */
SELECT ContactName,CompanyName FROM Customers WHERE City = 'London'

/* 5.在顾客表(Customers)中找出所在城市为London、Madrid、Torino和Paris的顾客编号及电话 */
SELECT CustomerID,Phone FROM Customers WHERE City = 'London' or City = 'Madrid' or City = 'Torino' or City = 'Paris'

/* 6.在订单表(Orders)中找出国籍不是Brazil、Spain和Mexico的订单编号和订货日期 */
SELECT OrderID,OrderDate FROM Orders WHERE ShipCountry not in('Brazil','Spain', 'Mexico')

/* 7.在产品表(Products)中找出单位数量中有box的产品名和产品编号 */
SELECT ProductName,ProductID FROM Products WHERE QuantityPerUnit like '%box%'

/* 8.在顾客表(Customers)中找出公司名的首字母为F的顾客编号和联系人 */
SELECT CustomerID,ContactName FROM Customers WHERE CompanyName like 'F%'

/* 9.在顾客表(Cu=tomers)中找出公司名的首字母为F，第5位为k的顾客编号和联系人名 */
SELECT CustomerID,ContactName FROM Customers WHERE CompanyName like 'F___k%'

/* 10.统计在'1997-10-1' 到'1997-10-7'期间，订单中每个员工的订单数，并按订单数降序排序 */
SELECT EmployeeID AS 员工编号, COUNT(*) AS 订单数 FROM Orders WHERE OrderDate >= '1997-10-1' and OrderDate <= '1997-10-7'
group by EmployeeID order by COUNT(*) desc

/* 11.请查询平均价格在25及以上的产品类型 */
SELECT CategoryID, AVG(UnitPrice) AS 平均价格 FROM Products GROUP BY CategoryID HAVING AVG(UnitPrice) >= 25

/* 12.查询在'1997-10-1' 到'1997-10-7'期间订货的订单编号、客户联系人名称、城市、地址、联系电话，并按城市和订货日期升序排序。 */
Select OrderID, ContactName, City, Address, Phone From Orders, Customers
Where Orders.CustomerID = Customers.CustomerID and Orders.OrderDate >= '1997-10-1' and Orders.OrderDate <= '1997-10-7'
Order By City, OrderDate DESC;

/* 13.查询在'1997-10-1' 到'1997-10-7'期间订货的订单编号、客户联系人名称、城市、地址、联系电话，并按城市和订货日期升序排序。 */
select b.EmployeeID, COUNT(OrderID) AS 订单量 from Orders a right outer join Employees b
on a.EmployeeID = b.EmployeeID and OrderDate >= '1997-10-1' and OrderDate <= '1997-10-7'
group by b.EmployeeID order by b.EmployeeID asc

/* 14. 查询'1997-10-7'当天所售商品的库存情况，包括商品编号、名称、库存 */
select c.ProductID, c.ProductName, c.UnitsInStock from Orders a, [Order Details] b, Products c
where a.OrderID = b.OrderID and b.ProductID = c.ProductID and a.OrderDate = '1997-10-7'

/* 15. 查询客户编号“BSBEV”在“1997-5-16”订购的每一笔订单明细（包括订单号、订货日期、交货日期、产品名称、单价、数量、折扣后金额）。 */
select a.OrderID, a.OrderDate, a.RequiredDate, d.ProductName, b.UnitPrice, b.Quantity, b.UnitPrice*b.Quantity*(1-b.Discount) as 折扣金额
from Orders a, [Order Details] b, Customers c, Products d
where a.OrderID = b.OrderID and a.CustomerID = c.CustomerID and b.ProductID = d.ProductID
  and a.OrderDate = '1997-5-16' and a.CustomerID = 'BSBEV'

/* 16. 【选做】查询在'1997-10-1' 到'1997-10-7'期间订货的订单编号、客户联系人名称、城市、地址、联系电话、运费、订货数量、总金额和折扣后总金额，
   并按城市和订货日期升序排序。（提示：可采用导出表连接查询方案，其他方案亦可。） */
Select a.OrderID, MAX(c.ContactName) as ContactName, MAX(c.City) as City, MAX(c.Address) as Address, MAX(c.Phone) as Phone,
       MAX(a.Freight) as Freight, SUM(b.Quantity) as 订货数量, SUM(b.Quantity*b.UnitPrice) as 总金额,
       SUM(b.Quantity*b.UnitPrice*(1-b.Discount)) as 折扣后金额
From Orders a join [Order Details] b on a.OrderID = b.OrderID
join Customers c on c.CustomerID = a.CustomerID
where a.OrderDate >= '1997-10-1' and a.OrderDate <= '1997-10-7'
group by a.OrderID Order By MAX(c.City), MAX(a.OrderDate) asc;
-- Select a.OrderID, c.ContactName,c.City, c.Address, c.Phone, a.Freight, b.Quantity as 订货数量, b.UnitPrice,
--        b.Quantity*b.UnitPrice as 总金额, b.Quantity, b.UnitPrice*(1-b.Discount) as 折扣后金额
-- From Orders a join [Order Details] b on a.OrderID = b.OrderID
-- join Customers c on c.CustomerID = a.CustomerID
-- where a.OrderDate >= '1997-10-1' and a.OrderDate <= '1997-10-7'
-- Order By c.City, a.OrderDate DESC;

/* 17.请查询价格不低于其同类产品平均价格的产品编号、名称、价格、种类。（多于3种实现方案）*//
/* 1、嵌套查询 子查询按种类分组  */
select a.ProductID, a.ProductName, a.UnitPrice, a.CategoryID from Products a
where a.UnitPrice >= (select AVG(b.UnitPrice) from Products b where b.CategoryID = a.CategoryID group by b.CategoryID)
order by a.ProductID asc
/* 2、连接产品表和查询结果表 */
select a.ProductID, a.ProductName, a.UnitPrice, a.CategoryID
from Products a join (select b.CategoryID, AVG(b.UnitPrice) as AvgPrice from Products b group by b.CategoryID) as AvgPriceTable
    on a.CategoryID = AvgPriceTable.CategoryID and a.UnitPrice >= AvgPriceTable.AvgPrice
order by a.ProductID asc
/* 3、Exist实现 是否存在价格>= */
-- select a.ProductID, a.ProductName, a.UnitPrice, a.CategoryID from Products a
-- where exist(a.UnitPrice >= (select AVG(b.UnitPrice) from Products b where b.CategoryID = a.CategoryID group by b.CategoryID) )
-- order by a.ProductID asc


/* 18.【选做】请查询累计消费总金额在40000元及以上的客户编号、联系人、电话、国籍。（多于3种实现方案）*/
/* 1、三层，第一层查询得出每个订单的总金额，但每个客户可能有多个订单（运费+单价*数量*（1-折扣），第二层得出每个客户在不同订单加起来的总金额  */
select a.CustomerID, a.ContactName, a.Phone, a.Country, b.TotalPrice from Customers a,
(select OTable.CID, SUM(SumPrice) as TotalPrice from (
    select MAX(a.CustomerID) as CID,
           MAX(Freight) + SUM(UnitPrice*Quantity*(1-Discount)) as SumPrice
    from Customers a, Orders b, [Order Details] c
    where a.CustomerID = b.CustomerID and c.OrderID = b.OrderID
    group by b.OrderID) as OTable
group by OTable.CID) as b
where a.CustomerID = b.CID and b.TotalPrice >= 40000
/* 2.全部连接完后再去分组 */
