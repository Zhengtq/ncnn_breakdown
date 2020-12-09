#ifndef NCNN_DATAREADER_H
#define NCNN_DATAREADER_H

#include <stdio.h>

namespace ncnn {

class DataReader {
  public:
    virtual ~DataReader();
    virtual int scan(const char* format, void* p) const;
    virtual size_t read(void* buf, size_t size) const;
};

class DataReaderFromStdio : public DataReader {
  public:
    DataReaderFromStdio(FILE* fp);
    virtual int scan(const char* format, void* p) const;
    virtual size_t read(void* buf, size_t size) const;

  protected:
    FILE* fp;
};


}







#endif
