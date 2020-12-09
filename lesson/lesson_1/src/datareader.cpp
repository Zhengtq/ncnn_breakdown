#include "datareader.h"
#include <string.h>

namespace ncnn {
DataReader::~DataReader() {}

int DataReader::scan(const char*, void*) const { return 0; }
size_t DataReader::read(void*, size_t) const { return 0; }

DataReaderFromStdio::DataReaderFromStdio(FILE* _fp) : fp(_fp) {}

int DataReaderFromStdio::scan(const char* format, void* p) const { return fscanf(fp, format, p); }

size_t DataReaderFromStdio::read(void* buf, size_t size) const { return fread(buf, 1, size, fp); }
}
