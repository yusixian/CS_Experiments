
 ---创建insert触发器 ---
alter trigger trg_examRecordBFInsert
    on ExamRecord
    after insert
as
begin
    declare @sid int;
    set @sid = (select StuID from inserted)
    if (select COUNT(*) from ExamRecord a where a.StuID = @sid GROUP BY a.StuID) > 5
    begin
        print '一个学员提交的所有类型的测试申请不得超过5次'
        rollback transaction
    end

    declare @d1 date;
    declare @d2 date;
    declare @grade1 int;

    set @d1 = (select max(ExamDate) from ExamRecord a where a.StuID = @sid and a.ExamType != 1 GROUP BY a.StuID)
    set @d2 = (select ExamDate from inserted)
    set @grade1 = (select max(Grade) from ExamRecord a where a.StuID = @sid and a.ExamType != 1 GROUP BY a.StuID)
    if ( (select ExamType from inserted) = 1)
    begin
        if( @grade1 < 90)
        begin
            print '理论测试未通过，不得进行实践测试'
            rollback transaction
        end
        if((select datediff(month , @d1, @d2)) < 1)
        begin
            print '上次测试时间间隔未超过一个月，不得进行实践测试'
            rollback transaction
        end
    end
end


 ---创建insert触发器 ---
alter trigger trg_CarsInsert
    on Cars
    after insert
as
    if (select COUNT(*) from Cars a where a.CoachID =  (select CoachID from inserted) GROUP BY a.CoachID) > 2
    begin
        print '教练被分配的车辆数目不能超过2辆'
        rollback transaction
    end
