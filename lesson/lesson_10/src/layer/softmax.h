#ifndef LAYER_SOFTMAX_H
#define LAYER_SOFTMAX_H

#include "layer.h"

namespace ncnn {

class Softmax : public Layer {
  public:
    Softmax();
    virtual int load_param(const ParamDict& pd);
    virtual int forward_inplace(Mat& bottom_top_blob, const Option& opt) const;

  public:
    int axis;
};
}

#endif
