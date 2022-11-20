-- 这里如果不指定数据库的话，默认为master数据库*/
CREATE LOGIN YiJiaLogin WITH PASSWORD = '3h#w+rC!' , DEFAULT_DATABASE = 易驾驾校
GO
-- 指定数据库用户 YiJiaUser 的默认 schema 是 dbo
CREATE USER YiJiaUser FOR LOGIN YiJiaLogin with default_schema = dbo;
GO
-- 加入数据库角色，赋予数据库用户所有权限
exec sp_addrolemember 'db_owner', 'YiJiaUser'
-- 查看所有用户
exec sp_helpuser;