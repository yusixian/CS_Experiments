-- auto-generated definition
create table Cars
(
    CarID   int not null IDENTITY
        constraint Cars_pk
            primary key nonclustered,
    SchoolID int     not null
        constraint Cars_Schools_SchoolID_fk
            references Schools,
    CoachID  int     not null
        constraint Cars_Employees_EmployeeID_fk
            references Employees
)
go

create unique index Cars_CarID_uindex
	on Cars (CarID)
go

 --添加
Alter PROCEDURE p_CarsAdd
	@SchoolID int,
	@CoachID int
AS
BEGIN
    INSERT INTO dbo.Cars
            (SchoolID, CoachID )
    VALUES  ( @SchoolID, @CoachID )
END
GO

--删除
ALTER PROCEDURE p_CarsDel
	@CarID int
AS
BEGIN
	DELETE FROM dbo.Cars WHERE CarID = @CarID
	dbcc checkident(Cars,reseed,0)
END
GO

--查询
CREATE PROCEDURE p_CarsFindByID
	@CarID int
AS
BEGIN
	select * FROM dbo.Cars WHERE CarID = @CarID
END
GO

--显示全部
CREATE PROCEDURE p_CarsAll
AS
BEGIN
	select * FROM dbo.Cars
END
GO

 --------测试-------
exec p_CarsAdd @SchoolID = 1, @CoachID = 1;
exec p_CarsAll;

exec p_CarsDel @CarID  = 1;
exec p_CarsAll;

exec p_CarsAdd @SchoolID = 1, @CoachID = 1;
exec p_CarsAdd @SchoolID = 2, @CoachID = 2;
exec p_CarsFindByID @CarID  = 2;

exec p_CarsAdd @SchoolID = 1, @CoachID = 5;
exec p_CarsAdd @SchoolID = 2, @CoachID = 3;
exec p_CarsAll;
exec p_CarsAdd  @SchoolID = 1, @CoachID = 3;
exec p_CarsAdd  @SchoolID = 2, @CoachID = 3;



