#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H
#include <string>
#include "commondefine.h"
#include "loginstance.h"
class CDataBaseClient
{
 public:
    CDataBaseClient();
    virtual ~CDataBaseClient();
    virtual int Connect(const std::string &ipaddr,unsigned int port,const std::string &username,const std::string &password,const std::string &dbname) = 0;
    virtual void CloseDB() = 0;
    //About the Logs
    virtual bool Query(const std::string &sql) = 0;
    
 public:
        
    void SetLogInstance(CLogInstance *logInst)
    {
        m_logInst = logInst;        
    }
 protected:
    CLogInstance *m_logInst;
};
CDataBaseClient * CreateMySqlClient(CLogInstance *logInst);

#endif /* DATABASECLIENT_H */
