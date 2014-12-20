#include "mysqldatabase.h"

using namespace std;
CMySqlDataBase::CMySqlDataBase() {
    m_hmysql = mysql_init(NULL);   
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
                mysql_options(m_hmysql,MYSQL_OPT_RECONNECT,"1");
            }
            m_logInst->LogInfo("Connect host %s port %d ok!",host.c_str(),port);
                
        }
        else {
            if (m_logInst){
                m_logInst->LogError("Connect host:%s port %d username %s password %s ,error!",host.c_str(),port,username.c_str(),password.c_str());
            }

        }
            
    }

    
    return 0;
}
void CMySqlDataBase::CloseDB()
{
    if (m_hmysql) {
		mysql_close(m_hmysql);
		m_hmysql = NULL;
	}
}
bool CMySqlDataBase::Query(const std::string &sql)
{
	size_t len = sql.length();
	int ret = mysql_real_query(m_hmysql,sql.c_str(),len);
	if (ret > 0) {
		m_logInst->LogError("query %s error, retcode : %d",sql.c_str(),ret);
	}
	else {
		m_logInst->LogInfo("query %s ok!",sql.c_str());
		MYSQL_RES *res = mysql_store_result(m_hmysql);
		if (!res) {
			m_logInst->LogInfo("There is no results!");
		}
		else {
			my_ulonglong rownum = mysql_num_rows(res);
			m_logInst->LogInfo("There is %d results",rownum);
			unsigned int num_fields = mysql_num_fields(res);
			for (int i = 0; i < rownum; ++i) {
				MYSQL_ROW row;
				row = mysql_fetch_row(res);
				unsigned long *lengths;
				lengths = mysql_fetch_lengths(res);
				for (int j = 0;j < num_fields; ++j) {
					m_logInst->LogInfo("\tIndex %d Length %d resulte %s",j,lengths[j],row[j]);
				}
													   
				
			}
		}
	}
					 
	return ret == 0;
}
