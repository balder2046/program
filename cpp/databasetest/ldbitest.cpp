#include <stdio.h>
#include "ldbitest.h"
#include "loginstance.h"
#include "databaseclient.h"
#include <boost/pool/pool.hpp>
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
int main() {
    pooltest();
    
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
