#ifndef LAYER_SOFTMAX_H
#define LAYER_SOFTMAX_H

#include "layer.h"

namespace ncnn {

class Softmax : public Layer {
  public:
    Softmax();
    virtual int load_param(const ParamDict& pd);

  public:
    int axis;
};
}

#endif
