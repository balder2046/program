#ifndef ROWDATA_H
#define ROWDATA_H
#include <stdio.h>
#include <string.h>
#include "commondefine.h"
enum DataBaseDataType
{
    DATATYPE_NULL,
    DATATYPE_TINYINT,
    DATATYPE_SHORT,
    DATATYPE_SMALLINT=DATATYPE_SHORT,
    DATATYPE_INT,
    DATATYPE_BIGINT,
    DATATYPE_FLOAT,
    DATATYPE_DOUBLE,
    DATATYPE_STRING,
    DATATYPE_DATETIME,
    DATATYPE_BINARY,
    
};
//a databuffer represent a row    
class CRowData
{
    
 public:
    CRowData();
    ~CRowData();
public:
    void Reset();
public:
    bool WriteInt32(const char *szBuf,int length);
    bool GetTinyInt(byte *data,bool &isnull)
    {
        return getData(DATATYPE_TINYINT,data,1,isnull);
    }
    bool GetShort(short *data,bool &isnull)
    {
        return getData(DATATYPE_SHORT,(byte *)data,2,isnull);
    }
    bool GetInt(int *data,bool &isnull)
    {
        return getData(DATATYPE_INT,(byte *)data,4,isnull);
    }
    bool GetInt64(long long *data,bool &isnull)
    {
        return getData(DATATYPE_BIGINT,(byte *)data,8,isnull);
    }
    bool GetString(char *szText,size_t maxBuf,bool &isnull)
    {
        return getData(DATATYPE_STRING,(byte *)szText,maxBuf,isnull);
    }
    bool GetBinaryData(byte *buf,size_t maxBuf,bool &isnull)
    {
        return getData(DATATYPE_BINARY,buf,maxBuf,isnull);
    }
public:
    
    
    bool WriteTinyInt(byte *data)
    {
     
        if(!data)
        {
            
            return writeType(DATATYPE_NULL);
        }
        bool bsuc = writeType(DATATYPE_TINYINT);
        if (!bsuc) return false;
        return write(data,1);        
    }
    bool WriteShort(short *data)
    {
        
        if (!data)
        {
            return writeType(DATATYPE_NULL);
        }        
        if (!writeType(DATATYPE_SHORT)) return false;        
        return write(data,2);        
        
    }
    bool WriteInt(int *data)
    {
     
        if (!data)
        {
     
            return writeType(DATATYPE_NULL);
        }
        if (!writeType(DATATYPE_INT)) return false;        
        return write(data,sizeof(int));                
    }
    
    bool WriteInt64(long long *data)
    {
        DataBaseDataType type;
        if (!data)
        {
            type = DATATYPE_NULL;
            return writeType(type);
        }
        if (!writeType(DATATYPE_BIGINT)) return false;
        return write(data,sizeof(long long));        
    }
    bool WriteString(char *szText)
    {
        DataBaseDataType type;
        if (!szText)
        {
            type = DATATYPE_NULL;
            return writeType(type);
        }
        if (!writeType(DATATYPE_STRING)) return false;
        size_t len = strlen(szText);
        if (!write(&len,sizeof(len))) return false;
        return write(szText,len);        
    }
    bool WriteBinary(byte *buf,size_t length)
    {
        DataBaseDataType type;
        if (!buf)
        {
            return writeType(DATATYPE_NULL);
        }
        writeType(DATATYPE_BINARY);
        if (!write(&length,sizeof(int))) return false;
        return write(buf,length);        
    }
protected:
    
    bool Write(DataBaseDataType type,const char *szbuf,int length);
    bool write(const void *buf,size_t size);
    bool read(void *buf,size_t size);
private:
    bool writeType(DataBaseDataType type)
        {
            byte btype = (byte)type;
            return write(&btype,1);
            
        }
    bool testType(DataBaseDataType type,bool &isnull);
    bool getData(DataBaseDataType type,byte *buf,size_t size,bool &isnull);
    

private:
    byte *dataBuf;
    size_t mWrite;
    size_t mRead;

};



#endif /* ROWDATA_H */
