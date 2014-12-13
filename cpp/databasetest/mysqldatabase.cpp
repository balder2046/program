#include "Mysqldatabase.h"
#include <mysql/mysql.h>
using namespace std;
CMySqlDataBase::CMySqlDataBase() {
    m_hmysql = mysql_init(null);   
}
CMySqlDataBase::~CMySqlDataBase() {
    if (m_hmysql != NULL)
    {
        mysql_close(m_hmysql);
    }   
}
int CMySqlDataBase::Connect(const std::string &host,unsigned int port,const string &username,const string &password,const string &dbname) {
    bool bAutoReConnect = true;
    if (m_hmysql) {
        MYSQL *pHandle = NULL;
        pHandle = mysql_real_connect(m_hmysql,host.c_str(),username.c_str(),password.c_str(),dbname.c_str(),port,0,CLIENT_MULTI_RESULTS);
        if (pHandle) {
            if (bAutoReConnect){
                mysql_option(m_hmysql,MYSQL_OPT_RECONNECT,"1")
            }
                
        }
        else {
            if (m_logInst){
                m_logInst->printf();
            }

        }
            
    }

    
    return 0;
}
void CMySqlDataBase::CloseDB()
{
    
}
