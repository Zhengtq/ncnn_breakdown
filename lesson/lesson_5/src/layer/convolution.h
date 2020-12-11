#ifndef LAYER_CONVOLUTION_H
#define LAYER_CONVOLUTION_H

#include "layer.h"

namespace ncnn {

class Convolution : public Layer {
  public:
    Convolution();
    virtual int load_param(const ParamDict& pd);

  public:
    int num_output;
    int kernel_w;
    int kernel_h;
    int dilation_w;
    int dilation_h;
    int stride_w;
    int stride_h;
    int pad_left;
    int pad_right;
    int pad_top;
    int pad_bottom;
    float pad_value;
    int bias_term;
    int weight_data_size;
    int int8_scale_term;
    int activation_type;
    float bottom_blob_int8_scale;
    float top_blob_int8_scale;
    bool use_int8_requantize;
    int impl_type;

};
}

#endif
