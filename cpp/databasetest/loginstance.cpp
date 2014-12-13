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
