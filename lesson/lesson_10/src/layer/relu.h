#ifndef LAYER_RELU_H
#define LAYER_RELU_H
#include <string.h>
#include "layer.h"
using namespace std;
namespace ncnn {

class ReLU : public Layer {
  public:
    ReLU();
    virtual int load_param(const ParamDict& pd);
    virtual int forward_inplace(Mat& bottom_top_blob, const Option& opt) const;

  public:
    float slope;
};
}

#endif
