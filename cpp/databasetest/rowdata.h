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
    
protected:
    
    bool Write(DataBaseDataType type,const char *szbuf,int length);
    bool write(const void *buf,size_t size);
    bool read(void *buf,size_t size);
private:
    bool testType(DataBaseDataType type,bool &isnull);
    bool getData(DataBaseDataType type,byte *buf,size_t size,bool &isnull);

private:
    byte *dataBuf;
    size_t mWrite;
    size_t mRead;

};


#endif /* ROWDATA_H */
