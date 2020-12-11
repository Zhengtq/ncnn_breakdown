#ifndef NCNN_BLOB_H
#define NCNN_BLOB_H

#include <string>
#include <vector>

namespace ncnn {

class Blob {
  public:
    Blob();

  public:
    std::string name;
    int producer;
    std::vector<int> consumers;
};
}

#endif
