#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H
#include <string>
#include "commondefine.h"
class CDataBaseClient
{
 public:
    CDataBaseClient();
    virtual void Connect(const std::string &ipaddr,unsigned short port,const std::string &username,string &password,const std::string &dbname) = 0;
    virtual void CloseDB() = 0;
    void SetLogInstance(LogInstance *logInst)
    {
        m_logInst = logInst;
    }
 protected:
    LogInstance *m_logInst;
};


#endif /* DATABASECLIENT_H */
