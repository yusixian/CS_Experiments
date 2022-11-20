use 易驾驾校
create table ExamRecord
(
    ExamID        int identity
        constraint ExamRecord_pk
            primary key nonclustered,
    ExamDate      date              not null,
    ExamType      tinyint default 0 not null,
    Grade         int,
    FailureReason varchar(255),
    StuID         int               not null
        constraint StuID_fk
            references Students,
    SchoolID      int               not null
        constraint ExamRecord__fk
            references Schools
)
go
create unique index ExamRecord_ExamID_uindex
    on ExamRecord (ExamID)
go


--添加
CREATE PROCEDURE p_EXRCAdd
    @ExamDate       date,
    @ExamType       tinyint,
    @Grade          int,
    @FailureReason  varchar(255),
    @StuID          int,
    @SchoolID       int
AS
BEGIN
	BEGIN TRAN
		BEGIN TRY
			INSERT INTO ExamRecord
			        ( ExamDate, ExamType, Grade, FailureReason, StuID, SchoolID )
			VALUES  ( @ExamDate, @ExamType, @Grade, @FailureReason, @StuID, @SchoolID )
			COMMIT TRAN
		END TRY
		BEGIN CATCH
			ROLLBACK TRAN
		END CATCH
END
GO

--删除
CREATE PROCEDURE p_EXRCDel
	@ExamID int
AS
BEGIN
	DELETE FROM dbo.ExamRecord WHERE ExamID = @ExamID
END
GO

--查询
CREATE PROCEDURE p_EXRCFindByID
	@ExamID int
AS
BEGIN
	select * FROM dbo.ExamRecord WHERE ExamID = @ExamID
END
GO

--显示全部
CREATE PROCEDURE p_EXRCAll
AS
BEGIN
	select * FROM dbo.ExamRecord
END
GO

exec p_EXRCAdd @ExamDate = '2021-1-22', @ExamType = 0, @Grade = 70, @FailureReason = null, @StuID = 1, @SchoolID = 1;
exec p_EXRCDel @ExamID =
exec p_EXRCAdd @ExamDate = '2021-1-22', @ExamType = 0, @Grade = 70, @FailureReason = null, @StuID = 1, @SchoolID = 1;

exec p_EXRCAdd @ExamDate = '2021-02-16', @ExamType = 1, @Grade = 90, @FailureReason = null, @StuID = 1, @SchoolID = 1;  --无法插入的

exec p_EXRCAdd @ExamDate = '2021-02-21', @ExamType = 0, @Grade = 70, @FailureReason = null, @StuID = 1, @SchoolID = 1;
exec p_EXRCAdd @ExamDate = '2021-03-16', @ExamType = 0, @Grade = 90, @FailureReason = null, @StuID = 1, @SchoolID = 1;
exec p_EXRCAdd @ExamDate = '2021-05-12', @ExamType = 1, @Grade = 80, @FailureReason = null, @StuID = 1, @SchoolID = 1;
exec p_EXRCAdd @ExamDate = '2021-07-22', @ExamType = 1, @Grade = 90, @FailureReason = null, @StuID = 1, @SchoolID = 1;

exec p_EXRCAdd @ExamDate = '2021-09-22', @ExamType = 1, @Grade = 90, @FailureReason = null, @StuID = 1, @SchoolID = 1;  --无法插入的

exec p_EXRCAll;