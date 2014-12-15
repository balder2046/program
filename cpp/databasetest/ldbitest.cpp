#include <stdio.h>
#include "ldbitest.h"
#include "loginstance.h"
#include "databaseclient.h"
int main() {
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

