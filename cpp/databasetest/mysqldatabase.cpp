#include "mysqldatabase.h"
#include <memory.h>
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
void CMySqlDataBase::Test(const std::string &name)
{
    if (name == "proc")
    {
        MYSQL_STMT *stmt = NULL;
        stmt = mysql_stmt_init(m_hmysql);
        size_t length = 0;
        char cmdname[] = "call _LDBI_CreateUserCore(?,?,?)";
        length = strlen(cmdname);
        if (mysql_stmt_prepare(stmt, cmdname, length))
        {
            m_logInst->LogError("mysql_stmt_prepare error ,error reason %s", mysql_stmt_error(stmt));
            mysql_stmt_close(stmt);
            return;
        }
        int count = mysql_stmt_param_count(stmt);
        m_logInst->LogInfo("There is %d parameters",count);

        MYSQL_BIND bind[3];
        memset(bind,0,sizeof(bind));
        char username[] = "zhangsan";
        char password[] = "111111";
        int retcode = 1;
        unsigned long retcode_length = 0;
        unsigned long username_length = strlen(username);
        unsigned long password_length = strlen(password);
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (char *)username;
        bind[0].buffer_length = username_length;
        bind[0].length = &username_length;

        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = (char *)password;
        bind[1].buffer_length = password_length;
        bind[1].length = &password_length;
        
        bind[2].buffer_type = MYSQL_TYPE_LONG;
        bind[2].buffer = (char *)&retcode;
        bind[2].buffer_length = sizeof(int);
        bind[2].length = &retcode_length;
        if (mysql_stmt_bind_param(stmt,bind))
        {
            m_logInst->LogError("Bind Parameter Error,the reason is %s", mysql_stmt_error(stmt));
            mysql_stmt_close(stmt);
            return;
        }
        if (mysql_stmt_execute(stmt))
        {
            m_logInst->LogError("mysql_stmt_execute error ,error reason : %s", mysql_stmt_error(stmt));
            mysql_stmt_close(stmt);
            return;
        }
        int num_fields = mysql_stmt_field_count(stmt);
        m_logInst->LogInfo("There is %d fields!",num_fields);
        if (m_hmysql->server_status & SERVER_PS_OUT_PARAMS)
        {
            m_logInst->LogInfo("The Result is produced by procedure out parameter %s", "");
        }
        else
        {
            m_logInst->LogInfo("The Result is produced by procedure %s", "");
        }
        mysql_stmt_bind_result(stmt,&bind[2]);
        mysql_stmt_fetch(stmt);
        m_logInst->LogInfo("_LDBI_CreateUser RetCode %d , output length %d",retcode,retcode_length);
        mysql_stmt_close(stmt);
        stmt = NULL;       
    }
}
