use LGameDB;

drop procedure if exists _LDBI_CreateUserCore;
delimiter $$
/*retCode : 10000 账户名已经被注册*/
create procedure _LDBI_CreateUserCore (username char(20), password char(30),out retcode int)
label_return:begin
        set retcode = 0;
        if exists(select 1 from T_UserCore where F_UserName = username) then
           set retcode = 10000;
           leave label_return;
        end if;
        insert into T_UserCore(F_UserName,F_PassWord) values (username,password);
end$$
delimiter ;
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

drop procedure if exists _LDBI_CreateRole;
delimiter $$
create
procedure  _LDBI_CreateRole (gClientID int,RemoteID int,
FileIndex int,rolename char(30),roletype tinyint ,sex tinyint ,level smallint,Scenario int,exp bigint,money bigint, out Result int,out LClientID int,out RoleID int)
label_return:begin
        declare userid int default null;
        declare clientid int;
        declare username char(30) default null;
        declare userip char(20);
        declare gsid int;
        declare blockno int;
        declare zoneid int;
        declare fileindex tinyint;
        select F_UserID,F_LClientID,F_GSID,F_LoginIP,F_GSID,F_BlockNo,F_ZoneID
        into userid,clientid,gsid,userip,gsid,fileindex,blockno,zoneid from T_LoggedUser
        where F_ID = gClientID;
        if isnull(userid) or isnull(username) then
           set Result = 1020;
           leave label_return;
        end if;
        if exists(select 1 from T_Blocks where F_BlockNo=blockno) then
           if exists(select 1 from T_Role where F_RoleName = rolename) then
              set Result = 1011; #角色名已经存在
              leave label_return;
           elseif exists(select 1 from T_Role where F_UserID = userid and F_BlockNo = blockno and F_FileIndex = FileIndex) then
              set Result = 1012; # 此位置 已经存在角色
              leave label_return;
           elseif not isnull(fileindex) then
              set Result = 1012; #此位置 已经存在角色
              leave label_return;
           else
                # todo :开始事务
                start transaction;
                # todo: 插入T_Role表
                insert into T_Role(F_RemoteID,F_UserID,F_UserName,F_RoleName,F_FileIndex,F_Type,F_Sex,
                F_Level,F_Sceneario,F_Exp,F_Money,F_UpdateTime,F_BlockNo,F_ZoneID)
                values (RemoteID,userid,username,rolename,FileIndex,roletype,sex,level,Scenario,exp,money,now(),blockno,zoneid);
                set RoleID=Last_Insert_ID();
                # todo: 插入Log
                call _LDBI_RoleLog_Appand(userid,username,rolename,userip,gsid,roletype,sex,level,Scenario,exp,money);
                set Result = 1;                
                # todo :结束事务
                commit;
           end if;
        end if;
end$$

delimiter ;

drop table if exists T_Role;
create table T_Role(
       F_ID int  auto_increment primary key, # 主键
       F_UserID int not null, # 用户ID ，来源于 T_UserCore
       F_RemoteID int null, # 全局角色ID ??是否需要？
       F_UserName char(20) not null, # 用户名称 ？ 是否需要？
       F_RoleName char(30) not null, # 角色名称
       F_GSID smallint not null, # GSID 用户当前登陆的 GSID 
       F_FileIndex tinyint unsigned not null default 255, # 玩家创建角色的位置
       F_Type tinyint unsigned not null default 0, # 角色职业
       F_Sex tinyint not null default 0, # 角色性别
       F_Level smallint not null default 1, # 角色等级
       F_Scenario int not null default 0, # 角色场景 
       F_Exp bigint not null default 0, # 角色经验
       F_Money bigint not null default 0, # 角色当前的金钱
       F_TotalTime int not null default 0, # 当前的时间
       F_TotalEnter int not null default 0, # 进入总次数
       F_CreateTime datetime not null default now(),
       F_UpdateTime datetime null, # 更新时间
       F_StopTime datetime null,
       F_LastTime datetime null,
       F_BlockNo int null,
       F_ZoneID int not null default 0,
       index index_rolename  (F_RoleName)
) charset=utf8;






drop table if exists T_UserCore;
create table T_UserCore (
       F_ID int(4) not null unique auto_increment,
       F_UserName char(20) not null,
       F_PassWord char(32) not null,
       F_ActiveTime datetime not null ,
       F_LastTime DATETIME ,
       F_StopTime DATETIME ,
       F_IsAdult BIT(1) ,
      PRIMARY KEY (F_ID),
      KEY key_name (F_UserName)
) charset=utf8;

drop table if exists T_Blocks;
create table T_Blocks (
       F_ID int(4) primary key,
       F_BlockNo int(4) null
);

drop table if exists T_BigZone;
create table T_BigZone (
       F_ID int(4) primary key,
       F_Name varchar(50) not null,
       F_IP varchar(20) not null,
       F_Port int(4) null,
       F_Type int(4) not null,
       F_Status int(4) not null,
       F_Order int(4) not null,
       F_Desc varchar(50) not null
 )charset = utf8;
drop table if exists T_LoggedUser;
create table T_LoggedUser (
     F_ID int(4) primary key,
     F_UserID int(4) not null,
     F_UserName char(20) not null,
     F_LClientID int not null,
     F_LoginTime datetime not null,
     F_LoginIP char(20) not null,
     F_GSID int not null,
     F_FileIndex tinyint null,
     F_GameID int null,
     F_EnterGameTime datetime null,
     F_BlockNo int,
     F_ZoneID int not null default 0
)charset=utf8;
drop procedure if exists test_AddLoggedUser;
delimiter $$
create procedure test_AddLoggedUser (fid int,userid int,username char(20))
begin
        declare nowtime datetime;
        set nowtime = now();
        insert T_LoggedUser(F_ID,F_UserID,F_UserName,f_LClientID,F_LoginTime,F_LoginIP,F_GSID,F_GameID,F_EnterGameTime,F_BlockNo,F_ZoneID)
        values(fid,userid,username,30,now(),"192.168.0.1",8,8,now(),1,1);
end$$
delimiter ;

use GameLogDB;
drop table  if exists T_RoleLog;
create table T_RoleLog (F_ID int primary key auto_increment,F_UserID int not null,
       F_UserName char(30) not null,F_RoleName char(30) not null,F_EventID int not null,
       F_GSID smallint not null,F_Type tinyint not null,
       F_Sex tinyint not null,F_Scenario int,F_Level smallint not null,
       F_Exp bigint not null,F_Money bigint not null,F_UserIP char(16) not null,
       F_UpdateTime datetime default now()) charset=utf8;
use LGameDB;
