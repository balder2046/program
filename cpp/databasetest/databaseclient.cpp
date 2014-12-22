#include "databaseclient.h"
#include "mysqldatabase.h"
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



