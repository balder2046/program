#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H
#include "DataBaseclient.h"
class CMySqlDataBase : CDataBaseClient
{
 public:
    CMySqlDataBase();
    ~CMySqlDataBase();
 pulbic:
    int Connect(const std::string &addr,short port,const string &username,const string &password,const string &dbname);
    void CloseDB();
 private:
    MYSQL *m_hmysql;
};


#endif /* MYSQLDATABASE_H */
