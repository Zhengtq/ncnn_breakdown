#ifndef NCNN_NET_H
#define NCNN_NET_H
#include <stdlib.h>
#include <string>
#include <vector>
#include "blob.h"
#include "layer.h"

namespace ncnn{

class Net {
  public:
    Net();
    ~Net();

  public:
    std::vector<Layer*> layers;
    std::vector<Blob> blobs;  //存放blob的信息,如layer或者shape等等


};


}
#endif
