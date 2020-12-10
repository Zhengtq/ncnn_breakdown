#ifndef NCNN_LAYER_H
#define NCNN_LAYER_H
#include <string>
#include <vector>
#include "paramdict.h"

namespace ncnn {

class Layer {
  public:
    Layer();
    virtual ~Layer();
    virtual int load_param(const ParamDict& pd);

  public:
    std::string type;
    std::string name;
    std::vector<int> bottoms;
    std::vector<int> tops;

};


}

#endif
