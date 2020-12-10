#ifndef LAYER_CONCAT_H
#define LAYER_CONCAT_H

#include "layer.h"

namespace ncnn {

class Concat : public Layer {
  public:
    Concat();
    virtual int load_param(const ParamDict& pd);

  public:
    int axis;
};
}

#endif
