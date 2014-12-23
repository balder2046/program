#include "databaseclient.h"
#include "mysqldatabase.h"
#include "mysqldatabasep.h"
CDataBaseClient::CDataBaseClient()
{
    m_logInst = NULL;
}
CDataBaseClient::~CDataBaseClient() {
   
}
CDataBaseClient * CreateMySqlClient(CLogInstance *logInstance) {
    CDataBaseClient *pClient = new CMySqlDataBase();
    pClient->SetLogInstance(logInstance);
    return pClient;
}

void FreeMySqlClient(CDataBaseClient *&client)
{
    delete client;
    client = NULL;
}

CDataBaseClient * CreateDataBaseClient(const std::string &name,CLogInstance *logInstance)
{
    CDataBaseClient *pClient = NULL;
    if (name == "mysql")
    {
        pClient = new CMySqlDataBase();        
    }
    else if (name == "mysqlp")
    {
        pClient = new CMySqlDataBasePlus();
    }
    pClient->SetLogInstance(logInstance);
    return pClient;
}
void FreeDataBaseClient(CDataBaseClient *&client)
{
    SAFE_DELETE(client);
}


