#ifndef DBILOGIC_H
#define DBILOGIC_H
#include <string>
#include "databaseclient.h"
#include "mysqldatabasep.h"
class CDBILogic
{
public:
    CDBILogic();
    ~CDBILogic();
public:
    void CreateUserName(const std::string &username,const std::string &password);
    void LoginUserByName(const std::string &username,const std::string &password,int &globalid);
    void CreateRole(int globalid,const std::string &rolename,int fileindex,int profession,int scene);
    void DeleteRole(int globalid,int fileindex);
    void EnterGame(int globalid,int fileindex);
    void LeaveGame(int globalid,int fileindex);
private:
    CDataBaseClient *m_dbclient;
};



#endif /* DBILOGIC_H */
