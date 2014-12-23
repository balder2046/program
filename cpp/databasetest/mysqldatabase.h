#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H
#include "databaseclient.h"
#include <mysql/mysql.h>
class CMySqlDataBase :public  CDataBaseClient
{
 public:
    CMySqlDataBase();
    ~CMySqlDataBase();
 public:
    int Connect(const std::string &addr,unsigned int port,const std::string &username,const std::string &password,const std::string &dbname);
    void CloseDB();
 public:
	bool Query(const std::string &sql);
public:
    virtual void Test(const std::string &testname);
 private:
    MYSQL *m_hmysql;
};


#endif /* MYSQLDATABASE_H */
