delimiter $$
drop procedure if exists _LDBI_RoleLog_Appand;
create procedure _LDBI_RoleLog_Appand (userid int,EventID int,username char(20),
       rolename char(30),userip char(16),gsid smallint,roletype tinyint,
       sex tinyint,level smallint,Scenario int,exp bigint,money bigint)
begin
       insert into GameLogDB.T_RoleLog(F_UserID,F_EventID,F_UserName,F_RoleName,
       F_UserIP,F_GSID,F_Type,F_Sex,F_Level,F_Exp,F_Money,F_Scenario) values(
       userid,EventID,username,rolename,userip,gsid,roletype,sex,level,exp,money,Scenario);
        
end$$
delimiter ;


