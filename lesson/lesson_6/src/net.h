#ifndef NCNN_NET_H
#define NCNN_NET_H
#include <stdlib.h>
#include <string>
#include <vector>
#include "blob.h"
#include "datareader.h"
#include "layer.h"

namespace ncnn{

class Net {
  public:
    Net();
    ~Net();

    int load_param(const DataReader& dr);
    int load_param(const char* protopath);
    int find_blob_index_by_name(const char* name) const;

  public:
    std::vector<Layer*> layers;
    std::vector<Blob> blobs;  //存放blob的信息,如layer或者shape等等


};


}
#endif
