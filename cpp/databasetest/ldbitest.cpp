#include <stdio.h>
#include "ldbitest.h"
#include "loginstance.h"
#include "databaseclient.h"
#include <boost/pool/pool.hpp>
#include <time.h>
#include <gtest/gtest.h>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include "ldbidatabase.h"
using namespace boost;
using namespace std;


void pooltest()
{
    pool<> pl(sizeof(int));
    int *p = (int *)pl.malloc();
    pl.free(p);
    for (int i = 0; i < 100; ++i)
    {
        pl.ordered_malloc(10);
        
    }
}
int My_Add(int a, int b)
{
    return a + b;
}
TEST(DataBaseTest,addOPTest)
{
    EXPECT_EQ(3,My_Add(1,2));
}
void timetest()
{
    time_t now;
    time(&now);
    struct tm *tm_now = localtime(&now);
    char timeBuf[32];
    //using the strftime ,not the directly time
    strftime(timeBuf,32,"%F %T",tm_now);
        
    printf("Now strftime return time is %s",timeBuf);
    
    printf("Now is %4d-%02d-%02d %02d:%02d:%02d\n",tm_now->tm_year,tm_now->tm_mon,tm_now->tm_mday,
           tm_now->tm_hour,tm_now->tm_min,tm_now->tm_sec);    
}

TEST(DataBaseTest,readFromJson)
{
    fstream fs;
    fs.open("resource/data/newusers.json");
    ASSERT_TRUE(fs.is_open());
    if (fs.is_open())
    {
        Json::Reader reader;
        Json::Value value;
        Json::Value root;
        reader.parse(fs,root);
        ASSERT_TRUE(!root["Users"].isNull());
        value = root["Users"];
        size_t size = value.size();
        ASSERT_EQ(size, 3);
        //printf("%s",value[0]["Name"].asCString());
        const char *password = "111111";
        ASSERT_STREQ(value[0]["Name"].asCString(),"张三");
        ASSERT_STREQ(value[0]["Password"].asCString(),password);
        ASSERT_STREQ(value[1]["Name"].asCString(),"李四");
        ASSERT_STREQ(value[1]["Password"].asCString(),password);
        ASSERT_STREQ(value[2]["Name"].asCString(),"王五");
        ASSERT_STREQ(value[2]["Password"].asCString(),password);        
        fs.close();
    }
    
}
void Test_InsertUser(CLdbiDataBase *database)
{
    fstream fs;
    fs.open("resource/data/newusers.json");
    if (fs.is_open())
    {
        Json::Reader reader;
        Json::Value value;
        Json::Value root;
        reader.parse(fs,root);
        value = root["Users"];
        size_t size = value.size();
        for (int i = 0; i < (int)size;++i)
        {
            int ncode = 0;
            database->CreateUser(value[i]["Name"].asCString(), value[i]["Password"].asCString(),ncode);
            database->GetLogInstance()->LogInfo("Index %d code : %d",i,ncode);
        }
    }
}
void Test_LoginUser()
{
    
}
void Test_CreateRole()
{
    
}
void Test_DeleteRole()
{
    
}

int main(int argc,char *argv[]) {
    testing::InitGoogleTest(&argc,argv);

//    pooltest();
    timetest();
    CLogInstance *inst = new CLogInstance(stdout);
    inst->NewLine();
    //CDataBaseClient *client = CreateMySqlClient(inst);
    //CDataBaseClient *client = CreateDataBaseClient("mysqlp",inst);
    CLdbiDataBase *client = CreateLDBIDataBase(inst);
    client->Connect("127.0.0.1", 3306, "root", "root", "LGameDB");
    std::string sql = "insert into T_Test values()";
    client->Query(sql);
    

    std::string errsql = "insert into T_Test(name) values('赵磊');";
    client->Query(errsql);
//    std::string querysql = "select * from T_Test";
//    client->Query(querysql);
    client->Test("proc");
    Test_InsertUser(client);
    
    
    //Create Role
    //Goto Game
    //Leave to Game
    //Delete Role
    
    inst->LogInfo("Hello, That's from log!");
    delete client;
    return RUN_ALL_TESTS();
    
    return 0;
}
