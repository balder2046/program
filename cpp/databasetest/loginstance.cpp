#include "loginstance.h"
#include <stdarg.h>
CLogInstance::CLogInstance(FILE *filep)
{
    m_filep = filep;
}
CLogInstance::~CLogInstance()
{
    if (m_filep){
        fclose(m_filep);
    }       
}
void CLogInstance::printf(const char *format,...){
    va_list args;
    va_start(args,format);
    vfprintf(m_filep,format,args);
}
void CLogInstance::LogV(int error,const char *format,va_list args) {
    
    if (error == LOG_ERROR){
        fprintf(m_filep,"error : ");
        vfprintf(m_filep,format,args);
    }
    else if(error == LOG_WARNNING) {
        fprintf(m_filep,"warnning : ");
        vfprintf(m_filep,format,args);
    }
    else {
        fprintf(m_filep,"info : ");
        vfprintf(m_filep,format,args);
        
    }
	fprintf(m_filep,"\n");

    
}    

        
    
void CLogInstance::LogError(const char *format,...) {
    int error = LOG_ERROR;
    va_list args;
    va_start(args,format);
    LogV(error,format,args);
}



void CLogInstance::LogWarnning(const char *format,...) {
    va_list args;
    va_start(args,format);
    LogV(LOG_WARNNING,format,args);
}
void CLogInstance::LogInfo(const char *format,...){
    va_list args;
    va_start(args,format);
    LogV(LOG_INFO,format,args);
}

void CLogInstance::NewLine() {
	fprintf(m_filep,"\n");
}
