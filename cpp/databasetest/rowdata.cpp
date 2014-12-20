#include "rowdata.h"
#include "stdlib.h"
#include "stdio.h"
#include <time.h>
#include <string.h>
CRowData::CRowData(size_t maxSize, AllocatorBase *allocator)
{
    if (allocator == null)
    {
        m_pAllocator = AllocatorBase::GetDefaultAllocator();
    }
    else
    {
        m_pAllocator = allocator;
    }
    mDataBuf = (byte *)m_pAllocator->Alloc(maxSize);
    Reset();
}


CRowData::~CRowData()
{
    m_pAllocator->Free(mDataBuf);
}
bool CRowData::Write(DataBaseDataType type, const char *buf, int length)
{
    char *endptr = 0;
    byte nowtype = (byte)type;
    write(&nowtype,sizeof(byte));
    
    switch(type)
    {
    case DATATYPE_NULL:
        break;
    case DATATYPE_TINYINT:
    {
        int data = strtol(buf,&endptr,10);
        byte bydata = (byte)data;
        write(&bydata,sizeof(bydata));
        break;
    }
    case DATATYPE_SHORT:
    {
        int data = strtol(buf,&endptr,10);
        short sdata = (short)data;
        write(&sdata,sizeof(sdata));
        break;
    }
    case DATATYPE_INT:
    {
        int data = strtol(buf,&endptr,10);
        write(&data,sizeof(int));
        break;
    }
    
    case DATATYPE_BIGINT:
    {
        long long data = strtoll(buf,&endptr,10);
        write(&data,sizeof(long long));
        break;
    }
    case DATATYPE_FLOAT:
    {
        
        float data = strtof(buf,&endptr);
        write(&data,sizeof(float));
        break;
    }
    case DATATYPE_DOUBLE:
    {
        double data = strtod(buf,&endptr);
        write(&data,sizeof(data));
        break;
    }
    case DATATYPE_DATETIME:
    {
        int year,month,day,hour,minitue,second;
        sscanf(buf,"%4d-%2d-%2d %2d:%2d:%2d",&year,&month,&day,&hour,&minitue,&second);
        struct tm dateinfo;
        dateinfo.tm_year = year;
        dateinfo.tm_mon = month;
        dateinfo.tm_mday = day;
        dateinfo.tm_hour = hour;
        dateinfo.tm_min = minitue;
        dateinfo.tm_sec = second;
        time_t time = mktime(&dateinfo);
        write(&time,sizeof(time_t));
        break;
        
        
    }
    case DATATYPE_STRING:
    {
        int length = strlen(buf);
        write(&length,sizeof(int));
        write(buf,length);
        break;
    }
    case DATATYPE_BINARY:
    {
        write(&length,sizeof(int));
        write(buf,length);
        break;
    
    }
    default:
        return false;
        break;
        
        
    }
    return true;
      
};
void CRowData::Reset(){
    mRead = 0;
    mWrite = 0;
}
bool CRowData::write(const void *buf,size_t size)
{
    memcpy(mDataBuf + mWrite,buf,size);
    mWrite += size;
    return true;
}
bool CRowData::read(void *buf,size_t size)
{
    memcpy(buf,mDataBuf+mRead,size);
    mRead += size;
    return true;
}
bool CRowData::testType(DataBaseDataType type,bool &isnull)
{
    byte btype;
    bool suc = read(&btype,1);
    if (!suc) return false;
    isnull = false;
    if (type == DATATYPE_NULL)
    {
        isnull = true;
        return true;
    }
    else
    {
        return btype == (byte)type;
    }
    
}
bool CRowData::GetTimeString(char *szText,size_t maxBuf,bool &isnull)
{
    time_t timedata;
    getData(DATATYPE_DATETIME, (byte *)&timedata, sizeof(time_t), isnull);
    struct tm *tm_time = localtime(&timedata);
    strftime(szText,maxBuf,"%F %T",tm_time);
    return true;
}
bool CRowData::getData(DataBaseDataType type,byte *buf,size_t size,bool &isnull)
{
    bool suc = testType(type,isnull);
    if (!suc) return false;
    if (isnull) return true;
    //string and binarydata need to be specific
    if (type == DATATYPE_STRING || type == DATATYPE_BINARY)
    {
        size_t length = 0;
        suc = read(&length,sizeof(int));
        if (!suc) return false;
        if (length + 1 > size && type == DATATYPE_STRING)
        {
            length = size - 1;
        }
        read(buf,length);
        if (type == DATATYPE_STRING)
        {
            buf[length] = 0;    
        }
        
        return true;
    }
    else{
        return read(buf,size);       
    }
        
 
}
