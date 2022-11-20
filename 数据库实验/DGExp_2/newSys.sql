
--插入测试数据
INSERT INTO Schools (SchoolID, Name, City, Address, HeadMasterID) VALUES (1, N'易驾驾校郑州分校', N'郑州市', N'河南省郑州市中原区莲花街233号', 1);
INSERT INTO Schools (SchoolID, Name, City, Address, HeadMasterID) VALUES (2, N'易驾驾校深圳分校', N'深圳市', N'广东省深圳市宝安区福永街道222号', 6);
INSERT INTO 易驾驾校.dbo.Employees (EmployeeID, EmployeeType, Level, Name, Tel, Salary, Sex, Birthday, SchoolID) VALUES (2, 0, N'普通', N'Mone', N'61234222', 2114.0000, N'男', N'1995-12-12', 1)
INSERT INTO 易驾驾校.dbo.Employees (EmployeeID, EmployeeType, Level, Name, Tel, Salary, Sex, Birthday, SchoolID) VALUES (3, 0, N'高级', N'Henry', N'412121222', 5234.0000, N'男', N'1995-12-10', 1)
INSERT INTO 易驾驾校.dbo.Employees (EmployeeID, EmployeeType, Level, Name, Tel, Salary, Sex, Birthday, SchoolID) VALUES (4, 1, N'', N'Jack', N'312312312', 1231.0000, N'男', N'1996-12-12', 1)
INSERT INTO 易驾驾校.dbo.Employees (EmployeeID, EmployeeType, Level, Name, Tel, Salary, Sex, Birthday, SchoolID) VALUES (5, 0, N'高级', N'Merry', N'412344111', 6455.0000, N'女', N'1995-06-16', 2)
INSERT INTO 易驾驾校.dbo.Employees (EmployeeID, EmployeeType, Level, Name, Tel, Salary, Sex, Birthday, SchoolID) VALUES (6, 0, N'普通', N'Nayi', N'212222233', 2114.0000, N'男', N'1995-12-12', 2)
