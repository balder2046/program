#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H
#include <string>
#include "commondefine.h"
#include "loginstance.h"
class CDataBaseClient
{
 public:
    CDataBaseClient();
    virtual void Connect(const std::string &ipaddr,unsigned short port,const std::string &username,const std::string &password,const std::string &dbname) = 0;
    virtual void CloseDB() = 0;
    void SetLogInstance(CLogInstance *logInst)
    {
        m_logInst = logInst;
    }
 protected:
    CLogInstance *m_logInst;
};


#endif /* DATABASECLIENT_H */
