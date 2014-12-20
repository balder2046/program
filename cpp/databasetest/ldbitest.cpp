#include <stdio.h>
#include "ldbitest.h"
#include "loginstance.h"
#include "databaseclient.h"
#include <boost/pool/pool.hpp>
#include <time.h>
#include <gtest/gtest.h>
using namespace boost;

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
    
}
int main(int argc,char *argv[]) {
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
//    pooltest();
    timetest();
    CLogInstance *inst = new CLogInstance(stdout);
    inst->NewLine();
    CDataBaseClient *client = CreateMySqlClient(inst);
    client->Connect("127.0.0.1", 3306, "root", "root", "LGameDB");
    std::string sql = "insert into T_Test values()";
    client->Query(sql);

    std::string errsql = "insert into T_Test(name) values('赵磊');";
    client->Query(errsql);
    std::string querysql = "select * from T_Test";
    client->Query(querysql);
    inst->LogInfo("Hello, That's from log!");


    delete client;
    return 0;
}
