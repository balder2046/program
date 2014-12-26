#ifndef DATABASECLIENT_H
#define DATABASECLIENT_H
#include <string>
#include "commondefine.h"
#include "loginstance.h"
class CDataBaseClient
{
public:
    enum {Input_Parameter,Output_Parameter};
 public:
    CDataBaseClient();
    virtual ~CDataBaseClient();
    virtual int Connect(const std::string &ipaddr,unsigned int port,const std::string &username,const std::string &password,const std::string &dbname) = 0;
    virtual void CloseDB() = 0;
    //About the Logs
    virtual bool Query(const std::string &sql) = 0;
protected:
    virtual void onConnected(){};
    
    
    
 public:
        
    void SetLogInstance(CLogInstance *logInst)
    {
        m_logInst = logInst;        
    }
    CLogInstance *GetLogInstance()
        {
            return m_logInst;
        }
public:
    virtual void Test(const std::string &)
        {
            
        }
    
 protected:
    CLogInstance *m_logInst;
};
CDataBaseClient * CreateMySqlClient(CLogInstance *logInst);
void FreeMySqlClient(CDataBaseClient *&client);
CDataBaseClient * CreateDataBaseClient(const std::string &name,CLogInstance *logInst);
void FreeDataBaseClient(CDataBaseClient *&client);


#endif /* DATABASECLIENT_H */
