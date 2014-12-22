#ifndef DBILOGIC_H
#define DBILOGIC_H
#include <string>
#include "databaseclient.h"
class CDBILogic
{
public:
    CDBILogic();
    ~CDBILogic();
public:
    void CreateUserName(const std::string &username,const std::string &password);
private:
    CDataBaseClient *m_dbclient;
};



#endif /* DBILOGIC_H */
