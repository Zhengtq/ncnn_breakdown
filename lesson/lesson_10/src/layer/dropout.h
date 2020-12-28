#ifndef LAYER_DROPOUT_h
#define LAYER_DROPOUT_h
#include "layer.h"

namespace ncnn {

class Dropout : public Layer {
  public:
    Dropout();
    virtual int load_param(const ParamDict& pd);
    virtual int forward_inplace(Mat& bottom_top_blob, const Option& opt) const;

  public:
    float scale;
};
}

#endif
